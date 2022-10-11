#include <stdlib.h>
#include <Arduino.h>


/*
  makes the specified pin fade
*/
void pin_fade(int pin);

/*
  Sets the seed for rng numbers
*/
void setup_rng();

void set_led(int* lnStatus, int* lnPin, int led_index, int status);

/*
  Resets the given pattern
*/
void reset_pattern(int* led_pattern, int* led_pressed);

/*
  Generates a random led pattern
*/
void generate_pattern(int* led_pattern);

int check_score(int* pattern, int* pressed);