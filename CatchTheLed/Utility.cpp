#include "Utility.h"

#include <EnableInterrupt.h>
// keeps track if a message has been sent or not
int sent = 0;

void setup_rng(){
  srand(time(NULL));
}

void say_welcome(){
  if(!sent){
    Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
    sent++;
  }
}

void wakeUp(){}

void sleep(int bp[]){
  for (int i=0; i<4; i++){
    enableInterrupt(bp[i], wakeUp, CHANGE);
  }
  enableInterrupt(5, wakeUp,CHANGE);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  for (int i=0; i<4; i++){
    disableInterrupt(bp[i]);
  }
}

int array_contains(int* array, int length, int value){
  for(int i=0; i<length; i++){
    if(array[i]==value){
      return 1;
    }
  }
  return 0;
}

int findPosition(int* buttonPin, int length, int button){
  for(int i = 0; i < length; i++){
    if(buttonsPin[i] == button){
      return i;
    }
  }
  return -1;
}

