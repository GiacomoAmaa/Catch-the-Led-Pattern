#include "Leds.h"
#include "Utility.h"
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

void led_fade(uint8_t pin){
  analogWrite(pin, currIntensity);
  fade();
  delay(20);
}

void set_led(int* lnStatus, uint8_t* lnPin, int led_index, int status){
  if(status < 0 || status > 1){
    Serial.println("Error: invalid led status.");
    return;
  }

  if(lnStatus[led_index] != status){
    lnStatus[led_index] = status;
    digitalWrite(lnPin[led_index], status ? HIGH : LOW);
  }
}

void generate_pattern(volatile int* led_pattern){
  for(int i=0; i<4; i++){
    led_pattern[i] = rng(2);
  }
}

void reset_pattern(volatile int* led_pattern, volatile int* led_pressed){
  for(int i=0; i<4; i++){
    led_pressed[i] = 0;
  }
  generate_pattern(led_pattern);
}

void reset_led_status(int* lnStatus, uint8_t* lnPin){
  noInterrupts();
  for(int i = 0; i < 4; i++){
    set_led(lnStatus, lnPin, i, 0);
  }
  interrupts();
}

void apply_led_status(int* lnStatus, uint8_t* lnPin, volatile int* lnPattern){
  noInterrupts();
  for(int i=0; i<4; i++){
    set_led(lnStatus, lnPin, i, lnPattern[i]);
  }
  interrupts();
}

int check_score(volatile int* pattern, volatile int* pressed){
  for(int i=0; i<4; i++){
    if(pattern[i] != pressed[i]) {
      return 0;
    }
  }
  return 1;
}
