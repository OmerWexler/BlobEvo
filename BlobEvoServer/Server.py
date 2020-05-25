import socket
import threading

IP = "127.0.0.1"

# Player managment
PLAYER_PORT = 2000
REPORT_PLAYER_HEADER = "RNP"
PLAYER_COUNT_HEADER = "PCH"

def main():
    players = []
    
    player_server = socket.socket()
    player_server.bind((IP, PLAYER_PORT))
    player_server.listen(5)
    
    player_server_accept_thread = threading.Thread(target=accept_clients, args=(player_server, players, ))
    player_server_accept_thread.start()


def accept_clients(server: socket.socket, client_base: list):
    while True:
        client, addr = server.accept()
        print("Found client on - " + str(addr))

        client_base.append(client)

        handle_client_thread = threading.Thread(target=handle_player, args=(len(client_base) - 1, client_base, ))
        handle_client_thread.start()


def handle_player(client_id: int, client_base: list):
    while True:
        length = client_base[client_id].recv(2).decode()
        length = int(from_cpp_to_python(length))

        msg = client_base[client_id].recv(length)
        translated_msg = from_cpp_to_python(msg.decode())
        
        for i in range(0, len(client_base)):
            if i != client_id:
                print(str(client_id) + " Send - " + translated_msg)
                client_base[i].send(msg)

        print(str(client_id) + " Recv - " + translated_msg)
        
        if translated_msg[0:3] == REPORT_PLAYER_HEADER:
            report_player_count(len(client_base), client_base[client_id])


def report_player_count(player_count: int, client: socket.socket):
    msg = ''
    msg += PLAYER_COUNT_HEADER
    
    if player_count < 10:
        msg += '0'

    msg += str(player_count)
    client.send(from_pyhton_to_cpp(msg).encode())


def from_cpp_to_python(msg: str):
    return ''.join(chr(ord(letter) + 1) for letter in msg)

def from_pyhton_to_cpp(msg: str):
    return ''.join(chr(ord(letter) - 1) for letter in msg)

# def accept_clients():
#     global players
        
#     home_ip = "127.0.0.1" 
#     port = 2000
#     bind_successful = False

#     while (not bind_successful):
#         try:
#             s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#             s.bind((home_ip, port))
#             bind_successful = True

#         except OSError as e:
#             print(e)
            
#             if (e.errno == 10048): # Port already taken
#                 port += 1
        
#     print("Server up on: " + str(home_ip) + ", " + str(port))

#     while True:
#         s.listen(1)

#         new_client, client_address = s.accept()

#         new_player = PlayerHandler.PlayerHandler(new_client)
#         players.append(new_player)

#     s.close()


if __name__ == "__main__":
    main()