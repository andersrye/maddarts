# Simple dartboart monitor, prints output from dartboard
# Requires pySerial

import serial, time, httplib, urllib2

s = serial.Serial(
	port='/dev/tty.usbserial-A900DAT9', #replace with something OS-appropriate
	baudrate=9600,
	parity=serial.PARITY_ODD,
	stopbits=serial.STOPBITS_TWO,
	bytesize=serial.SEVENBITS
)

if(s.isOpen() == False):
    s.open()

def post_hit(hit):
	url = "http://mariamapserver.teleplan.no/hacksim/dart/"+hit
	result = urllib2.urlopen(url).read()
	#print result
	if result == '{message : "Nice shot!"}':
		print "        __   ___ " 
		print "|\ | | /  ` |__  "
		print "| \| | \__, |___ "
                 
	
buffer = ''

while True:
	time.sleep(.1)
	buffer += s.read(s.inWaiting())
	if '\n' in buffer:
		for msg in buffer.split("\n")[:-1]:
			throw = msg.strip().split(";")
			print throw
			if throw[1] == '3':	
				post_hit(throw[0])
		buffer = ''
		
