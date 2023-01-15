/* Library Functions: a collection of precompiled routines that a program can use. Can be imported/ included in your own program to ease coding experience.
Installed Keypad Library. The getKey() function is associaded with mySmolBoiPad Keypad. 
This example has a test to see if result is anything but zero will print to the serial monitor. 
*/

#include <Key.h>
#include <Keypad.h>

const byte ROWS =4;
const byte COLS = 4;

byte rowPins[ROWS] = {5, 4, 3, 2}; // {top left, ..., bottom left)
byte colPins[COLS] = {6, 7, 8, 9}; // {top left, ..., top right)

char buttons[ROWS][COLS] = {
  {'1', '2', '3', 'A'}, // 1st row
  {'4', '5', '6', 'B'}, // 2nd row
  {'7', '8', '9', 'C'}, // 3rd row
  {'*', '0', '#', 'D'}  // 4th row
};

Keypad mySmolBoiPad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(9600); // Begin monitoring via the serial monitor
}

void loop() {
  char result = mySmolBoiPad.getKey();

  if (result != 0) {   // if a button is pressed. 
    Serial.println(result);
  }
}
