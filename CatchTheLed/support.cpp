#include "support.h"
#include <time.h>
#include <stdlib.h>

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
