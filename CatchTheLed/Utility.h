#include <Arduino.h>
#include <time.h>
#include <avr/sleep.h>

/*
Prints a welcome string on the serial line
*/
void say_welcome();

/*
Sets the seed for rng numbers
*/
void setup_rng();

/*
Activates sleep mode 
*/
void sleep(int bp[]);

int array_contains(int* array, int value);

int findPosition(int* buttonPin, int length, int button);