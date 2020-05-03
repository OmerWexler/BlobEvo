import socket
import sys


def main(argv):
    # getopt.getopt(args, options, [long_options])
    host_name = socket.gethostname() 
    host_ip = socket.gethostbyname(host_name) 

    print(host_name)
    print(host_ip)

def handle_client(client: Socket):
    pass

if __name__ == "__main__":
    main(sys.argv)

# with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#     s.bind((HOST, PORT))
#     s.listen()
#     conn, addr = s.accept()
#     with conn:
#         print('Connected by', addr)
#         while True:
#             data = conn.recv(1024)
#             if not data:
#                 break
#             conn.sendall(data)