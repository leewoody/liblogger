# liblogger - copyright 2007, Vineeth Neelakant, nvineeth@gmail.com
# This file is part of liblogger.
#
# liblogger is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
# 
# liblogger is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Log server
import socket
import threading
import sys
import time
from datetime import date

HOST = ''                 # Symbolic name meaning the local host
PORT = 50007              # Arbitrary non-privileged port

if len(sys.argv) > 2:
	print "usage : %s [port no]" % (sys.argv[0])
elif len(sys.argv) == 2:
	# The user has specified a port number, try to use it.
	try:
		PORT = int(sys.argv[1])
	except:
		print "Invalid port no. %s specified" % (sys.argv[1])
		sys.exit(-1)
	# Check if the port falls in the valid range.
	if PORT > 65535 or PORT < 0:
		print " port number cannot exceed 65535 or lesser than 0"
		sys.exit(-1)

	print "Trying to use port ", PORT
else:	
	print " Port not specified Using default port " , PORT 


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
			#self.file.write('\n')
			self.file.flush()
			if len(data):
				print data
				#print "\n" #new line.
		self.conn.close()
		self.file.close()
		print "Connection closed :" , self.address


# --------------------- main() ---------------------- 		
try:
	# create the socket
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
	# bind to the indicated port.
	s.bind((HOST, PORT))
	s.listen(5)
	workers = []
	while 1:
		print "Waiting for connections on Port %d ....." % PORT
		conn, addr = s.accept()
		print 'Connected by', addr
		worker = Worker(conn,addr) 
		worker.start()
		workers.append(worker)
except :
	print 'caught an exception, exiting...'
	print "Exception Details:", sys.exc_info()[0], sys.exc_info() [1]
	sys.exit(-2)

