#include <time.h>
#include <stdlib.h>

/*
Sets the difficulty level based on the given value
*/
int set_difficulty(int NewVal);

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
Generates a random led pattern
*/
void generate_pattern(int* led_pattern);