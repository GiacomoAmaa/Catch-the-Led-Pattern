#include <stdlib.h>
#include <Arduino.h>


/*
makes the specified pin fade
*/
void pin_fade(int pin);

/*
Resets the given pattern
*/
void reset_pattern(int* led_pattern);

/*
Generates a random led pattern
*/
void generate_pattern(int* led_pattern);