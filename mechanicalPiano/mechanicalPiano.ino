#include <Arduino.h>

// Musical notes and their corresponding frequencies (Hz)
const int nC4 = 262;
const int nD4 = 294;
const int nE4 = 330;
const int nF4 = 349;
const int nG4 = 392;
const int nA4 = 440;
const int nB4 = 494;
const int nC5 = 523;

// Pin assignments for buttoms, LEDs, and buzzer
// MAKE SURE TO FILL IN THE BUTTON AND LED PIN ARRAYS WITH THE CORRECT PIN NUMBERS
const int buttonPins[] = {A0, A1, A2, A3, 6, 5};
const int notes[] = {nC4, nD4, nE4, nF4, nG4, nA4, nB4, nC5};

const int ledPin = 8;
const int varPin = A5;
const int buzzerPin = 3;
int varChange = 0;
int length = 0;

void setup() {
    // Iterates over the provided lists and initialises the pins for input/output
    int length = sizeof(buttonPins) / sizeof(buttonPins[0]);
    for (int i = 0; i < length; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    pinMode(buzzerPin, OUTPUT);
    pinMode(varPin, INPUT);

    // varPin connection
    Serial.begin(9600);
}

void loop() {
    varChange = analogRead(varPin);
    varChange = map(varChange, 0, 1023, 0, 225);

    // Iterates over the provided lists and checks if a key is pressed
    for (int i = 0; i < length; i++) {
        // Plays the corresponding note and turns on the corresponding LED
        if (digitalRead(buttonPins[i]) == LOW) {
            // analogWrite(buzzerPin, varChange);
            tone(buzzerPin, notes[i], 100);
            digitalWrite(ledPin, HIGH);
        } if (digitalRead(buttonPins[i]) == HIGH) {
            // Keeps the LED off when the key is not pressed.
            digitalWrite(ledPin, LOW);
        }
    }
}
