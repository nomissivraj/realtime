#include <Adafruit_NeoPixel.h>

//define NeoPixel Pin and Number of LEDs
#define PIN 1
#define NUM_LEDS 16

//create a NeoPixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
int ledState = 0;
int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // start the strip and blank it out
  strip.begin();
  strip.show();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= map (duration, 300, 20000, 50, 4000)) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == 0) {
      ledState = 1;
      for(int i = 0; i < NUM_LEDS; i++ ) {
        strip.setPixelColor(i, 0, 0, 255); 
      }
      strip.show();
    } else {
      ledState = 0;
      for(int i = 0; i < NUM_LEDS; i++ ) {
        strip.setPixelColor(i, 0, 0, 0); 
      }
      strip.show();
    }
  }
}
