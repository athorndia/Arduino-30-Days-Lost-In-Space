/* This example demonstrates how to connect HERO with rotary encoder and 7 segment display.
Here the rotary encoder is an input device and the 7 segment display is an output device.
The 7 segment display prints the values of the rotary encoder (positive or negative) on 4 digits
where the first digit (most left) is used for the minus sign (-).
Buzzer on breadboard. 2 wires connect buzzer(-)end to digital GND and buzzer(s) to pin 10 on HERO. 

Had to switch from pc to mac and installed the following libraries: TM1637, Keypad, Encoder by Paul Stoffregen...etc.
*/

#include <TM1637Display.h>
#include <Encoder.h>
 
// Rotary Encoder Inputs connected to pins on HERO:
#define CLK2 2
#define DT2 3
 
// Define the display connection pins for 4 digit 7 segment display connected to pins on HERO:
#define CLK 6
#define DIO 5

// Define the "decrypted" secret numbers for audio buzzer:
// *Original code = 23-353-1688, but I didn't want to turn it 1688x, so the numbers were modified for convenience*
#define SECRET1 5
#define SECRET2 10
#define SECRET3 15 // done 
 
// Create display object of type TM1637Display:
TM1637Display OurDisplay = TM1637Display(CLK, DIO);
 
// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
 
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
 
// You can set the individual segments per digit to spell words or create other symbols on 7 segment 4 digit display:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
 
int counter = 0;    // keep a running tally of steps...this is keeping count of increments in the rotation of the encoder:
int currentStateCLK;
int lastStateCLK;
String currentDir =""; 
int buzzer = 10;  // pin 10 of the HERO that drives the buzzer
int toneFreq = 0; // the number of cycles per second with which we're going to activate the buzzer and will create the tone that'll unlock the "navigation system".

// *************************************************************************** //

// custom functions to give audio feedback

void playBuzz() {
  tone(buzzer, toneFreq, 1000);
  delay(1000);
  noTone(buzzer);
  delay(100);
  OurDisplay.clear();
  counter++;
}

// *************************************************************************** //

/* The setup routine initializes the serial monitor and sets up the interrupt function for the rotary encoder 
to detect rotations of the encoder shaft and those interrups call an interrupt service routine whose name is "updateEncoder". */

void setup() {
 
  // Set encoder pins as inputs
  pinMode(CLK2,INPUT);
  pinMode(DT2,INPUT);
 
  // Setup Serial Monitor
  Serial.begin(9600);
 
  // Read the initial state of A (CLK)
  lastStateCLK = digitalRead(CLK2);
 
  // Clear the display:
  OurDisplay.clear();
  delay(200);
  OurDisplay.setBrightness(7);
 
  // Call Interrupt Service Routine (ISR) updateEncoder() when any high/low change
  // is seen on A (CLK2) interrupt  (pin 2), or B (DT2) interrupt (pin 3)
 
  attachInterrupt(digitalPinToInterrupt(CLK2), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT2), updateEncoder, CHANGE);
}

// *************************************************************************** //
 
/* This loop routine puts information out to the serial monitor and to the 7 segment display
 and at appropriate times send the audio signal of the correct frequency to the buzzer. */
void loop() {
  OurDisplay.showNumberDec(counter);
  delay(50);
 
 /* when counter reaches designated value we will set tone frequency to that value 
 and we will play the buzzer for second. */
  if(counter == SECRET1) {  
    toneFreq=SECRET1;
    playBuzz();
  }
 
 if(counter == SECRET2) {
    toneFreq=SECRET2;
    playBuzz();
 } 

 if(counter == SECRET3) {
    toneFreq=SECRET3 ;
    playBuzz();
 }
}
 
// *************************************************************************** //

/* This is our ISR (Interrupt Service Routine) which has the job of responding to interrupt events.
It's simply used to detect and react to rotations in the shaft of the rotary encoder.  
*/
void updateEncoder(){
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK2);
 
  // If last and current state of CLK are different, then a pulse occurred;
  // React to only 0->1 state change to avoid double counting
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
 
    // If the DT state is different than the CLK state then
    // the encoder is rotating CW so INCREASE counter by 1
    if (digitalRead(DT2) != currentStateCLK) {
      counter ++;
      currentDir ="CW";
     
    } else {
      // Encoder is rotating CCW so DECREASE counter by 1
      counter --;
      currentDir ="CCW";
    }
 
    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter= ");
    Serial.println(counter);
  }
 
  // Remember last CLK state to use on next interrupt...
  lastStateCLK = currentStateCLK;
  delay(1); // Put in a slight delay to help debounce the reading. 
}
