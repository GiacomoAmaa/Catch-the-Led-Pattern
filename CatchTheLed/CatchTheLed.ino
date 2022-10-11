#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include "Potentiometer.h"
#include "Leds.h"
#include "Buttons.h"
#include "Utility.h"


// Potentiometer
#define POT_PIN A0

// Red led pins
#define LS_PIN 11
// Green led pins
#define L1_PIN 13
#define L2_PIN 12
#define L3_PIN 10
#define L4_PIN 9

// Button pins
#define B1_PIN 5
#define B2_PIN 4
#define B3_PIN 3
#define B4_PIN 2

// Time constants in ms
#define TIME_BEFORE_SLEEP = 10000
#define T1 2000
#define T2 4000
#define T3 10000

// Game states
#define MENU 0
#define SEQUENCE 1
#define INSERT 2
#define PENALITY 3
#define SLEEP 4

// Buttons pin position
int buttonPin[] = {B1_PIN, B2_PIN, B3_PIN, B4_PIN};

// Green leds pin position
int lnPin[] = {L1_PIN, L2_PIN, L3_PIN, L4_PIN};

// Current game state
int currentState;

// Current timer count
int timer;

// Boolean for checking leds status
int* lnStatus;

// Memorize pattern
int* lnPattern;


static void setLed(int led_index, int status){
  if(status < 0 || status > 1){
    Serial.println("Error: invalid led status.");
    return;
  }

  if(lnStatus[led_index] != status){
    lnStatus[led_index] = status;
    digitalWrite(lnPin[led_index], status ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LS_PIN, OUTPUT);

  setup_rng();

  lnStatus = (int*)malloc(sizeof(int)*4);
  lnPattern = (int*)malloc(sizeof(int)*4);
  for(int i=0; i<4; i++){
    lnStatus[i] = 0;
    lnPattern[i] = -1;
    pinMode(lnPin[i], OUTPUT);
    pinMode(buttonPin[i], INPUT);
  }

  currentState = 0;
  timer = 0;
}

void loop() {
  switch(currentState){
    case MENU:
      potentiometer_handler(POT_PIN);
      pin_fade(LS_PIN);

      /* TODO
      timer che va in background quando passano 10 secondi manda a nanna.
       reset timer dopo nanna  e dopo chg game mode reset
      */

      break;
    case SEQUENCE:
      delay(T1);
      generate_pattern(lnPattern);
      for(int i=0; i<4; i++){
        setLed(i, lnPattern[i]);
      }
      delay(T2);
      for(int i=0; i<4; i++){
        setLed(i, 0);
      }
      currentState = INSERT;
      timer = millis();
      break;
    case INSERT:
      if(millis() - timer >= T3){
        currentState = PENALITY;
        break;
      }
      // controllo pressione bottoni
      break;
    case PENALITY:
      digitalWrite(LS_PIN, HIGH);
      Serial.println("Penality!");
      delay(1000);
      digitalWrite(LS_PIN, LOW);
      currentState = MENU;
      break;
    case SLEEP:
      sleep();
      break;
  }
}

