import socket
import threading
import BaseServer
from Utils import *

PLAYER_PORT = 2000
REPORT_PLAYER_HEADER = "RNP"
PLAYER_COUNT_HEADER = "PCH"

class PlayerServer(BaseServer.BaseServer):
    def __init__(self, OUTER_IP):
        super().__init__("Player Server", OUTER_IP, PLAYER_PORT)

    def client_msg_callback(self, translated_msg: str, client_id: int, client_base: list):
        if translated_msg[0:3] == REPORT_PLAYER_HEADER:
            self.report_player_count(len(client_base), client_base[client_id]) 

    
    def report_player_count(self, player_count: int, client: socket.socket):
        msg = ''
        msg += PLAYER_COUNT_HEADER
        
        if player_count < 10:
            msg += '0'

        msg += str(player_count)
        client.send(from_pyhton_to_cpp(msg).encode())
