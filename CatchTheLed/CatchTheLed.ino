#include <EnableInterrupt.h>
#include <avr/sleep.h>
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

#define START_WAIT 2000
#define TIME_SEQ_DISPLAY 4000
#define TIME_TO_INSERT 10000

#define DIFFICULTY_MODIFIER 250
#define DIFFICULTY_PROGRESS 150

// Game states
#define MENU 0
#define DISPLAY 1
#define INSERT 2
#define PENALITY 3
#define SLEEP 4

// Buttons pin position
int buttonPin[] = {B1_PIN, B2_PIN, B3_PIN, B4_PIN};

// Green leds pin position
int lnPin[] = {L1_PIN, L2_PIN, L3_PIN, L4_PIN};

// Current game state
int currentState;
int currentTimeSeqDisplay;
int currentTimeToInsert;
int systemTimeAfterDisplay;

// Boolean for checking leds status
int* lnStatus;
// Memorize pattern
int* lnPattern;

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

  currentState = MENU;
  systemTimeAfterDisplay = 0;
  currentTimeSeqDisplay = TIME_SEQ_DISPLAY;
  currentTimeToInsert = TIME_TO_INSERT;
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
    case DISPLAY:
      int timeSeqDisplay = currentTimeSeqDisplay-DIFFICULTY_MODIFIER*get_difficulty();

      delay(START_WAIT);
      generate_pattern(lnPattern);
      for(int i=0; i<4; i++){
        set_led(lnStatus, lnPin, i, lnPattern[i]);
      }
      delay(timeSeqDisplay);
      for(int i=0; i<4; i++){
        set_led(lnStatus, lnPin, i, 0);
      }

      currentState = INSERT;
      systemTimeAfterDisplay = millis();
      break;
    case INSERT:
      int timeToInsert = currentTimeToInsert-DIFFICULTY_MODIFIER*get_difficulty();

      if(millis() - systemTimeAfterDisplay >= timeToInsert){
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
      break;
  }
}

void wakeUp(){}


/*
void loop(){
 Serial.println("GOING IN POWER DOWN IN 1s ...");
 Serial.flush();
 delay(1000);
 
 set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
 sleep_enable();
 sleep_mode(); 
 Serial.println("WAKE UP");
 sleep_disable(); 
 */
