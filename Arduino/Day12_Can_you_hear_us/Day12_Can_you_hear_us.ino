/* This examples demonstrates how you can assign frequency tones to your Keypad. 
Wires connects Keypad to HERO Digital PWM pins:(top -> bottom: c4-pin9, c3-pin8, c2-pin7, c1-pin6, r1-pin5, r2-pin4, r3-pin3, r4-pin2). 
Buzzer located BBf123. Wire connects 5v to BB(+)bus. Another wire connects BB(+)bus to 3j. And another wire connects 1j to pin10.

Arrays need to use const, a variable qualifier that modifies the behavior of the variable, making a variable "read-only". This means that the variable can be used just as any other variable of its type, but its value cannot be changed.

A byte is a data type that stores an 8-bit unsigned number, from 0 to 255. Syntax: byte var = val.

A char is a data type used to store a character value. Character literals = 'A'; Multiple characters = "ABC". It's possible to do arithmetic on characters. 

*/

#include <Key.h>
#include <Keypad.h>  

const byte ROWS =4;
const byte COLS = 4;

byte rowPins[ROWS] = {5, 4, 3, 2}; // (top left -> bottom left; index: 0, 1, 2, 3)
byte colPins[COLS] = {6, 7, 8, 9}; // (top left -> top right; index: 0, 1, 2, 3)

char buttons[ROWS][COLS] = {
  {'1', '2', '3', 'A'}, // 1st row
  {'4', '5', '6', 'B'}, // 2nd row
  {'7', '8', '9', 'C'}, // 3rd row
  {'*', '0', '#', 'D'}  // 4th row
};

Keypad mySmolBoiPad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS); 

int tones [ROWS][COLS] = { // a frequency tone (Hertz) for each button (low # = low frequency)
  {31, 93, 147, 208},
  {247, 311, 370, 440},
  {523, 587, 698, 880},
  {1397, 2637, 3729, 4978}
};

int buzzer = 10; // pin 10 drives the buzzer

//*********************************************************************************************

void setup() {
  Serial.begin(9600); // Begin monitoring via the serial monitor
}

//*********************************************************************************************

void loop() {

  int toneFreq = 0;
  char result = mySmolBoiPad.getKey();

  if (result != 0) {   // if a button is pressed. 
    for (byte j=0; j<ROWS; j++) {
      for (byte i=0; i<COLS; i++) {
        if (result == buttons[j][i]) {    // found it, get the corresponding tone
          toneFreq=tones[j][i];
        }
        } // end i loop
      } // end j loop

    Serial.print("Key: ");  // send the result to serial...
    Serial.println(result);
    Serial.print("  Freq: ");
    Serial.println(toneFreq);

    tone(buzzer, toneFreq, 500); //... and play the tone for a half second 
    delay(500);
    noTone(buzzer); // end it nicely 
    
  }
}
