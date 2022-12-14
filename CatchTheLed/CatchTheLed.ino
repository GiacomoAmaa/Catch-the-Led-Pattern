#define EI_ARDUINO_INTERRUPTED_PIN

#include <avr/sleep.h>
#include "Potentiometer.h"
#include "Leds.h"
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
// time between sequences
#define START_WAIT_RANGE 2000
#define MINIMUM_WAIT_TIME 300
// combination show time
#define TIME_SEQ_DISPLAY 4000
#define MINIMUM_SEQ_TIME 1000
// time to insert the sequence
#define TIME_TO_INSERT 7000
#define MINIMUM_INSERT_TIME 2300
// modifiers in ms
#define DIFF_MODIFIER 200
#define DIFF_PROG_MODIFIER 30

// time to wait for a new game to start
#define END_GAME_WAIT 10000

// utility
#define ERRORS_ALLOWED 3
#define DELAY_BUTTON_PRESS 30

// Game states
#define MENU 0
#define SEQUENCE 1
#define INSERT 2
#define PENALITY 3
#define SLEEP 4

// Buttons pin position
uint8_t buttonPin[] = { B1_PIN, B2_PIN, B3_PIN, B4_PIN };

// Green leds pin position
uint8_t lnPin[] = { L1_PIN, L2_PIN, L3_PIN, L4_PIN };

int timeReduction[] = {0, 200, 400, 800};

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

int errors;
int score;
int sent;

void setup() {
  Serial.begin(9600);
  pinMode(LS_PIN, OUTPUT);

  setup_rng();

  lnStatus = (int*)malloc(sizeof(int) * 4);
  lnPattern = (int*)malloc(sizeof(int) * 4);
  lnPressed = (int*)malloc(sizeof(int) * 4);
  for (int i = 0; i < 4; i++) {
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
  sent = 0;

  generate_pattern(lnPattern);
}

void button_on_press() {

  int interruptedPin = arduinoInterruptedPin;
  int indexInterrupted = -1;
  for (int i = 0; i < 4; i++) {
    if (buttonPin[i] == interruptedPin) {
      indexInterrupted = i;
      break;
    }
  }
  if (indexInterrupted < 0) {
    Serial.println("Error: cant find interrupted pin index.");
    return;
  }


  if (currentState == MENU && interruptedPin == B1_PIN) {
    sent = 0;
    digitalWrite(LS_PIN, LOW);
    currentState = SEQUENCE;
  } else if (currentState == SEQUENCE) {
    Serial.println("You pressed a button too early!");
    currentState = PENALITY;
  } else if (currentState == INSERT) {
    if (lnPattern[indexInterrupted] == 0) {
      Serial.println("This led was not lighten up!");
      currentState = PENALITY;
    } else {
      lnPressed[indexInterrupted] = 1;
    }
  }
  // delay implemented for avoiding the bouncing
  delay(DELAY_BUTTON_PRESS);
}

void decrease_time(){
  currentTimeSeqDisplay -= DIFF_PROG_MODIFIER * get_difficulty();
  currentTimeToInsert -= DIFF_PROG_MODIFIER * get_difficulty();

  if( currentTimeSeqDisplay < MINIMUM_SEQ_TIME ){
    currentTimeSeqDisplay = MINIMUM_SEQ_TIME ;
  }
  if( currentTimeToInsert < MINIMUM_INSERT_TIME ){
    currentTimeToInsert = MINIMUM_INSERT_TIME ;
  }
}

void changeState(int newState) {
  if (newState >= 0 && newState <= 4) {
    noInterrupts();
    currentState = newState;
    interrupts();
  }
}

void reset() {
  reset_pattern(lnPattern, lnPressed);
  errors = 0;
  score = 0;
  sent = 0;
  currentTimeSeqDisplay = TIME_SEQ_DISPLAY;
  currentTimeToInsert = TIME_TO_INSERT;
  systemTimeAfterDisplay = 0;
  systemTimeIdling = 0;
  changeState(MENU);
}

void loop() {
  if (currentState == MENU) {

    if (!sent) {
      Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
      sent = 1;
    }
    systemTimeIdling = systemTimeIdling == 0 ? millis() : systemTimeIdling;
    potentiometer_handler(POT_PIN, &systemTimeIdling);
    led_fade(LS_PIN);
    
    if (millis() - systemTimeIdling >= TIME_BEFORE_SLEEP) {
      changeState(SLEEP);
      systemTimeIdling = 0;
      sent = 0;
      digitalWrite(LS_PIN, LOW);
    }

  } else if (currentState == SEQUENCE) {

    if (!sent) {
      Serial.println("GO !");
      sent = 1;
    }
    unsigned long timeSeqDisplay = currentTimeSeqDisplay - timeReduction[get_difficulty() - 1];
    delay(rng(START_WAIT_RANGE) + MINIMUM_WAIT_TIME);
    apply_led_status(lnStatus, lnPin, lnPattern);
    delay(timeSeqDisplay);
    reset_led_status(lnStatus, lnPin);
    if (currentState == SEQUENCE) {
      changeState(INSERT);
    }
    systemTimeAfterDisplay = millis();

  } else if (currentState == INSERT) {

    unsigned long timeToInsert = currentTimeToInsert - timeReduction[get_difficulty() - 1];
    apply_led_status(lnStatus, lnPin, lnPressed);
    if (millis() - systemTimeAfterDisplay >= timeToInsert) {
      if (check_score(lnPattern, lnPressed)) {
        score++;
        Serial.println("New point! Score: " + String(score));
        decrease_time();
        reset_led_status(lnStatus, lnPin);
        reset_pattern(lnPattern, lnPressed);
        changeState(SEQUENCE);
      } else {
        reset_pattern(lnPattern, lnPressed);
        Serial.println("Too Slow!");
        changeState(PENALITY);
      }
    }

  } else if (currentState == PENALITY) {

    //switch off green leds
    reset_led_status(lnStatus, lnPin);
    //switch on red button for 1 sec
    digitalWrite(LS_PIN, HIGH);
    Serial.println("Penality!");
    delay(1000);
    digitalWrite(LS_PIN, LOW);
    //when too many errors have been commited the game ends
    errors++;
    if (errors >= ERRORS_ALLOWED) {
      Serial.println("Game Over. Final score: " + String(score));
      delay(END_GAME_WAIT);
      reset();
    } else {
      changeState(SEQUENCE);
    }

  } else if (currentState == SLEEP) {
    sleep();
    changeState(MENU);
  }
}
