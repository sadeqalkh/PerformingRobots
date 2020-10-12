//PROGRAM'S CONCEPT
// This program's concept lets the robot play audio for one time, run its motors, display expressions, and use a button to control the robot's initialization. 
// The button role is to control both the OLED display and the motors. The motors run when a button initializes the function "DancingRobot." When the motors' loop 
// ends, the OLED display shows a sad facial expression, indicating that the robot is at a stable position that prevents it from running. The user's role is to make 
// the robot happy to dance in which the user should expect a smiley face for the robot's satisfaction.

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
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    32

//  smiley face that initiates in the OLED display when the motors move

static const unsigned char PROGMEM SmileyFace_bmp[] =
{
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000011, B11000000, B00000011, B11000000,
  B00000011, B11000000, B00000011, B11000000,
  B00000011, B11000000, B00000011, B11000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000001, B10000000, B00000001, B10000000,
  B00000001, B10100000, B00000101, B10000000,
  B00000000, B11011111, B11110110, B00000000,
  B00000000, B01110000, B00011100, B00000000,
  B00000000, B00001111, B11110000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000
};

//  sad face that initiates in the OLED display when the motors stop running

static const unsigned char PROGMEM SadFace_bmp[] =
{
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000011, B11000000, B00000011, B11000000,
  B00000011, B11000000, B00000011, B11000000,
  B00000011, B11000000, B00000011, B11000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00011111, B11110000, B00000000,
  B00000000, B11100000, B00011110, B00000000,
  B00000001, B10000000, B00000011, B00000000,
  B00000011, B00000000, B00000001, B10000000,
  B00001110, B00000000, B00000000, B11100000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000
};



void setup()
{
  //  this is where the robots music starts playing
  MP3StartUp();

  //  Use to halt motor movement (ground)
  pinMode(8, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Starting sketch.");

  //  SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  //if statement in which identifies in the SerialMonitor if the button is acknowledged in Arduino or not.
  if (button.begin() == false)
  {
    Serial.println("Button Not Acnowledged");
    while (1);
  }
  Serial.println("Button Acnowledged");

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();


  myMotorDriver.settings.commInterface = I2C_MODE;

  //  set address if I2C configuration selected with the config jumpers
  myMotorDriver.settings.I2CAddress = 0x5D; //config pattern is "1000" (default) on board for address 0x5D

  //  set chip select if SPI selected with the config jumpers
  myMotorDriver.settings.chipSelectPin = 10;

  //  initialize the driver get wait for idle
  while ( myMotorDriver.begin() != 0xA9 ) //  Wait until a valid ID word is returned
  {
    Serial.println( "ID mismatch, trying again" );
    delay(500);
  }
  Serial.println( "ID matches 0xA9" );

  //  Check to make sure the driver is done looking for slaves before beginning
  Serial.print("Waiting for enumeration...");
  while ( myMotorDriver.ready() == false );
  Serial.println("Done.");
  Serial.println();

  //  Uncomment code for motor 1 inversion
  while ( myMotorDriver.busy() ); //Waits until the SCMD is available.
  myMotorDriver.inversionMode(1, 1); //invert motor 1

  while ( myMotorDriver.busy() );
  //  Enables the output driver hardware
  myMotorDriver.enable();
}

//identifying the left and right motors by 0 and 1 in the program
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

void loop()
{
  //to display values and text from the function "ButtonisPressed"
  ButtonisPressed();
  display.display();
}

//Function that is responsible for all the user's button INPUT
void ButtonisPressed()
{
  int ButtonPressed = button.isPressed();

  if (button.isPressed() == true)
  {
    DancingHappyFace();
  }

  // while loop to stop the program from repeting the previous display text, preventing it to force covering the upcoming initializations data/values and texts.

  while (button.isPressed() == true)
  {
    DancingRobot();
  }

  if (button.isPressed() == false)
  {
    StopDancingFace();
  }
}

void DancingRobot()
{
  //  stop both motors for 10 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay (1000);

  //  go forward for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 210);
  delay(5000);

  //  turn left for 4 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 150);
  delay(4000);

  // go forward for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 200);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 200);
  delay(5000);

  // go right for 1 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 150);
  delay(1000);

  // go forward for 1 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 200);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 200);
  delay(1000);

  // go left for 1 second
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 150);
  delay(1000);

  // go forward for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 200);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 200);
  delay(5000);

  //move backward for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 200);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 200);
  delay(5000);

  // go FORWARD for 13 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 50);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 50);
  delay(13000);

  // go RIGHT for 3 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 250);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 250);
  delay(3000);

  // go LEFT for 5 second
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 250);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 250);
  delay(5000);

  // go RIGHT for 5 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 250);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 250);
  delay(5000);

  // go LEFT for 5 second
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 250);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 250);
  delay(5000);

  // go FORWARD for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 150);
  delay(5000);

  //go BACKWARD for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 150);
  delay(5000);

  // go RIGHT for 5 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 250);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(5000);

  // go LEFT for 5 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 250);
  delay(5000);

  // go FORWARD for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 150);
  delay(5000);

  //go BACKWARD for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 150);
  delay(5000);

  //stop for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 0);
  delay(5000);

  // go RIGHT for 5 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 150);
  delay(5000);

  // go FORWARD for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 150);
  delay(5000);

  // go LEFT for 5 second
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 150);
  delay(5000);

  //go BACKWARD for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 150);
  delay(5000);

  // go FORWARD for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 150);
  delay(5000);

  // go RIGHT for 5 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 110);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 110);
  delay(5000);

  // go FORWARD for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 100);
  delay(5000);

  // go RIGHT for 5 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 90);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 90);
  delay(5000);

  //go BACKWARD for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 90);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 90);
  delay(5000);

  // go LEFT for 6 second
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 50);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 50);
  delay(6000);
}


void StopDancingFace()
{
  //  to stop motors from running after the Robot Dance
  delay(10);
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);

  //  declare the bit drawing of the sad face in this function
  display.clearDisplay();
  display.drawBitmap
  ( (display.width()  - LOGO_WIDTH ) / 2, (display.height() - LOGO_HEIGHT) / 2, SadFace_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);

  display.display();
}

void DancingHappyFace()
{
  //  declare the bit drawing of the smiley face in this function
  display.clearDisplay();
  display.drawBitmap
  ( (display.width()  - LOGO_WIDTH ) / 2, (display.height() - LOGO_HEIGHT) / 2, SmileyFace_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);

  display.display();
}

void MP3StartUp()
{
  Wire.begin();

  //  Check to see if Qwiic MP3 is present on the bus
  if (mp3.begin() == false)
  {
    Serial.println("Qwiic MP3 failed to respond. Please check wiring and possibly the I2C address. Freezing...");
    while (1);
  }

  mp3.setVolume(31); //Volume can be 0 (off) to 31 (max)
  //  getting info from MP3 player to the Serial Monitor

  Serial.print("Playing the first track: ");
  mp3.playTrack(1);
  //  Give the WT2003S a bit of time before we check to see which track is playing (allow song to start)
  delay(500);

  Serial.println("All done!");
}
