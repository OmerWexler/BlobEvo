import socket
import threading
import BaseServer
from Utils import *

GAME_MANAGER_PORT = 2001

class GameManagerServer(BaseServer.BaseServer):
    def __init__(self, OUTER_IP):
        super().__init__("Game Manager Server", OUTER_IP, GAME_MANAGER_PORT)

    def client_msg_callback(self, translated_msg: str, client_id: int, client_base: list):
        pass
