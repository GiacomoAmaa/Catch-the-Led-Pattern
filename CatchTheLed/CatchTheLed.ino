#include "TimerOne.h"
#include "EnableInterrupt.h"
#include "support.c"

#define POT_PIN A0


int difficulty;
int potValue;
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
    int potNewValue = anlogRead(POT_PIN);
    if(potValue != potNewValue ){
      set_diff(potNewValue);
    }

    break;
    case START: 
    break;
    case SLEEP: 
    break;
  }
}

