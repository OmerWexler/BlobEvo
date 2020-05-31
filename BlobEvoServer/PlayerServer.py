import socket
import threading
import BaseServer
from Utils import *

PLAYER_PORT = 2000
REPORT_PLAYER_HEADER = "RNP"
PLAYER_ID_HEADER = "PIH"

class PlayerServer(BaseServer.BaseServer):
    def __init__(self, OUTER_IP):
        super().__init__("Player Server", OUTER_IP, PLAYER_PORT)
        self.players = []

    def client_msg_callback(self, msg: str, client_id: int, client_base: list):
        decoded_msg = msg.decode()
        translated_msg = from_cpp_to_python(decoded_msg)

        new_player_id = len(client_base) - 1
        
        if new_player_id < 10:
            new_player_id = '0' + str(new_player_id)
        elif new_player_id > 10:
            new_player_id = str(new_player_id)
        
        if translated_msg[0:3] == REPORT_PLAYER_HEADER:
            self.echo_player_list(new_player_id, client_base[client_id])
        
        self.players.append(translated_msg[3:])


    def echo_player_list(self, player_id: str, client: socket.socket):
        msg = ''
        msg += PLAYER_ID_HEADER
        msg += str(player_id)
        client.send(from_pyhton_to_cpp(msg).encode())

        for player in self.players:
            msg = ''
            msg += REPORT_PLAYER_HEADER
            msg += player
            print(player)
            client.send(from_pyhton_to_cpp(msg).encode())
