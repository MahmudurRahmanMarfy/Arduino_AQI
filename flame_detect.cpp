#include <Arduino.h>
//#include "flame_detect.h"  // Include flame_detect.h if you have any functions in that file

int buzzer = 8;
int time1 = 500;
int time2 = 50;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(4, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int flameIntensity = analogRead(A0);
  int flameDetection = digitalRead(4);

  Serial.print("Flame_intensity:");
  Serial.print(flameIntensity);
  Serial.print("  ");
  Serial.print("Flame_detection: ");
  Serial.println(flameDetection);

  // Warning sound
  if (flameIntensity < 800 && flameDetection == 0) {
    tone(buzzer, 1000);
    delay(time1);
    noTone(buzzer);
    delay(time1);
  }

  // Alarm sound
  if (flameIntensity < 750 && flameDetection == 1) {
    tone(buzzer, 2000);
    delay(time2);
    noTone(buzzer);
    delay(time2);
  }
}
