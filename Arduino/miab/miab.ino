
#include <NewPing.h>
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

int motorDelay1;
int motorDelay2;
int motorDelay3;

long int goTime1, goTime2, goTime3, serialTime1, serialTime2, serialTime3, goTimeMotor1;

NewPing sonar1(trigPin1, echoPin1, 200); // NewPing setup of pins and maximum distance.
NewPing sonar2(trigPin2, echoPin2, 200); // NewPing setup of pins and maximum distance.
NewPing sonar3(trigPin3, echoPin3, 200); // NewPing setup of pins and maximum distance.

// the transistor which controls the motor will be attached to digital pin 9
int motorControl1 = 6;
int motorControl2 = 5;
int motorControl3 = 7;


void setup() {
  // put your setup code here, to run once:
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();
  strip3.begin();
  strip3.show();

  goTime1 = millis();
  goTime2 = millis();
  goTime3 = millis();

  goTimeMotor1 = millis();

  serialTime1 = millis();
  serialTime2 = millis();
  serialTime3 = millis();

  Serial.begin(9600);

  // make the transistor's pin an output:
  pinMode(motorControl1, OUTPUT); 
  pinMode(motorControl2, OUTPUT); 
  pinMode(motorControl3, OUTPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() >= goTime1) {
    functionGo1();
    if (millis() >= serialTime1) {
      Serial.print("Sensor1");
      Serial.println(constrain(map(delay1, 0, 132, 100, 0), 0, 132));
//      Serial.println(delay1);
      serialTime1 = millis() + nextSerialTime1;
    }
  }
  delay(1);        // delay in between reads for stability


  if(millis() >= goTime2) {
    functionGo2();
    if (millis() >= serialTime2) {
      Serial.print("Sensor2");
      Serial.println(constrain(map(delay2, 0, 132, 100, 0), 0, 132));
      serialTime2 = millis() + nextSerialTime2;
    }
  }
   delay(1);        // delay in between reads for stability

   if(millis() >= goTime3) {
    functionGo3();
    if (millis() >= serialTime3) {
      Serial.print("Sensor3");
      Serial.println(constrain(map(delay3, 0, 132, 100, 0), 0, 132));
      serialTime3 = millis() + nextSerialTime3;
    }
  }
   delay(1);        // delay in between reads for stability
}

// Ring 1
void functionGo1 () {

  motorDelay1 = constrain(map(sonar1.ping_cm(), 200, 30, 75, 255), 75, 255);
  delay1 = constrain(sonar1.ping_cm(), 0, 200);
  duration1 = map(delay1, 0, 200, 0, 400);
  unsigned long currentMillis1 = millis();

  if (sonar1.ping_cm() == 0){
    analogWrite(motorControl1, 75);
    }
  else{
     analogWrite(motorControl1, motorDelay1);
  }

  if (delay1 != 0) {
  if (currentMillis1 - previousMillis1 >= (duration1)) {
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
}

// Ring 2
void functionGo2 () {
  motorDelay2 = constrain(map(sonar2.ping_cm(), 200, 30, 75, 255), 75, 255);
  delay2 = constrain(sonar2.ping_cm(), 0, 200);
  duration2 = map(delay2, 0, 200, 0, 400);
  unsigned long currentMillis2 = millis();

  if (sonar2.ping_cm() == 0){
    analogWrite(motorControl2, 75);
    }
  else{
     analogWrite(motorControl2, motorDelay2);
//     Serial.println(delay2);
  }

  if (delay2 != 0) {
  if (currentMillis2 - previousMillis2 >= (duration2)) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis2;

    // if the LED is off turn it on and vice-versa:
    if (ledState2 == 0) {
      ledState2 = 1;
      for(int i = 0; i < NUM_LEDS; i++ ) {
        strip2.setPixelColor(i, 255, 255, 0); 
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
}

// Ring 3
void functionGo3 () {
  motorDelay3 = constrain(map(sonar3.ping_cm(), 200, 30, 75, 255), 75, 255);
  delay3 = constrain(sonar3.ping_cm(), 0, 200);
  duration3 = map(delay3, 0, 200, 0, 400);
  unsigned long currentMillis3 = millis();

  if (sonar3.ping_cm() == 0){
    analogWrite(motorControl3, 75);
    }
  else{
     analogWrite(motorControl3, motorDelay3);
//     Serial.println(delay3);
  }

  if (delay3 != 0) {
  if (currentMillis3 - previousMillis3 >= (duration3)) {
    // save the last time you blinked the LED
    previousMillis3 = currentMillis3;

    // if the LED is off turn it on and vice-versa:
    if (ledState3 == 0) {
      ledState3 = 1;
      for(int i = 0; i < NUM_LEDS; i++ ) {
        strip3.setPixelColor(i, 255, 0, 0); 
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
}
