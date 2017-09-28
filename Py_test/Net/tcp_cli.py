# -*- coding:utf-8 -*-

from socket import *

HOST = '127.0.0.1'
PORT = 21568
ADDR = (HOST, PORT)

BUFSIZ = 1024

tcpCliSocket = socket(AF_INET, SOCK_STREAM)
tcpCliSocket.connect(ADDR)

while True:
	data = raw_input('>')
	if not data:
		break
	tcpCliSocket.send(data)
	data = tcpCliSocket.recv(BUFSIZ)
	if not data:
		break
	print data
tcpCliSocket.close()