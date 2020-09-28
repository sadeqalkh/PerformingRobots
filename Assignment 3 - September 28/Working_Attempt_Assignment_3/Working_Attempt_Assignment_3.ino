//The program's concept is to let the user visualize his/her button presses counts in the OLED display. As the program starts functioning in the OLED display, 
//the user will be looking at the 'Adafruit' logo. The OLED display logo can be recognized by the user as a welcome or start page to the button count. 
//As the user presses once on the start page, the program will direct the user to another page display "Button Pressed." When the button is unpressed by the user, 
//the program will lead the user to a page display "Count" with a value that starts from 1 and increments forever by 1. Thus, leaving the user with a count value 
//that demonstrates the total number of button presses.


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_Qwiic_Button.h>

QwiicButton button; //initializing the QwiicButton with the name button. Also, "button" is considered as a Pin to refer to.

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ButtonCount = 0; //an integer value that is reponsible for the button counts

void setup()
{
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
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
}


void loop()
{
  //to display values and text from the function "ButtonisPressed"
  ButtonisPressed();
  display.display();

}

//Function that is responsible for all the user's button INPUT
void ButtonisPressed()
{


  int ButtonValue = button.isPressed();

  if (button.isPressed() == true)
  {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(25, 15);
    display.println("Button");
    display.setCursor(25, 35);
    display.println("Pressed");
    display.display();

    // while loop to stop the program from repeting the previous display text, preventing it to force covering the upcoming initializations data/values and texts.

    while (button.isPressed() == true)
    {
      delay(10);
    }
  }

  //if ButtonValue is HIGH/pressed from the user, increment the previous value to the new one.
  //In this step the user will see the number of count will increase by one when pressing the button

  if (ButtonValue == true)
  {
    ButtonCount++;
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 25);
    display.print("Count: ");
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(90, 25);
    //printing the button count values to the i2c OLED display
    display.println(ButtonCount);
    display.display();
  }

  //creating a while loop to cover a repititive loop from "ButtonCount" Values
  //As the value "ButtonCount" appears and update, the program will stop until a further press from the user

  while (button.isPressed() == false)
  {
    delay(10);
  }

}
