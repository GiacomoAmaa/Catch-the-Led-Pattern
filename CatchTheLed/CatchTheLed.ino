#include "TimerOne.h"
#include "EnableInterrupt.h"

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
      Serial.println(get_difficulty());
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

int diffScaler[] = {256, 512, 768, 1024};
int diff = 1;
int currIntensity = 0;
int fadeAmount = 5;

void set_difficulty(int newVal){
    for (int i = 0; i < 4; i++){
        if(newVal < diffScaler[i]){
            diff = i + 1;
            break;
        }
    }
}

int get_difficulty(){
    return diff;
}

void fade(){
  currIntensity += fadeAmount;
  if (currIntensity == 0 || currIntensity == 255) {
    fadeAmount = -fadeAmount ; 
  }
}

int get_intensity(){
  return currIntensity;
}

