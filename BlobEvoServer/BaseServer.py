import socket
import threading
from Utils import *

class BaseServer:
    def __init__(self, name:str, OUTER_IP: str, port: int):
        super().__init__()

        self.OUTER_IP = OUTER_IP
        self.port = port
        self.name = name


    def run(self):
        client_base = []
        
        outer_server = socket.socket()
        
        if self.OUTER_IP != None:
            outer_server.bind((self.OUTER_IP, self.port))
            outer_server.listen(5)
            
            player_server_accept_thread = threading.Thread(target=self.accept_clients, args=(outer_server, client_base, ))
            player_server_accept_thread.start()
        
        inner_server = socket.socket()
        inner_server.bind(("127.0.0.1", self.port))
        inner_server.listen(5)

        player_server_accept_thread = threading.Thread(target=self.accept_clients, args=(inner_server, client_base, ))
        player_server_accept_thread.start()


    def accept_clients(self, server: socket.socket, client_base: list):
        while True:
            client, addr = server.accept()
            print(self.name + " | found client on - " + str(addr) + "\n")

            client_base.append(client)

            handle_client_thread = threading.Thread(target=self.handle_client, args=(len(client_base) - 1, client_base, ))
            handle_client_thread.start()


    def handle_client(self, client_id: int, client_base: list):
        try:
            while True:
                length = client_base[client_id].recv(2).decode()
                length = int(from_cpp_to_python(length))

                msg = client_base[client_id].recv(length)
                translated_msg = from_cpp_to_python(msg.decode())
                
                for i in range(0, len(client_base)):
                    if i != client_id:
                        print(self.name + " | " + " id - " + str(client_id) + " sent - " + translated_msg + "\n")
                        client_base[i].send(msg)

                print(self.name + " | " + " id - " + str(client_id) + " received - " + translated_msg + "\n")
                self.client_msg_callback(msg, client_id, client_base)
        except:
            client_base.remove(client_base[client_id])
            

    def client_msg_callback(self, msg: str, client_id: int, client_base: list):
        pass