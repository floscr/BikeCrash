#include <time.h>
#include <stdlib.h>

const int ENA = 7;
const int IN1 = 6;
const int IN2 = 5;

// Ungefaehr die dauer wie lang der motor zum ausfahrent braucht vor dem aushaehngemechanismus
const int DRIVE_OUT_DURATION = 24000;

// Ungefaehr die dauer wie lang der motor zum einfahren braucht
const int DRIVE_IN_DURATION = 32000;

int durationIndex = 0;
int durations[] = { 1000, 10000, 3000, 1000, 5000, 2000, 5000, 1000 };
int durationsLen = sizeof durations / sizeof durations[0];
int getNextDuration() {
  if (durationIndex == durationsLen - 1) {
    durationIndex = 0;
  }
  durationIndex++;
  return durations[durationIndex];
}

void setup() {
  Serial.begin(9600);      // Tells the arduin to print the output to the

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
    delay(DRIVE_OUT_DURATION);

    // Wait some time before going over the limit
    stopDrive();
    delay(getNextDuration());

    // Start driving out again over the limit
    driveOut();
    delay(6000);

    // wait some time to drive in the moter
    delay(20000);

    // Go to the initial position of the motor
    driveIn();
    delay(DRIVE_IN_DURATION);
  }

  exit(0);
}
