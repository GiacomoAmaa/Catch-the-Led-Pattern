#include "Leds.h"

// Led brightness intensity
int currIntensity = 0;

// Intensity change factor
int fadeAmount = 5;


static void fade(){
  currIntensity += fadeAmount;
  if (currIntensity == 0 || currIntensity == 255) {
    fadeAmount = -fadeAmount ; 
  }
}

void pin_fade(int pin){
  analogWrite(pin, currIntensity);
  fade();
  delay(20);
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
