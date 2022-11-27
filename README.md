# Project Features

Data obtained from a small database stored on an embedded system (simulating data received from an external device) are to be subjected to a processing task. 

The data processing operation should be repeated precisely every 250ms, but is to be slowed to every 500ms when the user button is pressed, when the button is pressed again, the program should go back to being processed every 250ms. 

The orange LEDs should turn on if the result of the processing is zero, the blue LEDs should turn on if the result of the processing is more than 500. Otherwise, all four LEDs should be off. The user button shall be read using an interrupt service routine. 

The two red LEDs on the board should light when processing is slowed. The results of the processing calculations are to be placed in a location in memory from which they are to be deleted every 250ms (simulating removal to an external device). 

The rate of deletion should become 500ms when processing is slowed. 

The green LEDs should toggle when data has been deleted.

- Target Board - STM32 Discovery
- Hardware interrupts implemented
- Shared resources Protector

# UML Design Diagrams

![alt text](https://github.com/[username]/[reponame]/blob/[branch]/image.jpg?raw=true)
