const int Led_1 = 13;
const int Led_2 = 12;
const int Led_3 = 11;
const int Led_4 = 10;
const int Led_5 = 9;

const int First_Pattern_Button = 2;
const int Second_Pattern_Button = 3;

int FirstPattern = 0;
int SecondPattern = 0;

int First_ButtonState = 0;
int Second_ButtonState = 0;

int DELAY = 100;

void setup()
{

  pinMode(Led_1, OUTPUT);
  pinMode(Led_2, OUTPUT);
  pinMode(Led_3, OUTPUT);
  pinMode(Led_4, OUTPUT);
  pinMode(Led_5, OUTPUT);

  pinMode(First_Pattern_Button, INPUT);
  pinMode(Second_ButtonState, INPUT);

}

void loop()
{
  First_ButtonState = digitalRead(First_Pattern_Button);
  Second_ButtonState = digitalRead(Second_Pattern_Button);


  if (First_ButtonState == HIGH && Second_ButtonState == LOW)
  {
    digitalWrite (Second_ButtonState, LOW);;
    FirstPattern++;
    delay(1000);
  }

  //To initialize the First pattern

  if (FirstPattern == HIGH)
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

  if (Second_ButtonState == HIGH && First_ButtonState==LOW)
  {
    digitalWrite (First_ButtonState, LOW);
    SecondPattern++;
    delay(1000);
  }
  if (SecondPattern == HIGH)
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
}
