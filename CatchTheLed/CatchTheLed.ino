#define EI_ARDUINO_INTERRUPTED_PIN

#include <avr/sleep.h>
#include "Potentiometer.h"
#include "Leds.h"
#include "Buttons.h"
#include "Utility.h"
#include <EnableInterrupt.h>

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
#define TIME_BEFORE_SLEEP 10000

#define START_WAIT_RANGE 2000
#define TIME_SEQ_DISPLAY 4000
#define TIME_TO_INSERT 10000

#define DIFF_MODIFIER 250
#define DIFF_PROG_MODIFIER 50
#define DIFF_PROGRESS 150

#define ERRORS_ALLOWED 3

#define DELAY_TIME_PRESS 30

// Game states
#define MENU 0
#define DISPLAY 1
#define INSERT 2
#define PENALITY 3
#define SLEEP 4

// Buttons pin position
uint8_t buttonPin[] = {B1_PIN, B2_PIN, B3_PIN, B4_PIN};

// Green leds pin position
uint8_t lnPin[] = {L1_PIN, L2_PIN, L3_PIN, L4_PIN};

volatile int currentState;
unsigned long currentTimeSeqDisplay;
unsigned long currentTimeToInsert;
unsigned long systemTimeAfterDisplay;
unsigned long systemTimeIdling;

// Boolean for checking leds status
int* lnStatus;
// Memorize pattern
volatile int* lnPattern;
volatile int* lnPressed;
volatile int pressed;

int errors;
int score;

void setup() {
  Serial.begin(9600);
  pinMode(LS_PIN, OUTPUT);

  setup_rng();

  lnStatus = (int*)malloc(sizeof(int)*4);
  lnPattern = (int*)malloc(sizeof(int)*4);
  lnPressed = (int*)malloc(sizeof(int)*4);
  for(int i=0; i<4; i++){
    lnStatus[i] = 0;
    lnPattern[i] = -1;
    lnPressed[i] = 0;
    pinMode(lnPin[i], OUTPUT);
    pinMode(buttonPin[i], INPUT);
    enableInterrupt(buttonPin[i], button_on_press, RISING);
  }

  currentState = MENU;

  currentTimeSeqDisplay = TIME_SEQ_DISPLAY;
  currentTimeToInsert = TIME_TO_INSERT;
  systemTimeAfterDisplay = 0;
  systemTimeIdling = 0;

  errors = 0;
  score = 0;

  pressed = 0;
  generate_pattern(lnPattern);
}

void button_on_press(){

  int interruptedPin = arduinoInterruptedPin;
  int indexInterrupted = find_position((int*)buttonPin, 4, interruptedPin);

  if(currentState == MENU && interruptedPin == B1_PIN){
    currentState = DISPLAY;
  } else if(currentState == DISPLAY) {
    Serial.println("You pressed a button too early!");
    currentState = PENALITY;
  } else if(currentState == INSERT) { 
    /********in insert quando premi il bottone si deve accendere anche il led corrispondente**************/
    if (lnPattern[indexInterrupted] == 0){
      Serial.println("This led was not lighten up!");
      currentState = PENALITY;
    } else {
      lnPressed[indexInterrupted] = 1;
      pressed = 1;
    }
  }

  // delay implemented for avoiding the bouncing
  delay(DELAY_TIME_PRESS);
}

void changeState(int newState){
  if(newState >= 0 && newState <= 4){
    noInterrupts();
    currentState = newState;
    interrupts();
  }
}

void reset(){
  reset_pattern(lnPattern, lnPressed);
  errors = 0;
  score = 0;
  currentTimeSeqDisplay = TIME_SEQ_DISPLAY;
  currentTimeToInsert = TIME_TO_INSERT;
  systemTimeAfterDisplay = 0;
  systemTimeIdling = 0;
  changeState(MENU);
}

void loop() {
  if(currentState == MENU){
    systemTimeIdling = systemTimeIdling == 0 ? millis() : systemTimeIdling;
    say_welcome();
    potentiometer_handler(POT_PIN);
    pin_fade(LS_PIN);
    if(millis() - systemTimeIdling >= TIME_BEFORE_SLEEP){
      changeState(SLEEP);
      systemTimeIdling = 0;
      reset_salute();
      led_write(LS_PIN, LOW);
    }
  }
  else if(currentState == DISPLAY){
    int timeSeqDisplay = currentTimeSeqDisplay - DIFF_MODIFIER * get_difficulty();
    delay(rng(START_WAIT_RANGE));
    apply_led_status(lnStatus, lnPin, lnPattern);
    delay(timeSeqDisplay);
    reset_led_status(lnStatus, lnPin);
    changeState(INSERT);
    systemTimeAfterDisplay = millis();
  }
  else if(currentState == INSERT){
    int timeToInsert = currentTimeToInsert-DIFF_MODIFIER*get_difficulty();

    apply_led_status(lnStatus, lnPin, lnPressed);

    if(millis() - systemTimeAfterDisplay >= timeToInsert){
      changeState(PENALITY);
    } else if(check_score(lnPattern, lnPressed) == 1){
      score++;
      Serial.println("New point! Score: " + String(score));
      currentTimeToInsert -= DIFF_PROGRESS + DIFF_PROG_MODIFIER*get_difficulty();
      currentTimeSeqDisplay -= DIFF_PROGRESS + DIFF_PROG_MODIFIER*get_difficulty();
      reset_pattern(lnPattern, lnPressed);
      changeState(DISPLAY);
    }
  }
  else if(currentState == PENALITY){
      reset_led_status(lnStatus, lnPin);

      led_write(LS_PIN, HIGH);
      Serial.println("Penality!");
      delay(1000);
      led_write(LS_PIN, LOW);

      errors++;
      if(errors >= ERRORS_ALLOWED){
        /** VA SPAMMATO PER 10 SEC NON INVIATO E POI ASPETTA 10 SEC**/
        Serial.println("Game Over. Final score: " + String(score));
        delay(10000);
        reset();
      } else {
        changeState(DISPLAY);
      }
  }
  else if(currentState == SLEEP){
    sleep();
    changeState(MENU);
  }
  
}

