#include "Leds.h"
#include <Arduino.h>

// Led brightness intensity
int currIntensity = 0;

// Intensity change factor
int fadeAmount = 5;


void fade(){
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

void set_led(int* lnStatus, int* lnPin, int led_index, int status){
  if(status < 0 || status > 1){
    Serial.println("Error: invalid led status.");
    return;
  }

  if(lnStatus[led_index] != status){
    lnStatus[led_index] = status;
    digitalWrite(lnPin[led_index], status ? HIGH : LOW);
  }
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
