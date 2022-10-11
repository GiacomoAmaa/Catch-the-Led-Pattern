#include "support.h"

// Mapper for analog values in 4 difficulty levels
int diffScaler[] = {256, 512, 768, 1024};

// Current difficulty
int diff = 1;

// Led brightness intensity
int currIntensity = 0;

// Intensity change factor
int fadeAmount = 5;


int set_difficulty(int newVal){
  int i;
  for (i = 0; i < 4; i++){
      if(newVal < diffScaler[i]){
          return i + 1;
        }
  }
  return i;
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

void setup_rng(){
  srand(time(NULL));
}

void reset_pattern(int* led_pattern){
  for(int i=0; i<4; i++){
    led_pattern[i] = -1;
  }
}

void generate_pattern(int* led_pattern){
  for(int i=0; i<4; i++){
    led_pattern[i] = rand() % 2;
  }
}
