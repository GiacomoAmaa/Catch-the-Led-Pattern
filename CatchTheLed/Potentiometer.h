#include <Arduino.h>

/*
Reads the potentiometer analog value and refreshes the difficulty
*/
void potentiometer_handler(int potPin);

/*
returns difficulty
*/
int get_difficulty();