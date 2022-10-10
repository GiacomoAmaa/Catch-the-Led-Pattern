#include "TimerOne.h"
#include "EnableInterrupt.h"
#include "support.c"

#define POT_PIN A0
#define DIFF_SCALE 256

int potValue;
int difficulty;
enum game_state {MENU,START,SLEEP};
int currentState;

void setup() {
 Serial.begin(9600);
 currentState = 0;
 potValue = 0;
 difficulty = 0;
}

void loop() {
  switch(currentState){
    case MENU:
    potHandler();

    break;
    case START: 
    break;
    case SLEEP: 
    break;
  }
}

