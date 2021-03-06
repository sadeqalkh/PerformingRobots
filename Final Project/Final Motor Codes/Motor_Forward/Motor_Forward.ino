// This program is designed to let the Robot move Forward.

#include <Arduino.h>
#include <stdint.h>
#include "Wire.h" // for QWIIC communication
#include "SCMD.h"
#include "SCMD_config.h"

//  Motor initializations
#include "SCMD.h"
#include "SCMD_config.h"
SCMD myMotorDriver;
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

//  Button initializations
#include <SparkFun_Qwiic_Button.h>
QwiicButton button;

//  variables in this program
int state = 0;
unsigned long motionStartedAt = 0;
int button_state;

void setup()
{
  //For the motors
  pinMode(8, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Starting sketch.");

  myMotorDriver.settings.commInterface = I2C_MODE;
  myMotorDriver.settings.I2CAddress = 0x5D;
  myMotorDriver.settings.chipSelectPin = 10;

  Wire.begin();

  while ( myMotorDriver.busy() );
  myMotorDriver.enable();

  if (button.begin() == false)
  {
    Serial.println("Program did not connect to button! Freezing...");
    while (1);
  }
  else
  {
    Serial.println("Button is connected.");
  }
}

void loop()
{
  if (button_state == 0)
  {
    Button_Will_Not_Work();
  }
  if (button.isPressed() == true)
  {
    button_state = 1;
  }
  if (button_state == 1)
  {


    unsigned long currentMillis = millis();


    switch (state)
    {

      // motors will not start initiating

      case 0:

        No_Movement();
        motionStartedAt = millis();
        state = 1;
        break;

      // the motor will remain in position for 6 seconds

      case 1:

        if ((currentMillis - motionStartedAt) > 6000) {
          state = 2;
        }
        break;

      // Motors will move FORWARDS

      case 2:
        motionStartedAt = millis();
        Forward_Movement();
        state = 3;
        break;

      // the motor will remain rolling FORWARD for 10 seconds

      case 3:

        if ((currentMillis - motionStartedAt) > 10000)
        {
          state = 4;
        }
        break;

      // Stop the motors

      case 4:

        No_Movement();
        break;

    }
    // End switch(state)
  }
  //End button == 1
}
// End loop function

void Button_Will_Not_Work(void)
{

}

void Forward_Movement()
{
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 60);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 60);
}
void No_Movement()

{
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
}
