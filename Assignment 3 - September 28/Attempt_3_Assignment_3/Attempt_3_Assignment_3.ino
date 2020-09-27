#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_Qwiic_Button.h>

QwiicButton button;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ButtonCount = 0;

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

  int ButtonValue = button.isPressed();

  if (button.isPressed() == true)
  {
    display.clearDisplay();

    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("B. Pressed");
    
    while (button.isPressed() == true)
    {
      delay(10);
    }
  }

if (ButtonValue == true)
{
  ButtonCount++;
  display.println("");
  display.print("Count: ");
}
display.println(ButtonCount);

  while(button.isPressed() == false)
  {
    delay(10);
  }
  display.display();      // Show initial text
  delay(100);
}
