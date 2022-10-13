#include <stdlib.h>
#include <Arduino.h>

/*
Makes the specified pin fade
*/
void led_fade(uint8_t pin);

/*
Switches on/off the specified pin and updates the logical led map
*/
void set_led(int* lnStatus, int* lnPin, int led_index, int status);

/*
Generates a random led pattern
*/
void generate_pattern(volatile int* led_pattern);

/*
Resets the given pattern
*/
void reset_pattern(volatile int* led_pattern, volatile int* led_pressed);

/*
Switches off all leds and updates the logical led map
*/
void reset_led_status(int* lnStatus, uint8_t* lnPin);

/*
Inserts a given
*/
void apply_led_status(int* lnStatus, uint8_t* lnPin, volatile int* lnPattern);

/*
Checks if the pressed button is correct
*/
int check_score( volatile int* pattern, volatile int* pressed);
 