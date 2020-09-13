const int Led_1 = 13;
const int Led_2 = 12;
const int Led_3 = 11;
const int Led_4 = 10;
const int Led_5 = 9;

const int Pattern_Button = 2;
const int Off_Button = 3;

int Pattern =0;

int Pattern_Button_State = 0;
int Off_Button_State = 0;

int DELAY = 100;

void setup()
{

  pinMode(Led_1, OUTPUT);
  pinMode(Led_2, OUTPUT);
  pinMode(Led_3, OUTPUT);
  pinMode(Led_4, OUTPUT);
  pinMode(Led_5, OUTPUT);

  pinMode(Pattern_Button, INPUT);
  pinMode(Off_Button, INPUT);

}

void loop()
{
  Pattern_Button_State = digitalRead(Pattern_Button);
  

  if (Pattern_Button == HIGH && Off_Button == LOW)
  {
    Pattern++;
    delay(1000);
  }
else
{
  Off_Button == HIGH;
}
  //To initialize the First pattern

  if (Pattern == 1)
  {
    digitalWrite(Led_1 , 1);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 1);

    delay(DELAY);

    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 1);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 1);
    digitalWrite(Led_5 , 0);

    delay(DELAY);

    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 1);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 0);

    delay(DELAY);
  }
  
  if (Pattern == 2)
  {
    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 1);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 0);

    delay(DELAY);

    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 1);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 1);
    digitalWrite(Led_5 , 0);

    delay(DELAY);

    digitalWrite(Led_1 , 1);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 1);

    delay(DELAY);
  }

  //To initialize the Third pattern


  if (Pattern == 3)
  {
    digitalWrite(Led_1 , 1);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 0);

    delay(DELAY);

    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 1);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 0);

    delay(DELAY);

    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 1);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 0);

    delay(DELAY);

    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 1);
    digitalWrite(Led_5 , 0);

    delay(DELAY);

    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 1);

    delay(DELAY);
  }

  //To initialize the Fourth pattern

  if (Pattern == 4)
  {
    digitalWrite(Led_1 , 1);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 1);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 1);

    delay(DELAY);

    digitalWrite(Led_1 , 1);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 1);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 1);

    delay(DELAY);

    digitalWrite(Led_1 , 1);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 1);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 1);

    delay(DELAY);

    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 1);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 1);
    digitalWrite(Led_5 , 0);

    delay(DELAY);

    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 1);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 1);
    digitalWrite(Led_5 , 0);

    delay(DELAY);

    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 1);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 1);
    digitalWrite(Led_5 , 0);

    delay(DELAY);
  }

  if (Pattern == 5)
  {
    digitalWrite(Led_1 , 0);
    digitalWrite(Led_2 , 0);
    digitalWrite(Led_3 , 0);
    digitalWrite(Led_4 , 0);
    digitalWrite(Led_5 , 0);

    Pattern = 0;
  }
}
