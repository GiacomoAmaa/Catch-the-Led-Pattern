#include "Utility.h"
#include <time.h>
#include <stdlib.h>

#define TIME_BEFORE_END 10000

unsigned long timerCount = 0;

void setup_rng(){
  srand(time(NULL));
}

int rng(int max_range){
  return rand() % max_range;
}

void sleep(){
  Serial.println("Going to sleep... PRESS ANY BUTTON TO WAKE ME UP");
  delay(100);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
}

int array_contains(int* array, int length, int value){
  for(int i=0; i<length; i++){
    if(array[i]==value){
      return 1;
    }
  }
  return 0;
}
