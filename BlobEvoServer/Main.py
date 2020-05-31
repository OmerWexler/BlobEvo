import PlayerServer 
import GameManagerServer 
import BlobDirectionServer 

IP = "192.168.1.20"

def main():
    player_server = PlayerServer.PlayerServer(IP)
    player_server.run()

    game_manager_server = GameManagerServer.GameManagerServer(IP)
    game_manager_server.run()

    blob_direction_server = BlobDirectionServer.BlobDirectionServer(IP)
    blob_direction_server.run()

if __name__ == "__main__":
    main()