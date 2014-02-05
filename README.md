mad-darts
=========

## arduino-dart ##

The code that runs on the Arduino. Prints hits to serial (9600 baud) in the format 

	<sector>;<multiplier>

ex.:

	20;3

is a triple 20.

## pi-dart ##

Listens to the messages from the arduino on the serial port, and adds metadata (board ID and time stamp in ms) in the format

	<board-id>;<sector>;<multiplier;<timestamp>

ex.:

	b1;9;1;1391604497717

and then broadcasts this message using socat.

NB: arduino needs to be plugged in before starting the script. 

## test-files ##

Only used for testing GPIO on the pi.

Requires [wiringPi](http://wiringpi.com)

Compile with 

	gcc -Wall -o keypad keypad.c -lwiringPi
