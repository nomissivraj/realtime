
/*
 Motor Control with a Transistor

 This example shows you how to control a motor's using a transistor.
 When a pushbutton on pin 2 is pressed, the Arduino will control a transistor
 via PWM, which will slowly ramp up the motor's speed, then slow it down.

 The circuit : 
 * momentary switch with one end connected to 5V, the other end connected 
   to GND through a 10-kilohm resistor, and digital pin 2.
 * TIP120 tranistor, with the Base connected to digital pin 9, the Emitter to ground,
   and the Collector to one lead from a 9V DC motor
 * a 9V battery, with the ground connected to the Arduino's ground, and the power
   connected to the motor
 * 1N4001 diode across the motor's leads, with the striped side conneted to the 9V

 The Arduino can only provide 40mA at 5V on its pins. Most motors require 
 more current and/or voltage to overcome intertia and run. A transistor
 can act as a digital switch, enabling the Arduino to control loads with 
 higher electrical requirements. 

 Created on 03 January 2013
 by Scott Fitzgerald 

 http://www.arduino.cc/en/Tutorial/TransistorMotorControl

 This example code is in the public domain.
 */

#include <NewPing.h>



int trigPin1 = 5;    // Trigger
int echoPin1 = 6;    // Echo
int delay1;

int trigPin2 = 7;
int echopin2 = 8;
int delay2;

int trigPin3 = 9;
int echoPin3 = 10;
int delay3;

unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false; // true if still waiting for delay to finish

NewPing sonar1(trigPin1, echoPin1, 200); // NewPing setup of pins and maximum distance.
NewPing sonar2(trigPin2, echoPin2, 200); // NewPing setup of pins and maximum distance.
NewPing sonar3(trigPin3, echoPin3, 200); // NewPing setup of pins and maximum distance.

// the transistor which controls the motor will be attached to digital pin 9
int motorControl = 9;

// the setup routine runs once when you press reset:
void setup() {
Serial.begin(57600);
  delayStart = millis();   // start delay
  delayRunning = true; // not finished yet

  // make the transistor's pin an output:
  pinMode(motorControl, OUTPUT);  
  
}

// the loop routine runs over and over again forever:
void loop() {

  //Motor 1
  delay1 = map (sonar1.ping_cm(), 200, 5, 5, 252);
  if (delayRunning && ((millis() - delayStart) >= 500)) {
    if (sonar.ping_cm() == 0){
      analogWrite(motorControl, 100);
      Serial.println(delay1);
    }
    else{
       analogWrite(motorControl, delay1);
       Serial.println(delay1);
    }
  }

  //Motor 2
  delay2 = map (sonar2.ping_cm(), 200, 5, 5, 252);
  if (delayRunning && ((millis() - delayStart) >= 500)) {
    if (sonar2.ping_cm() == 0){
      analogWrite(motorControl, 100);
      Serial.println(delay2);
    }
    else{
       analogWrite(motorControl, delay2);
       Serial.println(delay2);
    }
  }

  //Motor 3
  delay3 = map (sonar3.ping_cm(), 200, 5, 5, 252);
  if (delayRunning && ((millis() - delayStart) >= 500)) {
    if (sonar3.ping_cm() == 0){
      analogWrite(motorControl, 100);
      Serial.println(delay3);
    }
    else{
       analogWrite(motorControl, delay3);
       Serial.println(delay3);
    }
  }
  

  

  delay(1);        // delay in between reads for stability
  
}
