import time
from communications import Communications
from evoprog2wayvalve import Evoprog2WayValve

com = Communications('/.//COM3', 115200)
time.sleep(1)
print com.receiveString()

#configuration
print "configuring..."
valve = Evoprog2WayValve([46])
valve.addConnection(1,2,com)
valve.addConnection(1,3,com)

com.sendString("rValvePos 46\r")
time.sleep(0.5)
print com.receiveString()

i = 0;
while True:
	pos = (i % 8) + 2
	print "moving to position " + str(pos)
	valve.setConnection(1, pos, com)
	i = i + 1
	time.sleep(7)

