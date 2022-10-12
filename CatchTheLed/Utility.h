#include <Arduino.h>
#include <time.h>
#include <avr/sleep.h>

/*
Prints a welcome string on the serial line
*/
void say_welcome();

/*
Allows to salute again
*/
void reset_salute();

/*
Sends endgame message
*/
void end_game(int score);

/*
Sets the seed for rng numbers
*/
void setup_rng();

/*
Activates sleep mode 
*/
void sleep();

int array_contains(int* array, int value);