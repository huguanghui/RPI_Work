# -*- coding: utf-8 -*-

from socket import *
from time import ctime

HOST = ''
PORT = 21568
ADDR = (HOST, PORT)

BUFSIZ = 1024

tcpSerSock = socket(AF_INET, SOCK_STREAM)
tcpSerSock.bind(ADDR)
tcpSerSock.listen(5)

try:
	while True:
		print 'waiting for connection...'
		tcpSerSock, addr = tcpSerSock.accept()
		print '...connect from:', addr
		while True:
			data = tcpSerSock.recv(BUFSIZ)
			if not data:
				break
			tcpSerSock.send('[%s] %s Data' % (ctime(), data))

			tcpSerSock.close
except EOFError, KeyboardInterrupt:
	tcpSerSock.close