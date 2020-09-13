//initializing the Led Pins in the program

const int LED_1 = 13;
const int LED_2 = 12;
const int LED_3 = 11;
const int LED_4 = 10;
const int LED_5 = 9;

//initailizing the Button Pins in the program

const int Button_1 = 2;
const int Button_2 = 3;

//initializing the state of the Buttons in the program

int ButtonState_1;
int ButtonState_2;

//initializing the Patterns of the two buttons in the program

int Pattern_1;
int Pattern_2;

//initializing a delay value for the Buttons' patterns

int DelayValue = 500;

void setup()
{
  //LEDs from 1 to 5 in the breadboad are OUTPUT values to the program

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);

  //Two Buttons in the breadboard are considered as INPUT values to the program

  pinMode(Button_1, INPUT);
  pinMode(Button_2, INPUT);

}

void loop()
{

  //reading values from Button_1 to the state of the Button " ButtonState_1 "

  ButtonState_1 = digitalRead(Button_1);

  // if the state of the First button is at a HIGH value, proceed

  if (ButtonState_1 == HIGH)
  {
    //an increment for the First Pattern will help to indicate " ButtonState_1 " to the Pattern

    Pattern_1++;

    delay(2000);
  }

  //initialing the First Pattern for the Blue Button and LEDs

  if (Pattern_1 == 1)
  {
    digitalWrite(LED_1, 1);
    digitalWrite(LED_3, 0);
    digitalWrite(LED_5, 1);

    delay(DelayValue);

    digitalWrite(LED_1, 0);
    digitalWrite(LED_3, 1);
    digitalWrite(LED_5, 0);

    delay(DelayValue);
  }

  //initializing an extra pattern without a role in LEDs
  //This pattern is intialized for the sake of switching the Blue Button to " LOW " (Off)

  if (Pattern_1 == 2)
  {
    digitalWrite(LED_1, 0);
    digitalWrite(LED_3, 0);
    digitalWrite(LED_5, 0);

    //Returning values to the first Pattern after a press on the Blue Button.

    Pattern_1 = 0;
  }

  //reading values from Button_2 to the state of the Button " ButtonState_2 "

  ButtonState_2 = digitalRead(Button_2);

  // if the state of the Second button is at a HIGH value, proceed
  
  if (ButtonState_2 == HIGH)
  {

    //an increment for the First Pattern will help to indicate " ButtonState_2 " to the Pattern

    Pattern_2++;
    delay(2000);
  }

  //initialing the First Pattern for the Red Button and LEDs

  if (Pattern_2 == 1)
  {
    digitalWrite(LED_2, 1);
    digitalWrite(LED_4, 1);

    delay(DelayValue);

    digitalWrite(LED_2, 0);
    digitalWrite(LED_4, 0);

    delay(DelayValue);
  }

  //initializing an extra pattern without a role in LEDs
  //This pattern is intialized for the sake of switching the Red Button to " LOW " (Off)

  if (Pattern_2 == 2)
  {
    digitalWrite(LED_2, 0);
    digitalWrite(LED_4, 0);

    //Returning values to the first Pattern after a press on the Red Button.
    
    Pattern_2 = 0;
  }
}
