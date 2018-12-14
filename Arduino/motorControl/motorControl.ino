
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
long duration1;
int delay1;
int distance1;
unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false; // true if still waiting for delay to finish

NewPing sonar(trigPin1, echoPin1, 200); // NewPing setup of pins and maximum distance.

// give a name to digital pin 2, which has a pushbutton attached
int pushButton = 2;

// the transistor which controls the motor will be attached to digital pin 9
int motorControl = 9;

// the setup routine runs once when you press reset:
void setup() {
Serial.begin(57600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  delayStart = millis();   // start delay
  delayRunning = true; // not finished yet
  
  // make the pushbutton's pin an input:
  //pinMode(pushButton, INPUT);

  // make the transistor's pin an output:
  pinMode(motorControl, OUTPUT);  
  
}

// the loop routine runs over and over again forever:
void loop() {
  delay1 = map (sonar.ping_cm(), 200, 5, 5, 252);
  if (delayRunning && ((millis() - delayStart) >= 500)) {
 if (sonar.ping_cm() == 0){
 analogWrite(motorControl, 100);
  Serial.println(delay1);
}
  else{
    analogWrite(motorControl, delay1);
    Serial.println(delay1);
  }
  
  Serial.print(sonar.ping_cm());
  Serial.println();
  }

  

  //delay(1);        // delay in between reads for stability
  
}
