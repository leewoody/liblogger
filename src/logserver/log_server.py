# Log server
import socket
import threading
import sys
import time
from datetime import date

HOST = ''                 # Symbolic name meaning the local host
PORT = 50007              # Arbitrary non-privileged port

class Worker(threading.Thread):
	def __init__(self, conn, address):
		threading.Thread.__init__(self)        
		self.conn		= conn
		self.address	= address
		self.filename		= time.strftime("%d-%b-%Y-%H-%M-%S.log",time.localtime())
		self.file		= open(self.filename,'w')
		self.runFlag	= 1

	def run(self):
		print 'Log filename is ',self.filename
		while self.runFlag:
			data = self.conn.recv(1024)
			if not data: break
			self.file.write(data)
			self.file.write('\n')
			self.file.flush()
			if len(data):
				print data
				print "" #new line.
		self.conn.close()
		self.file.close()
		print "Connection closed :" , self.address


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
s.bind((HOST, PORT))
s.listen(5)
workers = []
while 1:
	try:
		print "Waiting for connections on Port %d ....." % PORT
		conn, addr = s.accept()
		print 'Connected by', addr
		worker = Worker(conn,addr) 
		worker.start()
		workers.append(worker)
	except:
		print 'caught an exception, exiting...'
		sys.exit()
