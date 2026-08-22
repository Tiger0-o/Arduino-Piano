// Capacitive-touch piano using the mechanical piano's output layout.
#include <Arduino.h>
#include <CapacitiveSensor.h>

const int nC4 = 262;
const int nD4 = 294;
const int nE4 = 330;
const int nF4 = 349;
const int nG4 = 392;
const int nA4 = 440;
const int nB4 = 494;
const int nC5 = 523;

const int commonPin = 2;
const int ledPin = 8;
const int varPin = A5;
const int buzzerPin = 3;

const int sampleCount = 10;
const long capacitanceThreshold = 150;
const int notes[] = {nC4, nD4, nE4, nF4, nG4, nA4, nB4, nC5};
const int touchPins[] = {4, 5, 6, 7, 9, 10, A0, A1};
const int keyCount = sizeof(touchPins) / sizeof(touchPins[0]);

CapacitiveSensor keys[] = {
	CapacitiveSensor(commonPin, touchPins[0]),
	CapacitiveSensor(commonPin, touchPins[1]),
	CapacitiveSensor(commonPin, touchPins[2]),
	CapacitiveSensor(commonPin, touchPins[3]),
	CapacitiveSensor(commonPin, touchPins[4]),
	CapacitiveSensor(commonPin, touchPins[5]),
	CapacitiveSensor(commonPin, touchPins[6]),
	CapacitiveSensor(commonPin, touchPins[7])
};

void setup() {
	for (int i = 0; i < keyCount; i++) {
		keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
	}

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
	pinMode(buzzerPin, OUTPUT);
	pinMode(varPin, INPUT);
	Serial.begin(9600);
}

void loop() {
	analogRead(varPin);

	int pressedKey = -1;
	for (int i = 0; i < keyCount; i++) {
		if (keys[i].capacitiveSensor(sampleCount) > capacitanceThreshold) {
			pressedKey = i;
		}
	}

	if (pressedKey >= 0) {
		tone(buzzerPin, notes[pressedKey]);
		digitalWrite(ledPin, HIGH);
	} else {
		noTone(buzzerPin);
		digitalWrite(ledPin, LOW);
	}
}
