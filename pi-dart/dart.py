# Simple dartboart monitor, prints output from dartboard
# Requires pySerial

import serial, time

s = serial.Serial(
	port='/dev/tty.usbserial-A900DAT9', #replace with something OS-appropriate
	baudrate=9600,
	parity=serial.PARITY_ODD,
	stopbits=serial.STOPBITS_TWO,
	bytesize=serial.SEVENBITS
)

if(s.isOpen() == False):
    s.open()
	
buffer = ''

while True:
	time.sleep(.1)
	buffer += s.read(s.inWaiting())
	if '\n' in buffer:
		for msg in buffer.split("\n")[:-1]:
			print msg
		buffer = ''
		
