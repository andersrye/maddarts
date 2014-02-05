// Anders S Rye 2014

#include <time.h>
#include <stdio.h>
#include <wiringPi.h>
#include <pcf8574.h>

int main (int argc, char** argv)
{
	wiringPiSetup();
	pcf8574Setup (100, 0x21);
	pcf8574Setup (110, 0x3a);
	pcf8574Setup (120, 0x24);

	printf("pri %i\n", piHiPri(99));

	int row[10] = {100, 101, 102, 103, 104, 110, 111, 112, 113, 114};
	int column[7] = {120, 121, 122, 123, 124, 125, 126};

	int n;
	for(n = 0; n < 10; n++)
	{
		pinMode(row[n], OUTPUT);
		digitalWrite(row[n], HIGH);
	}
	for(n = 0; n < 7; n++)
	{
		pinMode(column[n], INPUT);
	}

	char* board[10][7] = {
			      {"0a", "1a", "2a", "3a", "4a", "5a", "6a"},
			      {"0b", "1b", "2b", "3b", "4b", "5b", "6b"},
			      {"0c", "1c", "2c", "3c", "4c", "5c", "6c"},
			      {"0d", "1d", "2d", "3d", "4d", "5d", "6d"},
			      {"0e", "1e", "2e", "3e", "4e", "5e", "6e"},
			      {"0f", "1f", "2f", "3f", "4f", "5f", "6f"},
			      {"0g", "1g", "2g", "3g", "4g", "5g", "6g"},
			      {"0h", "1h", "2h", "3h", "4h", "5h", "6h"},
			      {"0i", "1i", "2i", "3i", "4i", "5i", "6i"},
			      {"0j", "1j", "2j", "3j", "4j", "5j", "6j"}
			     };


	for (;;)
	{
		int i;
		for(i = 3; i < 5; i++)
		{
			digitalWrite(row[i], LOW);
			int j;
			for(j = 3; j < 5; j++)
			{
				int r = digitalRead(column[j]);
				if(r == 0)
				{
					delay(1);
					if(r != digitalRead(column[j])) continue;
					printf("%s %s %li\n", argv[1], board[i][j], time(NULL));
					fflush(stdout);

					while( digitalRead(column[j]) == 0) { ; }
				}
			}
			digitalWrite(row[i], HIGH);
		}
//		delay(1);
	}
	return 0;
}
