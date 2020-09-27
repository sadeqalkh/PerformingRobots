
#include <SparkFun_Qwiic_Button.h>
QwiicButton button;


int value = 0;
int counter = 0;
int currentState = 0;
int previousState = 0;





void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic button examples");
  Wire.begin(); //Join I2C bus

  //check if button will acknowledge over I2C
  if (button.begin() == false) {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Button acknowledged.");
}

void loop()
{
  //check if button is pressed, and tell us if it is!
  if (button.isPressed() == true) {
    Serial.println("The button is pressed!");
    while (button.isPressed() == true)
      delay(10);  //wait for user to stop pressing

    Serial.println("The button is not pressed!");
  }
  delay(20); //Don't hammer too hard on the I2C bus


  if (button.isPressed() == true)
  {
    currentState = 1;
  }
  delay(10);
  if (button.isPressed() == false)
  {
    currentState = 0;
  }

  if (currentState != previousState)
  {
    if (currentState == 1)
    {
      counter++;
      Serial.println(counter);
    }
  }
  previousState = currentState;
  delay(250);


}
