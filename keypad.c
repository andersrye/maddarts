#include <stdio.h>
#include <wiringPi.h>
#include <pcf8574.h>

main ()
{
	wiringPiSetup();
	pcf8574Setup (100, 0x21);

	printf("Hello\n");

	pinMode(100, OUTPUT);
	pinMode(101, OUTPUT);
	pinMode(102, OUTPUT);
	pinMode(103, OUTPUT);
	pinMode(104, INPUT);
	pinMode(105, INPUT);
	pinMode(106, INPUT);

	digitalWrite(100, HIGH);
	digitalWrite(101, HIGH);
	digitalWrite(102, HIGH);
	digitalWrite(103, HIGH);

	char array[4][3] = {{'3', '2', '1'},
			    {'6', '5', '4'},
			    {'6', '8', '7'},
			    {'#', '0', '*'}};

	for (;;)
	{
		int i;
		for(i = 0; i < 4; i++)
		{
			digitalWrite(i +100, LOW);
			int j;
			for(j = 4; j < 7; j++)
			{
				int r = digitalRead(j + 100);
				if(r == 0)
				{
					delay(5);
					if(r != digitalRead(j)) continue;
					printf("PRESSED: %c\n", array[i][j-4]);
					while( digitalRead(j+100) == 0) { ; }
				}
			}
			digitalWrite(i+100, HIGH);
		} 
		//digitalWrite(100, HIGH);
		//delay(1000);
		//digitalWrite(100, LOW);
		//printf("104: %i\n", digitalRead(104));
		//printf("105: %i\n", digitalRead(105));
		//printf("106: %i\n", digitalRead(106));
		//printf("hallo\n");
		delay(10);
	}
	return 0;
}
