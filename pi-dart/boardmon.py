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
	pmsg = "ID " + msg[2] + ": "
	if msg[4] == "2":
		pmsg += "DOUBLE"
	elif msg[4] == "3":
		pmsg += "TRIPLE!"
	pmsg += " " + msg[3]
	return pmsg
	
buffer = ''

while True:
	time.sleep(.1)
	buffer += s.read(s.inWaiting())
	if '\n' in buffer:
		for msg in buffer.split("\n")[:-1]:
			string = "THROW;" + str(int(time.time()*1000)) + ";" + sys.argv[1] + ";" + msg.strip() + "\n"
			print format(string)
			#print string
			p.stdin.write(string)
		buffer = ''
		
