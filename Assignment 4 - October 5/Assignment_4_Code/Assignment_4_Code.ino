//Sadeq M. Alkhoori

// Program's Concept: 
//The program's concept is to let the user experience a prototype or a child version of the main project. The program starts by outputting data from 
//the MP3 player, giving the user a context to the robot's role and personality. The robot starts by saying, "Hello, dear humans. My name is Alpha, the robot. 
//My job in my body is to move within a loop. I can move forward, backward, right, and left." Because the text needs 18 seconds to play, the motors will start 
//moving after 10 seconds from the start. The robots will perform movements, as said by the robots. The robots' script will be playing in a pattern in which it 
//will be said for the first time, skip the second, and restate again in the third motors' loop.

#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"
#include "SparkFun_Qwiic_MP3_Trigger_Arduino_Library.h"
#include <Wire.h>

SCMD myMotorDriver; //This creates the main object of one motor driver and connected slaves.
MP3TRIGGER mp3;

void setup()
{
  //  calling the Mp3 startup function
  MP3StartUp();

  //  Use to halt motor movement (ground)
  pinMode(8, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Starting sketch.");



  myMotorDriver.settings.commInterface = I2C_MODE;

  //  set address if I2C configuration selected with the config jumpers
  myMotorDriver.settings.I2CAddress = 0x5D; //config pattern is "1000" (default) on board for address 0x5D

  //  set chip select if SPI selected with the config jumpers
  myMotorDriver.settings.chipSelectPin = 10;

  //  initialize the driver get wait for idle
  while ( myMotorDriver.begin() != 0xA9 ) //Wait until a valid ID word is returned
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

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

void loop()
{
//  calling MP3 audio player and motor initializations to be considered as a loop
  RobotSpeaking();
  RobotFirstSteps();



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
  Serial.print("Song count: ");
  Serial.println(mp3.getSongCount());

  Serial.print("Volume level: ");
  Serial.println(mp3.getVolume());

  Serial.print("Firmware version: ");
  Serial.println(mp3.getVersion());

  Serial.print("Playing the first track: ");
  mp3.playTrack(1);
  //  Give the WT2003S a bit of time before we check to see which track is playing (allow song to start)
  delay(500); 
  
  String songName = mp3.getSongName();
  Serial.println(songName);

  Serial.println("All done!");
}

void RobotSpeaking()
{
  while (mp3.isPlaying() == true)
  {
    mp3.playTrack(1);
    delay(50); // Don't pound the Qwiic MP3 too hard!
  }

  Serial.print("Playing the next track: ");
  mp3.playNext();
  delay(100); //Give the WT2003S a bit of time before we check to see which track is playing (allow Robot Speech to start)
  String MP3Name = mp3.getSongName();
  Serial.println(MP3Name);
}
void RobotFirstSteps()
{
  //  stop both motors for 10 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0); //Stop motor
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0); //Stop motor
  delay (10000);

  //  go forward for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 210);
  delay(5000);

  //  turn left for 4 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(4000);

  // go forward for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 200);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 200);
  delay(5000);

  // go right for 1 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 150);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(1000);

  // go forward for 1 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 200);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 200);
  delay(1000);

  // go left for 1 second
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
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
}
