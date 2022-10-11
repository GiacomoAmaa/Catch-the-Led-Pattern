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