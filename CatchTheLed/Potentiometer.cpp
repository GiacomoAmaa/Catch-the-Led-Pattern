#include "Potentiometer.h"

// Mapper for analog values in 4 difficulty levels
int diffScaler[] = {256, 512, 768, 1024};

// Current difficulty
int diff = 1;

int set_difficulty(int newVal){
  int i;
  for (i = 0; i < 4; i++){
      if(newVal < diffScaler[i]){
          return i + 1;
        }
  }
  return i;
}