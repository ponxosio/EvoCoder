import serial
import time

class Communications(object):

	def __init__(self, device, rate):
		self.ser = serial.Serial(port=device, baudrate=rate, timeout=10)
	
	def sendString(self, string):
		return self.ser.write(string)
	
	def receiveString(self):
		return self.ser.readline()
	
	def synch(self):
			time.sleep(0.5)