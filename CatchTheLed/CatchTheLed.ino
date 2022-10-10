#include "TimerOne.h"
#include "EnableInterrupt.h"
#include "support.h"

#define POT_PIN A0
#define LS_PIN 13
#define L1_PIN 12
#define L2_PIN 11
#define L3_PIN 10
#define L4_PIN 9

#define T1 2000
#define T2 4000
#define T3 10000

#define MENU 0
#define SEQUENCE 1
#define INSERT 2
#define PENALITY 3
#define SLEEP 4

int potValue;
int currentState;
int timer;

// Green leds pin position
int lnPin[4];

// Boolean for checking leds status
int* lnStatus;

// Memorize pattern
int* lnPattern;

void setup() {
  Serial.begin(9600);
  pinMode(LS_PIN, OUTPUT);

  setup_rng();

  lnPin[0] = L1_PIN;
  lnPin[1] = L2_PIN;
  lnPin[2] = L3_PIN;
  lnPin[3] = L4_PIN;

  lnStatus = (int*)malloc(sizeof(int)*4);
  lnPattern = (int*)malloc(sizeof(int)*4);
  for(int i=0; i<4; i++){
    lnStatus[i] = 0;
    lnPattern[i] = -1;
  }

  currentState = 0;
  potValue = 0;
  timer = 0;
}

void setLed(int led_index, int status){
  if(status < 0 || status > 1){
    Serial.println("Error: invalid led status.");
    return;
  }

  if(lnStatus[led_index] != status){
    lnStatus[led_index] = status;
    digitalWrite(lnPin[led_index], status ? HIGH : LOW);
  }
}

void loop() {
  switch(currentState){
    case MENU:
      int potNewValue = analogRead(POT_PIN);
      if(potValue != potNewValue ){
        set_difficulty(potNewValue);
        Serial.println(String(get_difficulty()));
      }
      analogWrite(LS_PIN, get_intensity()); 
      fade();
      delay(20); 

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
      break;
  }
}
