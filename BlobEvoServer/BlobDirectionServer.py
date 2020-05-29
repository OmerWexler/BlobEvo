import socket
import threading
import BaseServer
from Utils import *

PLAYER_PORT = 2002

class BlobDirectionServer(BaseServer.BaseServer):
    def __init__(self, OUTER_IP):
        super().__init__("Blob Direction Server", OUTER_IP, PLAYER_PORT)

    def client_msg_callback(self, translated_msg: str, client_id: int, client_base: list):
        pass
