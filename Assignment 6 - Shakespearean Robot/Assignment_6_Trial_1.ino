#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_Qwiic_Button.h>

#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"
#include "SparkFun_Qwiic_MP3_Trigger_Arduino_Library.h"

//  initializing the QwiicButton with the name button. Also, "button" is considered as a Pin to refer to.
QwiicButton button;

// OLED display width, in pixels
#define SCREEN_WIDTH 128
// OLED display height, in pixels
#define SCREEN_HEIGHT 64

//  Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SCMD myMotorDriver; //This creates the main object of one motor driver and connected slaves.
MP3TRIGGER mp3; // Considering "mp3" as a name for the Qwiic MP3 TRIGGER

//  Declaring the dimensions of both smiley and sad face in the program
#define LOGO_HEIGHT   26  //Max is 64
#define LOGO_WIDTH    64  //Max is 128

bool Button_Pressed;
int LED_Brightness = 100;

static const unsigned char PROGMEM Crown_Logo[] =
{
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000001, B11111111, B11111111, B10000000, B00000000, B00000000,
  B00000000, B11110000, B00000011, B00000000, B00000000, B11000000, B00001111, B00000000,
  B00000000, B11011100, B00000110, B00000000, B00000000, B01100000, B00111011, B00000000,
  B00000000, B01100110, B00001100, B00000000, B00000000, B00110000, B01100110, B00000000,
  B00000000, B01100011, B00011000, B00000000, B00000000, B00011000, B11000110, B00000000,
  B00000000, B01100001, B10110000, B00000000, B00000000, B00001101, B10000110, B00000000,
  B00000000, B00110000, B11100000, B00000001, B10000000, B00000111, B00001100, B00000000,
  B00000000, B00110000, B01100000, B00000110, B01100000, B00000110, B00001100, B00000000,
  B00000000, B00110000, B00110000, B00001100, B00110000, B00001100, B00001100, B00000000,
  B00000000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00000000,
  B00000000, B00011000, B00001100, B00110000, B00001100, B00110000, B00011000, B00000000,
  B00000000, B00011000, B00000110, B01100000, B00000110, B01100000, B00011000, B00000000,
  B00000000, B00001100, B00000011, B11000000, B00000011, B11000000, B00110000, B00000000,
  B00000000, B00001100, B00000001, B10000000, B00000001, B10000000, B00110000, B00000000,
  B00000000, B00001100, B00000011, B11000000, B00000011, B11000000, B00110000, B00000000,
  B00000000, B00000110, B00000110, B01100000, B00000110, B01100000, B01100000, B00000000,
  B00000000, B00000110, B00001100, B00110000, B00001100, B00110000, B01100000, B00000000,
  B00000000, B00000111, B11111111, B11111111, B11111111, B11111111, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000111, B11111111, B11111111, B11111111, B11111111, B11100000, B00000000,
  B00000000, B00000111, B11111111, B11111111, B11111111, B11111111, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};

void setup()
{
  Serial.begin(9600);

  //  To start loading the OLED Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  //  To clear the OLED Display
  display.clearDisplay();
  //  To display the Crown Logo bitmap in the OLED Display
  display.drawBitmap(0, 0, Crown_Logo, 128, 64, WHITE);
  ( (display.width()  - LOGO_WIDTH ) / 2, (display.height() - LOGO_HEIGHT) / 2, Crown_Logo, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  //  Setting motor driver at I2C
  myMotorDriver.settings.commInterface = I2C_MODE;
  //  I2C address of motor driver
  myMotorDriver.settings.I2CAddress = 0x5D;
  //  I2C address of motor driver
  Wire.begin();

  //---------------------------------------------------------------------------------------

  //  For Button Check in the Serial Monitor

  //  check if button will acknowledge over I2C
  if (button.begin() == false)
  {
    Serial.println("Program did not connect to button! Freezing...");
    while (1);
  }
  Serial.println("Button is connected.");

  //---------------------------------------------------------------------------------------

  //  For OLED Display Check in the Serial Monitor

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D))
  { // Address 0x3D for 128x64
    Serial.println(F("OLED Display allocation failed, please try and reconnect the display."));
    for (;;); // Don't proceed, loop forever
  }

  //---------------------------------------------------------------------------------------

  // For MP3 Player Check in the Serial Monitor

  if (mp3.begin() == false)
  {
    Serial.println("Qwiic MP3 failed to respond. Please check wiring and possibly the I2C address. Freezing...");
    while (1);
  }

  //---------------------------------------------------------------------------------------
}




#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

void loop()
{
  if (button.isPressed() == true)
  {
    button.LEDon(LED_Brightness);
    Button_Pressed = true;
    delay(50);
  }
  if (Button_Pressed == true)
  {
    mp3.playTrack(1);

    for (int movement = 0; movement < 1; movement++)
    {
      delay(1000);

      Forward_Movement_Fast();
      delay(5000);

      Right_Movement();

      Left_Movement();

      Forward_Movement_Slow();
      delay(5000);

      Right_Movement();

      Backward_Movement_Slow();
      delay(5000);

      Stop_Movement();

      Right_Movement();

      Right_Movement();

      Forward_Movement_Slow();
      delay(5000);

      Left_Movement();

      Stop_Movement();

      Left_Movement();

      Backward_Movement_Slow();
      delay(5000);

      Right_Movement();

      Left_Movement();

      Right_Movement();

      Stop_Movement();

      Backward_Movement_Fast();
    }
    Button_Pressed = false;
  }
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);

  mp3.stop();
  Button_Pressed = false;

}
void Right_Movement()
{
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 0);
  delay(2000);

  myMotorDriver.setDrive( LEFT_MOTOR, 1, 125);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 0);
  delay(2000);

  myMotorDriver.setDrive( LEFT_MOTOR, 1, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 0);
  delay(1000);
}

void Left_Movement()
{
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 150);
  delay(2000);

  myMotorDriver.setDrive( LEFT_MOTOR, 1, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 125);
  delay(2000);

  myMotorDriver.setDrive( LEFT_MOTOR, 1, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 100);
  delay(1000);
}

void Stop_Movement()
{
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay (5000);
}

void Forward_Movement_Slow()
{
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 100);
}

void Forward_Movement_Fast()
{
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 150);
}

void Backward_Movement_Slow()
{
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 100);
}

void Backward_Movement_Fast()
{
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 150);
  delay(7000);
}