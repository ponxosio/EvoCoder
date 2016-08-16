import time
from communications import Communication

com = Communication('/.//COM3', 38400)
time.sleep(5.05)

for i in range(0,20):
	time.sleep(0.05)
	print 'sending READS'
	com.sendString("READS")

	print 'receiving...'
	time.sleep(0.05)
	print com.receiveString()