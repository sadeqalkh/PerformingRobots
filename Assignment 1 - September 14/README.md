# Assignment One Documentation Page:

### Photo Documentation of Arduino and Breadboard:

![Assignment 1 PIC1](https://user-images.githubusercontent.com/60816393/93029214-9d84b200-f62a-11ea-9e1b-59a120c0da26.jpeg)

![Assignment 1 PIC2](https://user-images.githubusercontent.com/60816393/93029215-a1183900-f62a-11ea-9aae-2e500fb228f4.jpeg)

### The Schematic Diagram:

<img width="1183" alt="Screen Shot 2020-09-13 at 10 54 41 PM" src="https://user-images.githubusercontent.com/60816393/93026055-31974f00-f614-11ea-94b3-636aa2f637d7.png">

### Video Documentation:

https://youtu.be/qK9H7TAn3Ao

### Initial Concepts:

The initial concepts in which I passed through consisted of two main ideas of functioning. The idea was implementing patterns in the program that switches from one pattern to another by a button. As it seems, the main idea narrowed to the usage of one button for switching between lighting modes in the LED. 

At this point, I thought, whenever there is a play button, there is a stop and a reverse button. I started first by exploring how I might reverse an act from, for instance, Button 'A'. In the program, Button 'A' centered on being functional in the program by using an increment to direct the user through four to five different patterns. Knowing that I never used decrements in my previous programs, I started to explore its nature in the main code to acknowledge whether a backward button can be functional. Unfortanelty, It was not for an unknown reason, in which, when implemented, the LEDs tended to act randomly. Thus, I decided to switch to the second idea, the stop button instead of a reverse button.

In the second concept, the stop button was to support the passing button. As a case scenario, I thought, for instance, the user may want to turn Off the LEDs after perhaps exploring them. In Reality, the stop button did not work as intended. The button in the program was sending messages in the Serial Monitor; however, it was useless from the user's point of view or in Arduino. This aspect of the button was merely a physical object that existed in the input value but did not affect the central program values. Thus, directing me to think for a simpler alternative for a better working program.

### Working Concept:

This program aims to let users, specifically children, complete a simple pattern of LEDs by pushing two Buttons. Each button in the program will correspond to its LEDs, defined by the Red and Blue colors. The user in this program also can undo the patterns to set the LEDs to Off.
### Outcome:

This assignment helped me to recover techniques and information for Arduino Examples 'Blink' and 'Button.'

### Challenges:

The challenges that I mostely encountered in this assignment was from the Inital Attemps (Concepts).

### Sources:

Arduino Example "Blink":
https://www.arduino.cc/en/tutorial/blink

Arduino Example "Button":
https://www.arduino.cc/en/tutorial/button
