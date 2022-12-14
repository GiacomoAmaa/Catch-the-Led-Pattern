#include <Arduino.h>

/*
Reads the potentiometer analog value and refreshes the difficulty
*/
void potentiometer_handler(int potPin, unsigned long* systemTimeIdling);

/*
Returns difficulty
*/
int get_difficulty();