/* This example demonstrates how to control and input information using a rotary encoder.  
It's important to be able to determine the state of rotation of the encoder and keep track of the number of rotations either clockwise (CW) or counterclockwise (CCW).

Rotary Encoder = a device that allows us to turn a shaft/knob and have that correspond to numberical or data information that can be accessed or used by the HERO system.
There are several different types of rotary encoders. 
(1) Absolute Encoders give a unique correspondence between an angular position of the knob and the value that comes out, so there is a maximum clockwise and maximum counterclockwise position.  
(2) Relative Encoders can turn indefinitely and can tell relatively you how much the knob has turned clockwise or counterclockwise from some original position. 

A relative encoder was used today. It has 20 positions that it clicks through a full rotation of 360 degrees. Corresponds to 1/20th of a circle or an angular resolution of 18 degrees. 
It has 4 pins (CLK, DT, +[VCC], GND). GND and VCC will be connected to GND and +5V pins of the HERO board respectively. SW is a switch.

      GND is the ground connection.
      
      VCC is the positive supply voltage, typically 3.3 – 5 volts.
      
      SW is the active low push button switch output. When the knob is pressed down, the voltage goes LOW.
      
      DT (Output B) is similar to CLK output, but it lags behind CLK by a 90° phase shift. This output is used to determine the direction of rotation.
      
      CLK (Output A) is the primary output pulse to determine the amount of rotation. 
      Each time the knob is turned in either direction by just one detent (click), the ‘CLK’ output goes through one cycle of going HIGH and then LOW.

If signal A turns HIGH before signal B, the HERO board will know that the rotary encoder is rotating clockwise. 
If signal B goes HIGH before signal A, then we know it's rotating the knob counterclockwise. 

The concept of an interrupt is important for tackling unexpected events.  We need to tell the HERO what to do when an interrupt occurs. The name of this routine is called 'updateEncoder'. 

Unexpected counting errors may be caused by rotating the knob too fast or accidentely rotating the knob in the opposite direction. It could skip a number or go back to 0. 

Useful website: https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/ 

*/


// Include the 7-segment display library:
#include <TM1637Display.h>
 
// Rotary Encoder Inputs
#define CLK2 2
#define DT2 3
 
// Define the display connection pins:
#define CLK 6
#define DIO 5
 
// Create display object of type TM1637Display:
TM1637Display OurDisplay = TM1637Display(CLK, DIO);
 
// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
 
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
 
// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
 
int counter = 0;    // keep a running tally of how many encoder clicks we've gone through...everytime we go clockwise we'll increment counter by +1, everytime we go counterclockwise we'll decrement/decrease it by 1.  
int currentStateCLK; // keeps track of changes...either HIGH or LOW of the pins of the encoder. 
int lastStateCLK;
String currentDir =""; // string variable (an array of characters) that allows us to write on the display. 

//***************************************************************************************************************************************************//
 
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
  delay(1000);
  OurDisplay.setBrightness(7);
 
  // Call Interrupt Service Routine (ISR) updateEncoder() when any high/low change
  // is seen on A (CLK2) interrupt  (pin 2), or B (DT2) interrupt (pin 3)
 
  attachInterrupt(digitalPinToInterrupt(CLK2), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT2), updateEncoder, CHANGE);
}

//***************************************************************************************************************************************************//

void loop() {
  OurDisplay.showNumberDec(counter);
  delay(50);

  // TEST
  if(counter == 50) {
    OurDisplay.setSegments(data);
    delay(2000);
    OurDisplay.clear();
  }
 
 if(counter == 75) {
    OurDisplay.setSegments(data);
    delay(2000);
    OurDisplay.clear();
  }
 
  if(counter == 100) {
    OurDisplay.setSegments(done);
    delay(3000);
    OurDisplay.clear();
    delay(1000);
    OurDisplay.setSegments(done);
    delay(3000);
    OurDisplay.clear();
 }
 
}
 
//************************************ This is our ISR which has the job of responding to interrupt events *************************************************//

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
}
