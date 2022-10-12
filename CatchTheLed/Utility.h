#include <Arduino.h>
#include <time.h>
#include <avr/sleep.h>

/*
Sets the seed for rng numbers
*/
void setup_rng();

int rng(int max_range);

/*
Sends endgame message
*/
void end_game(int score);

/*
Sets the seed for rng numbers
*/
void setup_rng();

/*
Activates sleep mode 
*/
void sleep();

int array_contains(int* array, int value);

//int find_position(int* array, int length, int value);