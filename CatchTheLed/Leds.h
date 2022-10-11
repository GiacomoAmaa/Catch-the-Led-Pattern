#include <time.h>
#include <stdlib.h>
#include <Arduino.h>

/*
Calculates the next intensity value to make a led fade
*/
void fade();

/*
Returns the intensity to assign to fading led
*/
int get_intensity();

/*
Sets the seed for rng numbers
*/
void setup_rng();

/*
Resets the given pattern
*/
void reset_pattern(int* led_pattern);

/*
Generates a random led pattern
*/
void generate_pattern(int* led_pattern);