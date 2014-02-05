// Anders S Rye 2014

#include <stdio.h>
#include <wiringPi.h>
#include <pcf8574.h>

main ()
{
	wiringPiSetup();
	pcf8574Setup (100, 0x21);

	printf("Press a button\n");

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
			    {'9', '8', '7'},
			    {'#', '0', '*'}};

	int row[4] = {100, 101, 102, 103};
	int column[3] = {104, 105, 106};

	for (;;)
	{
		int i;
		for(i = 0; i < 4; i++)
		{
			digitalWrite(row[i], LOW);
			int j;
			for(j = 0; j < 3; j++)
			{
				int r = digitalRead(column[j]);
				if(r == 0)
				{
					delay(5);
					if(r != digitalRead(column[j])) continue;

					printf("PRESSED: %c\n", array[i][j]);

					while( digitalRead(column[j]) == 0) { ; }
				}
			}
			digitalWrite(row[i], HIGH);
		} 
		delay(10);
	}
	return 0;
}
