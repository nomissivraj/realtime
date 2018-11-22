#include <Adafruit_NeoPixel.h>

//define NeoPixel Pins and Number of LEDs
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define NUM_LEDS 16

//create NeoPixel strips
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LEDS, PIN3, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;

int ledState1, ledState2, ledState3 = 0;
int trigPin1 = 12;    // Trigger
int echoPin1 = 13;    // Echo
long duration1;

int trigPin2 = 10;    // Trigger
int echoPin2 = 11;    // Echo
long duration2;

int trigPin3 = 8;    // Trigger
int echoPin3 = 9;    // Echo
long duration3;

int nextTime1 = 10; // Do this every 100 milliseconds
int nextTime2 = 20;  // Do this every 50 milliseconds
int nextTime3 = 30;  // Do this every 50 milliseconds


long int goTime1, goTime2, goTime3;

void setup() {
//  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  // start the strip and blank it out
  strip1.begin();
  strip1.show();
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  // start the strip and blank it out
  strip2.begin();
  strip2.show();
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  // start the strip and blank it out
  strip3.begin();
  strip3.show();
  goTime1 = millis();
  goTime2 = millis();
  goTime3 = millis();
}

void loop() {
  if(millis() >= goTime1) functionGo1();
  if(millis() >= goTime2) functionGo2();
  if(millis() >= goTime3) functionGo3();
}

// Ring 1
void functionGo1 () {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  unsigned long currentMillis1 = millis();

  if (currentMillis1 - previousMillis1 >= map (duration1, 300, 20000, 50, 4000)) {
    // save the last time you blinked the LED
    previousMillis1 = currentMillis1;

    // if the LED is off turn it on and vice-versa:
    if (ledState1 == 0) {
      ledState1 = 1;
      for(int i = 0; i < NUM_LEDS; i++ ) {
        strip1.setPixelColor(i, 0, 0, 255); 
      }
      strip1.show();
    } else {
      ledState1 = 0;
      for(int i = 0; i < NUM_LEDS; i++ ) {
        strip1.setPixelColor(i, 0, 0, 0); 
      }
      strip1.show();
    }
  } goTime1 = millis() + nextTime1;
}

// Ring 2
void functionGo2 () {
//  Serial.print(duration2);
//  Serial.println();
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  unsigned long currentMillis2 = millis();

  if (currentMillis2 - previousMillis2 >= map (duration2, 300, 20000, 50, 4000)) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis2;

    // if the LED is off turn it on and vice-versa:
    if (ledState2 == 0) {
      ledState2 = 1;
      for(int i = 0; i < NUM_LEDS; i++ ) {
        strip2.setPixelColor(i, 255, 0, 0); 
      }
      strip2.show();
    } else {
      ledState2 = 0;
      for(int i = 0; i < NUM_LEDS; i++ ) {
        strip2.setPixelColor(i, 0, 0, 0); 
      }
      strip2.show();
    } 
  } goTime2 = millis() + nextTime2;
}

// Ring 3
void functionGo3 () {
//  Serial.print(duration3);
//  Serial.println();
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  unsigned long currentMillis3 = millis();

  if (currentMillis3 - previousMillis3 >= map (duration3, 300, 20000, 50, 4000)) {
    // save the last time you blinked the LED
    previousMillis3 = currentMillis3;

    // if the LED is off turn it on and vice-versa:
    if (ledState3 == 0) {
      ledState3 = 1;
      for(int i = 0; i < NUM_LEDS; i++ ) {
        strip3.setPixelColor(i, 0, 255, 0); 
      }
      strip3.show();
    } else {
      ledState3 = 0;
      for(int i = 0; i < NUM_LEDS; i++ ) {
        strip3.setPixelColor(i, 0, 0, 0); 
      }
      strip3.show();
    } 
  } goTime3 = millis() + nextTime3;
}
