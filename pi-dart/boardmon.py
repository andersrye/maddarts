import serial, time, sys, subprocess

p = subprocess.Popen(["socat", "-", "UDP-DATAGRAM:255.255.255.255:5000,broadcast"], stdin=subprocess.PIPE)

def set_procname(newname):
    from ctypes import cdll, byref, create_string_buffer
    libc = cdll.LoadLibrary('libc.so.6')    #Loading a 3rd party library C
    buff = create_string_buffer(len(newname)+1) #Note: One larger than the name (man prctl says that)
    buff.value = newname                 #Null terminated string as it should be
    libc.prctl(15, byref(buff), 0, 0, 0) #Refer to "#define" of "/usr/include/linux/prctl.h" for the misterious value 16 & arg[3..5] are zero as the man page says.


if(len(sys.argv) < 2):
	print "Missing board ID"
	sys.exit(0)

set_procname("boardmon")

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
		
