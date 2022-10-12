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
Activates sleep mode 
*/
void sleep();

/*
Returns true if the given array contains the specified value
*/
int array_contains(int* array, int value);
