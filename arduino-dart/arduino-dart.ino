
int row[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int column[7] = {12, A0, A1, A2, A3, A4, A5};

char* board[10][7] = {{"14;3", "14;2", "14;1", "25;2", "9;1", "9;2", "9;3"},
                      {"11;3", "11;2", "11;1", "25;1", "12;1", "12;2", "12;3"},
                      {"8;3", "8;2", "8;1", "NULL", "5;1", "5;2", "5;3"},
                      {"16;3", "16;2", "16;1", "NULL", "20;1", "20;2", "20;3"},
                      {"15;3", "15;2", "15;1", "NULL", "10;1", "10;2", "10;3"},
                      {"2;3", "2;2", "2;1", "NULL", "6;1", "6;2", "6;3"},
                      {"17;3", "17;2", "17;1", "NULL", "13;1", "13;2", "13;3"},
                      {"3;3", "3;2", "3;1", "NULL", "4;1", "4;2", "4;3"},
                      {"19;3", "19;2", "19;1", "NULL", "18;1", "18;2", "18;3"},
                      {"7;3", "7;2", "7;1", "NULL", "1;1", "1;2", "1;3"}};

void setup()
{
  for(int n = 0; n < 10; n++)
  {
    pinMode(row[n], OUTPUT);
    digitalWrite(row[n], HIGH);
  }
  for(int n = 0; n < 7; n++)
  {
    pinMode(column[n], INPUT_PULLUP);
  }
  
  Serial.begin(9600);
}

void loop()
{
  for(int i = 0; i < 10; i++)
  {
    //PORTD = i < 6 ? 0x7f^(4 << i) : 0x7f;
    //PORTB = i < 6 ? 0xf : 0xf^(1<<i-6);
    digitalWrite(row[i], LOW);
    byte pins = PINC << 1 | digitalRead(column[0]);
    if(pins != 0x7f)
    {
      int j = log(0x7f^pins)/log(2);
      Serial.println(board[i][j]);
      while( digitalRead(column[j]) == 0) { ; }
    }
    digitalWrite(row[i], HIGH);
  }
}