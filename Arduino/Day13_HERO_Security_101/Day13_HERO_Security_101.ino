#include <Key.h>
#include <Keypad.h>  

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
byte colPins[COLS] = {6, 7, 8, 9}; // (top left -> top right; index: 0, 1, 2, 3)

Keypad mySmolBoiPad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS); 

// custom function to process a login attempt ************************************************

int unlockMode() {
  char result;

  Serial.println("Unlock Mode: Type Password to continue");
  delay(500);

  for(int i = 0; i < PassLength; i++) {
    while(!(result = mySmolBoiPad.getKey())) {      // the "do nothing while loop"
      // wait indefinitely for keypad input of any kind
    }
    if(currentPassword[i] != result) {    // a wrong key was pressed
      Serial.println("WRONG PASSWORD");
      Serial.println(result);
      return -1;                        // -1 means failed -- return immediately to while loop
    }
    Serial.print("*"); // print a phantom character for a successful keystroke 
  }   // done after 4 characters are accepted

  Serial.println("");
  Serial.println("Device Successfully Unlocked!");
  return 0;     // 0 is non-negative so this means we succeeded 
}

//*********************************************************************************************

void setup() {
  Serial.begin(9600); // Begin monitoring via the serial monitor
  delay(2000); // It's helpful to give the serial monitor a few seconds before printing on it
  Serial.println("Press * to set a new password.");
  Serial.println("Press # to access the system with the existing one.");
}

//*********************************************************************************************

void loop() {
  char result = mySmolBoiPad.getKey(); // returns a character associated with the key that was pressed

  if (result == '*') {    // choice to change password (true = *; false = anything else or nothing)
    int access = unlockMode();

    if (access < 0) { // if access if a negative number then the password entry failed
      Serial.println("Access Denied. Cannot change password without knowing the previous password.");
    }
    else {    // if access is non-negative then password was correctly entered as determined by unlockMode()
      Serial.println("Welcome, authorized user. Please Enter a new password: ");
      delay(500);

      for (int i = 0; i < PassLength; i++) {    // PassLength is 4 (0,1,2,3)
        while(!(result = mySmolBoiPad.getKey())) {    // A while loop will execute repeatedly unless a condition is met. The code will also not proceed to the next section until the condition is met.
          // wait indefinitely for keypad input of any kind. If no key has been pressed the while loop will be true and will continue to spin and wait for something to be typed.
          // if key is pressed result becomes non-zero... and the negation of something non-zero is zero (false), the while loop is no longer true and will drop out.
        }

        currentPassword[i] = result;
        Serial.print("*"); // print a phantom character for a successful keystroke 
      } // done after 4 characters are accepted. 

      Serial.println("");
      Serial.println("Password Successfully Changed!");
    }
  }

  else if (result == '#') {     // choice to access system with current password
    int access = unlockMode();
    if (access < 0) {
      Serial.println("Password error. Access Denied.");
    }
    else {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
    }
  }
  
}
