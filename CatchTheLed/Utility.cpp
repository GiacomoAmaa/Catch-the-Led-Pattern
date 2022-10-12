#include "Utility.h"
#include <time.h>
#include <stdlib.h>

// keeps track if a message has been sent or not
int sent = 0;

void setup_rng(){
  srand(time(NULL));
}

int rng(int max_range){
  return rand() % max_range;
}

void say_welcome(){
  if(!sent){
    Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
    sent++;
  }
}

void reset_salute(){
  sent = 0;
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

int find_position(int* array, int length, int value){
  int p = -1;
  for(int i = 0; i < length; i++ ){
    if(array[i] == value){
      p = i;
      break;
    }
  }
  return p;
}


