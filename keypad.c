#include <wiringPi.h>
#include <pcf8574.h>

main ()
{
	wiringPiSetup();
	pcf8574Setup (100, 0x21);

	
}
