#include "Utility.h"

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

void sleep(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  Serial.println("WAKE UP");
  sleep_disable();
}

void wakeUp(){}