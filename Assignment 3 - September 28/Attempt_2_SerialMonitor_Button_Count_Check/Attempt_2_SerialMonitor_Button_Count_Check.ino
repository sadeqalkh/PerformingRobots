#include <SparkFun_Qwiic_Button.h>
QwiicButton button;

int ButtonCount =0;

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic button examples");
  Wire.begin(); //Join I2C bus

  //check if button will acknowledge over I2C
  if (button.begin() == false) 
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Button acknowledged.");
}

void loop() 
{

int ButtonValue = button.isPressed();
  
  //check if button is pressed, and tell us if it is!
  if (button.isPressed() == true) 
  {
    Serial.println("The button is pressed!");
    while (button.isPressed() == true)
    {
      delay(10);  //wait for user to stop pressing
    }
    
  }
  //delay(20); //Don't hammer too hard on the I2C bus
  if (ButtonValue == true)
    {
      ButtonCount++;
     Serial.print("Button Count: ");
 
    }
    Serial.println(ButtonCount);
    while (button.isPressed() == false)
    {
      delay(10);
    }

  

}
