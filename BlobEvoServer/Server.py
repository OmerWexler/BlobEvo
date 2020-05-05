import socket
import PlayerHandler
import threading

players = []

def main():
    client_accept_thread = threading.Thread(target=start_accepting_clients)
    client_accept_thread.start()

    while True:
        pass
        
def start_accepting_clients():
    global players
        
    home_ip = "127.0.0.1" 
    port = 63000
    bind_successful = False

    while (not bind_successful):
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.bind((home_ip, port))
            bind_successful = True

        except OSError as e:
            print(e)
            
            if (e.errno == 10048): # Port already taken
                port += 1
        
    print("Server up on: " + str(home_ip) + ", " + str(port))

    while True:
        s.listen(1)

        new_client, client_address = s.accept()

        new_player = PlayerHandler.PlayerHandler(new_client)
        players.append(new_player)

    s.close()


if __name__ == "__main__":
    main()