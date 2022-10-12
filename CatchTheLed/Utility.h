#include <Arduino.h>
#include <time.h>
#include <avr/sleep.h>

/*
Sets the seed for rng numbers
*/
void setup_rng();

/*
Generates a random number in the given interval
*/
int rng(int max_range);

/*
Sends endgame message
*/
void end_game(int score);

/*
Activates sleep mode 
*/
void sleep();

/*
Returns true if the given array contains the specified value
*/
int array_contains(int* array, int value);

/*
Returns the position of the element that is equal to the given value or -1
*/
//int find_position(int* array, int length, int value);
