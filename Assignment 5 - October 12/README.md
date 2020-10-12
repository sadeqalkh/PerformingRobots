# Assignment 5 Documentation Page:

### Photo Documentation:

![Assignment 5 PIC2](https://user-images.githubusercontent.com/60816393/95710350-8957c300-0c71-11eb-85f7-4e0358ea492b.jpeg)

![Assignment 5 PIC1](https://user-images.githubusercontent.com/60816393/95710354-8a88f000-0c71-11eb-8589-56e024798164.jpeg)

![Assignment 5 Smiley Face](https://user-images.githubusercontent.com/60816393/95710358-8c52b380-0c71-11eb-9ad8-4263d17ee1c6.jpeg)

![Assignment 5 Sad Face](https://user-images.githubusercontent.com/60816393/95710361-8e1c7700-0c71-11eb-995e-3b060210045f.jpeg)

### Video Documentation:

https://youtu.be/WmsjIWV5O24

### Concept:

This program's concept lets the robot play audio for one time, run its motors, display expressions, and use a button to control the robot's initialization. The button role is to control both the OLED display and the motors. The motors run when a button initializes the function "DancingRobot." When the motors' loop ends, the OLED display shows a sad facial expression, indicating that the robot is at a stable position that prevents it from running. The user's role is to make the robot happy to dance in which the user should expect a smiley face for the robot's satisfaction.            

### Outcome:

I learned from this assignment how to control both the OLED display and the Motors by a button.

### Challenges:

My only challenge I experienced in this assignment is not knowing how to initialize the MP3 player in either "button.isPressed" or "mp3.Playing." At first, I tried to initialize the MP3 track in a loop because of my intension to play music with running motors. The motors where calculated in number of seconds to stop running as the music ends however, the result was different. In my first trial, I attempted to declare the MP3 player in the "button.isPressed," thinking that it will be easier since it controls the motors as well. By initializing the MP3 track in the scope, it started to interfer with motor's functionalities in the program because the motors never started when pressing the button. By knowing that flaw, I thought that the MP3 player can be initialized from the motors' movements instead. From this second trial, 

### Sources:
