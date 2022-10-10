#include "TimerOne.h"
#include "EnableInterrupt.h"
#include "support.h"

#define POT_PIN A0
#define LS_PIN 11

int potValue;
enum game_state {MENU,START,SLEEP};
int currentState;

void setup() {
 Serial.begin(9600);
 currentState = 0;
 potValue = 0;
 pinMode(LS_PIN, OUTPUT); 
}

void loop() {
  switch(currentState){
    case MENU:
    int potNewValue = analogRead(POT_PIN);
    if(potValue != potNewValue ){
      set_difficulty(potNewValue);
      Serial.println(String(get_difficulty()));
    }
    analogWrite(LS_PIN, get_intensity()); 
    fade();
    delay(20); 

    break;
    case START: 
    break;
    case SLEEP: 
    break;
  }
}
