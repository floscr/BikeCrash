#include <time.h>
#include <stdlib.h>
#include <stdio.h>

const int ENA = 7;
const int IN1 = 6;
const int IN2 = 5;

// Ungefaehr die dauer wie lang der motor zum einfahren braucht
const int DRIVE_IN_DURATION = 32000;

// Time out before the crash
int afterStopDurations[] = { 1000, 1000, 5000, 2000, 5000, 1000, };
int afterStopDurationsLen = sizeof afterStopDurations / sizeof afterStopDurations[0];
int afterStopIndex = -1;

// Time out after the crash
int afterCrashDurations[] = { 1000, 1000, 5000, 2000, 5000, 1000, };
int afterCrashDurationsLen = sizeof afterCrashDurations / sizeof afterCrashDurations[0];
int afterCrashIndex = -1;

// Time out before driving out motor again
int afterStartDurations[] = { 1000, 1000, 5000, 2000, 5000, 1000, };
int afterStartDurationsLen = sizeof afterStartDurations / sizeof afterStartDurations[0];
int afterStartIndex = -1;

int getNextDuration(int *index, int durations[], int len) {
  if (*index >= len - 1) {
    *index = 0;
  } else {
    *index = *index + 1;
  }

  return durations[*index];
}

void setup() {
  Serial.begin(9600); // Tells the arduin to print the output to the

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(ENA, HIGH);
}

void stopDrive() {
  digitalWrite(ENA, 0);
}

void driveIn() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void driveOut() {
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

int driveOutTime = 22000;

void driveInManual() {
  driveIn();
  exit(0);
}

void loop() {
  // Starting the program, driving in the motor
  driveIn();
  delay(DRIVE_IN_DURATION);

  // Starting the interval
  while (true) {
    driveOut();
    delay(driveOutTime);

    delay(getNextDuration(&afterStartIndex, afterStartDurations, afterStartDurationsLen));

    // Wait some time before going over the limit
    stopDrive();
    delay(getNextDuration(&afterStopIndex, afterStopDurations, afterStopDurationsLen));

    // Start driving out again over the limit
    driveOut();
    delay(6000);

    // wait some time to drive in the moter
    delay(getNextDuration(&afterCrashIndex, afterCrashDurations, afterCrashDurationsLen));

    // Go to the initial position of the motor
    driveIn();
    delay(DRIVE_IN_DURATION);
  }

  exit(0);
}
