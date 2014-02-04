import serial, time, sys, subprocess

p = subprocess.Popen(["socat", "-", "UDP-DATAGRAM:255.255.255.255:5000,broadcast"], stdin=subprocess.PIPE)

if(len(sys.argv) < 2):
	print "Missing board ID"
	sys.exit(0)

s = serial.Serial(
	port='/dev/ttyUSB0',
	baudrate=9600,
	parity=serial.PARITY_ODD,
	stopbits=serial.STOPBITS_TWO,
	bytesize=serial.SEVENBITS
)

if(s.isOpen() == False):
    s.open()

def format(string):
	msg = string.split(';')
	pmsg = "Board " + msg[0] + ": "
	if msg[2] == "2":
		pmsg += "DOUBLE"
	elif msg[2] == "3":
		pmsg += "TRIPLE!"
	pmsg += " " + msg[1]
	return pmsg

while 1 :
	output = ''
	time.sleep(.2)
	while s.inWaiting() > 0:
		output += s.read(1)
	if output != '':
		string = sys.argv[1] + ";" + output.strip() + ";" + str(int(time.time()*1000))
		print format(string)
		p.stdin.write(string + "\n")
		
