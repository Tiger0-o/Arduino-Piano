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
const int buttonPins[] = {A0, A1, A2, A3, 6, 5, 4, 2};
const int notes[] = {nC4, nD4, nE4, nF4, nG4, nA4, nB4, nC5};

const int ledPin = 8;
const int varPin = A5;
const int buzzerPin = 3;
int noteDuration = 0;
int length = 0;

const int ledOctave = 10;
const int button = 7;
bool octave = false;

void setup() {
    // Iterates over the provided lists and initialises the pins for input/output
    length = sizeof(buttonPins) / sizeof(buttonPins[0]);
    for (int i = 0; i < length; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    pinMode(button, INPUT_PULLUP);

    pinMode(ledOctave, OUTPUT);
    digitalWrite(ledOctave, LOW);

    pinMode(buzzerPin, OUTPUT);
    pinMode(varPin, INPUT);

    // varPin connection
    Serial.begin(9600);
}

void loop() {
    noteDuration = map(analogRead(varPin), 0, 1023, 50, 500);

    // Iterates over the provided lists and checks if a key is pressed
    bool buttonPressed = false;
    for (int i = 0; i < length; i++) {
        // Plays the corresponding note when a key is pressed.
        if (digitalRead(buttonPins[i]) == LOW) {
            if (octave) {
                tone(buzzerPin, notes[i] * 2, noteDuration);
            } else {
                tone(buzzerPin, notes[i], noteDuration);
            }
            buttonPressed = true;
        }
    }

    if (digitalRead(button) == LOW) {
        octave = !octave; // Toggles the octave state when the button is pressed
        digitalWrite(ledOctave, octave ? HIGH : LOW);

        while (digitalRead(button) == LOW) {
        }
    }

    // D8 is the only LED output and stays on while any key is pressed.
    if (buttonPressed) {
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }

}