#include "Potentiometer.h"

// Mapper for analog values in 4 difficulty levels
int diffScaler[] = {256, 512, 768, 1024};

// Current difficulty
int diff = 1;

// Potentiometer current value
int potValue = 0;

/*
Sets the difficulty level based on the given value
*/
int set_difficulty(int newVal){
  int i;
  for (i = 0; i < 4; i++){
      if(newVal < diffScaler[i]){
          return i + 1;
        }
  }
  return i;
}

int get_difficulty(){
  return diff;
}

void potentiometer_handler(int potPin){
  int potNewValue = analogRead(potPin);
  if(potValue != potNewValue ){
    int newDiff = set_difficulty(potNewValue);
    if(newDiff != diff){
      Serial.println("Difficulty : " + String(newDiff));
      diff=newDiff;
    }
  }
}
