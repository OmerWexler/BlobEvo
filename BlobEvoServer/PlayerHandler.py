import socket

class PlayerHandler:
    
    def __init__(self, client: socket.socket):
        self.client = client
