import socket
import Store

class PlayerHandler:
    
    def __init__(self, client: socket.socket, store: Store.Store):
        self.client = client
        self.store = store
