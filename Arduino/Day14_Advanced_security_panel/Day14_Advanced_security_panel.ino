/* This example demonstrates how to use a security code KeyPad with additional features such as light and sound. 

CIRCUIT: Wires connect Keypad -> HERO Pins (c4-pin13, c3-pin12, c2-pin7, c1-pin6, r1-pin5, r2-pin4, r3-pin3, r4-pin2).
The RGB LED use PWM. PWM(~) Review: Analog-like signals create by sending modulated on and off signals. PWM compatible pins are marked with tilde (~) on the HERO.
Red wire connects pin11-BB14a; Green wire connects pin10-BB16a; Blue wire connects pin9-BB17a. Three 220 ohm resistors bridge L->R, RGB LED located 14j-17j.
White wire connects 15g-leftBB(+)bus so LEDgnd is connected. 
Buzzer located 123j(S@top). Another white wire connects HERO Digital_gnd-leftBB(+)bus. And another white wire connects BB(+)bus-3f (connects buzzer).
*/

#include <Key.h>
#include <Keypad.h>  

int buzzer = 8; // sound output pin
int redPin = 11; // PWM color output pins
int greenPin = 10;
int bluePin = 9;

const byte ROWS =4;
const byte COLS = 4;
const byte PassLength = 4; // passwords will by 4 characters long
char currentPassword[PassLength] = {'0', '0', '0', '0'}; // default before setting

char buttons[ROWS][COLS] = {
  {'1', '2', '3', 'A'}, // 1st row
  {'4', '5', '6', 'B'}, // 2nd row
  {'7', '8', '9', 'C'}, // 3rd row
  {'*', '0', '#', 'D'}  // 4th row
};

byte rowPins[ROWS] = {5, 4, 3, 2}; // (top left -> bottom left; index: 0, 1, 2, 3)
byte colPins[COLS] = {6, 7, 12, 13}; // (top left -> top right; index: 0, 1, 2, 3)

Keypad mySmolBoiPad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS); 

// EXTERNAL custom function to process a login attempt *********************************************************************************************

int unlockMode() {    // purpose is to handle user attempts to enter a password and report back either success or failure depending upon the results of the key inputs.
  char result;

  RGB_color(0, 0, 0); // turn RGB LED OFF
  Serial.println("Unlock Mode: Type Password to continue");
  delay(500);

  for(int i = 0; i < PassLength; i++) {
    while(!(result = mySmolBoiPad.getKey())) {      // the "do nothing while loop"
      // wait indefinitely for keypad input of any kind
    }
    if(currentPassword[i] != result) {    // a wrong key was pressed
      Serial.println("WRONG PASSWORD");
      Serial.println(result);
      playError();
      return -1;                        // -1 means failed -- return immediately back to while loop
    }
    Serial.print("*"); // print a phantom character for a successful keystroke
    playInput();
    RGB_color(0, 0, 125); // flash LED Blue
    delay(100);
    RGB_color(0, 0, 0); 
  }   // done after 4 characters are accepted

  Serial.println("");
  Serial.println("Device Successfully Unlocked!");
  playSuccess();
  return 0;     // 0 is non-negative so this means we succeeded 
}

// EXTERNAL custom functions to give audio feedback *********************************************************************************************

void playSuccess() {
  tone(buzzer, 1000, 200);
  delay(200);
  tone(buzzer, 2700, 1000); // Sound: "Ta Da" (Low -> High)
  delay(1000);
  noTone(buzzer);
}

void playError() {
  tone(buzzer, 700, 200);
  delay(100);
  tone(buzzer, 141, 1000); // Sound: "Uh Oh" (Low -> Lower)
  delay(1000);
  noTone(buzzer);
}

void playInput() {
  tone(buzzer, 880, 200); // Sound: short sweet beep
  delay(50);
  noTone(buzzer);
}

// EXTERNAL custom function to light the LED *********************************************************************************************

void RGB_color(int red_value, int green_value, int blue_value)
{
  analogWrite(redPin, red_value);
  analogWrite(greenPin, green_value);
  analogWrite(bluePin, blue_value);
}

// SETUP ********************************************************************************************************************************

void setup() {
  pinMode(redPin, OUTPUT); // designate pins for PWM LED output
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  RGB_color(125, 125, 125); // set LED to White on startup...
  delay(2000);
  RGB_color(0, 0, 0); //... and OFF again
  
  Serial.begin(9600); // Begin monitoring via the serial monitor
  delay(2000); // It's helpful to give the serial monitor a few seconds before printing on it
  Serial.println("Press * to set a new password.");
  Serial.println("Press # to access the system with the existing one.");
}

// LOOP ********************************************************************************************************************************

void loop() {
  char result = mySmolBoiPad.getKey(); // returns a character associated with the key that was pressed

  if (result == '*') {    // choice to change password (true = *; false = anything else or nothing)
    int access = unlockMode();

    if (access < 0) { // if access if a negative number then the password entry failed
      Serial.println("Access Denied. Cannot change password without knowing the previous password.");
      RGB_color(125, 0, 0); // LED to RED
    }
    else {    // if access is non-negative then password was correctly entered as determined by unlockMode()
      RGB_color(0, 125, 0); // LED to GREEN
      delay(2000);
      RGB_color(0, 0, 0); //... and OFF again
      Serial.println("Welcome, authorized user. Please Enter a new password: ");
      delay(500);

      for (int i = 0; i < PassLength; i++) {    // PassLength is 4 (0,1,2,3)
        while(!(result = mySmolBoiPad.getKey())) {    
          /*A while loop will execute repeatedly unless a condition is met. 
            The code will also not proceed to the next section until the condition is met.
            It'll wait indefinitely for keypad input of any kind. 
            If no key has been pressed the while loop will be true and will continue to spin and wait for something to be typed.
            If a key is pressed result becomes non-zero... 
            ...and the negation of something non-zero is zero (false), the while loop is no longer true and will drop out.
        */
        }

        currentPassword[i] = result;
        Serial.print("*"); // print a phantom character for a successful keystroke 
        playInput();
        RGB_color(0, 0, 125); // flash LED Blue
        delay(100);
        RGB_color(0, 0, 0); //... and OFF again
      } // done after 4 characters are accepted. 

      Serial.println("");
      Serial.println("Password Successfully Changed!");
      RGB_color(0, 125, 0); // LED to Green
    }
  }

  else if (result == '#') {     // choice to access system with current password
    int access = unlockMode();
    if (access < 0) {
      Serial.println("Password error. Access Denied.");
      RGB_color(125, 0 , 0); // LED to Red
    }
    else {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
      RGB_color(0, 125, 0); // LED to Green 
    }
  }
  
}
