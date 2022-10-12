#include <Arduino.h>
#include <time.h>
#include <avr/sleep.h>

/*
Sets the seed for rng numbers
*/
void setup_rng();

int rng(int max_range);

/*
Prints a welcome string on the serial line
*/
void say_welcome();

/*
Allows to salute again
*/
void reset_salute();

/*
Activates sleep mode 
*/
void sleep();

int array_contains(int* array, int value);

int find_position(int* array, int length, int value);