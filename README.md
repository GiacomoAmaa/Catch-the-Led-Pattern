Embedded System and IoT  - a.y. 2022-2023

v1.0 - 20221001

Assignment #1 - Catch the Led Pattern!

We want to realise an embedded system implementing a game called Catch the Led Pattern!. 

Description 

The game board is based on 4 green leds L1, L2, L3, L4 and red led LS, four tactile buttons T1, T2, T3, T4 and a potentiometer Pot, displaced in the following layout:

 

During the game, repeatedly the leds L1…L4 are first turned off for some random time T1, and then turned on according to some random configuration or pattern (called here pattern). An example of pattern is:  L1 and L3 on, L2 and L4 off. After some  time T2  the leds are turned off and the player must recreate the pattern by pressing the corresponding buttons T1…T4 within some time T3. Each button Ti turns on the corresponding led Li. If the player recreates the correct pattern on time, the score is increased and the game goes on, by reducing the times T2 and T3 of some factor F.  If the player does not recreate the correct pattern on time,  she/he gets a penalty. The penalty is signalled by the red led Ls is turned on for 1 second. After three penalties the game ends and the score is displayed on the serial line. 

Game detailed behaviour 

In the initial state, all green leds are off but led LS that pulses (fading in and out), waiting for some player to start the game. On the serial line, it must be sent the message “Welcome to the Catch the Led Pattern Game. Press Key T1 to Start”. 

If/when the button T1 is pressed the game starts.  If the T1 button is not pressed within 10 seconds, the system must go in deep sleeping. The system can be awoken back  by pressing any button. Once awoken, the system goes in the initial state and the led Ls starts pulsing again. 
 
When the game starts, all leds are switched off and a “Go!” message is sent on the serial line. An initial score is set to zero.

During the game:
●	the leds L1…L4 are turned off for some random time T1 
●	the leds are then turned on according to some  random pattern, for some time T2 and then turned off again 
●	the player has max T3 time for recreating the pattern by pressing the buttons T1…T4 (each button Ti turns on the corresponding led Li)
●	the player can act only after the leds are turned off
○	if the player press buttons before, then she/he gets a penalty (see later)
●	If the player recreates the correct pattern on time, then:
○	the score is increased and a message "New point! Score: XXX" (where XXX is the current score) is sent on the serial line
○	the game goes on, by reducing the times T2 and T3 of some factor F.  
●	If the player does not recreate the correct pattern on time,  she/he gets a penalty: the red led Ls turned on for 1 second and a message "Penalty!" is sent on the serial line. 
●	After three penalties the game ends: a message "Game Over. Final Score: XXX" (where XXX is the final score) is sent on the serial line for 10 seconds, then the game restarts from the initial state.

Before starting the game, the potentiometer Pot device can be used to set the difficulty L level  which could be a value in the range 1..4 (1 easiest, 4 most difficult). The level must affect the value of the factor F (so that the more difficult the game is, the greater the factor F must be). 

________________________________________

The assignment:

●	Develop the game on the Arduino platform, implementing the embedded software in C using the Wiring framework. The game must be based on a superloop control architecture.
○	Choose concrete values for parameters in order to have the best game play. 
○	For any other aspect not specified, make the choice that you consider most appropriate.
●	The deliverable must a zipped folder assignment-01.zip including two subfolders:
○	src 
■	 including the Arduino project source code
○	doc, including
■	a representation of the schema/breadboard using tools such as   TinkerCad or Fritzing or Eagle
■	a short video (or the link to a video on the cloud) demonstrating the system

