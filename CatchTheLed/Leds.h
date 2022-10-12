#include <stdlib.h>
#include <Arduino.h>

/*
  makes the specified pin fade
*/
void pin_fade(uint8_t pin);

/*
turns on/off specified led
*/
void led_write(uint8_t pin, uint8_t state);

void set_led(int* lnStatus, int* lnPin, int led_index, int status);

/*
  Resets the given pattern
*/
void reset_pattern(int* led_pattern, int* led_pressed);

void reset_led_status(int* lnStatus, uint8_t* lnPin);

void apply_led_status(int* lnStatus, uint8_t* lnPin, int* lnPattern);

/*
  Generates a random led pattern
*/
void generate_pattern(int* led_pattern);

int check_score(int* pattern, int* pressed);