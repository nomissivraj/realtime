#include <Adafruit_NeoPixel.h>

//define NeoPixel Pins and Number of LEDs
#define PIN4 4
#define PIN2 2
#define PIN3 3
#define NUM_LEDS 16

//create NeoPixel strips
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS, PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LEDS, PIN3, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;

int ledState1, ledState2, ledState3 = 0;
int trigPin1 = 12;    // Trigger
int echoPin1 = 13;    // Echo
long duration1;
int delay1;

int trigPin2 = 10;    // Trigger
int echoPin2 = 11;    // Echo
long duration2;
int delay2;

int trigPin3 = 8;    // Trigger
int echoPin3 = 9;    // Echo
long duration3;
int delay3;

int nextTime1 = 10;  // Do this every 10 milliseconds
int nextTime2 = 20;  // Do this every 20 milliseconds
int nextTime3 = 30;  // Do this every 30 milliseconds

int nextSerialTime1 = 1000;
int nextSerialTime2 = 1000;
int nextSerialTime3 = 1000;


long int goTime1, goTime2, goTime3, serialTime1, serialTime2, serialTime3;

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  // start the strip1 and blank it out
  strip1.begin();
  strip1.show();
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  // start the strip1 and blank it out
  strip2.begin();
  strip2.show();
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  // start the strip1 and blank it out
  strip3.begin();
  strip3.show();
  
  goTime1 = millis();
  goTime2 = millis();
  goTime3 = millis();

  serialTime1 = millis();
  serialTime2 = millis();
  serialTime3 = millis();

  Serial.begin(9600);
}

void loop() {
  if(millis() >= goTime1) {
    functionGo1();
    if (millis() >= serialTime1) {
      Serial.print("Sensor_1: ");
      Serial.print(duration1);
//      Serial.print(map (duration1, 400, 13000, 0, 100));
      Serial.println();
      serialTime1 = millis() + nextSerialTime1;
    }
  }
  
  if(millis() >= goTime2) {
    functionGo2();
//    if (millis() >= serialTime2) {
//      Serial.begin(9600);
//      Serial.print("Sensor_2: ");
////      Serial.print(duration2);
//      Serial.print(map (duration2, 450, 27000, 0, 100));
//      Serial.println();
//      Serial.end();
//      serialTime2 = millis() + nextSerialTime2;
//    }
  }
  
  if(millis() >= goTime3) {
    functionGo3();
//    if (millis() >= serialTime3) {
//      Serial.begin(9600);
//      Serial.print("Sensor_3: ");
////      Serial.print(duration3);
//      Serial.print(map (duration3, 270, 27000, 0, 100));
//      Serial.println();
//      Serial.end();
//      serialTime3 = millis() + nextSerialTime3;
//    }
  }
}

// Ring 1
void functionGo1 () {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  delay1 = map (duration1, 500, 142000, 30, 3000);
  unsigned long currentMillis1 = millis();

  if (currentMillis1 - previousMillis1 >= delay1) {
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
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  delay2 = map (duration2, 450, 27000, 30, 3000);
  unsigned long currentMillis2 = millis();

  if (currentMillis2 - previousMillis2 >= delay2) {
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
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  delay3 = map (duration3, 270, 27000, 30, 3000);
  unsigned long currentMillis3 = millis();

  if (currentMillis3 - previousMillis3 >= delay3) {
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
