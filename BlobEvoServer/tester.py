import time
import socket
s = socket.socket()

s.bind(("127.0.0.1", 2000))
s.listen(1)
c, a = s.accept()

time.sleep(5)
msg = "REP0100300"
msg = ''.join(chr(ord(letter) - 1) for letter in msg)
c.send(msg.encode())

time.sleep(5)
msg = "REP0100301"
msg = ''.join(chr(ord(letter) - 1) for letter in msg)
c.send(msg.encode())

msg = c.recv(10).decode()
print(''.join(chr(ord(letter) + 1) for letter in msg))