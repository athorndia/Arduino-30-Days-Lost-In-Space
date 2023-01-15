/*This example demonstrates how Encryption can be used to send secure messages. 

Encyption: the process of converting information or data into a code, especially to prevent unauthorized access. 
Decryption: is a process that transforms encrypted information into its original format. 

Substitution Cypher: encrypt the plaintext by swapping each letter or symbol in the plaintext by a different symbol as directed by the DECRYPT KEY. Example shown: Kakashi vanishes and is replaced with a stump in front of Sauske. 
Ceasar Cypher: XYZ| ABEDEF -> ABCDEF | GHI 

Project idea: discover various other cyphers and use them in code projects/ make a game? 

Public & Private Key Encryption: The recipient's public key encrypts the message -> The recipient's private key decrypts the message. 

Decyption Notes:
- The encrypted program will use the four digit seven segment display code. 
- Do not assume pin numbers (ps. pin numbers will depend on your circuit / diagram).
- Ceasar Cypher used here will only substitute letters (does not substitute numbers in their basic form). 
- You can copy and paste the code into a website that can decode a Caesar Cipher. (1) https://cryptii.com/pipes/caesar-cipher (2) https://cyberchef.org/#recipe=ROT13(true,true,false,-7)
-- Make sure it’s set to “Decode” and adjust the Shift until you see text that makes sense as Arduino code. It was sort of clunky to copy/paste it back out, but it worked. Be sure to #define the CLK and DIO pins correctly! You should be able to then just upload and run it.
*/

// Include the 7-segment display library:
#include <TM1637Display.h>
 
// Define the display connections pins:
#define CLK 6
#define DIO 5
 
// Create display object of type TM1637Display:
TM1637Display mySmolBoiDisplay = TM1637Display(CLK, DIO);
 
// Create array that turns all segments on:
const uint8_t all_on[] = {0xff, 0xff, 0xff, 0xff}; // 0xff is a hexidecimal number whose binary
                                                 // representation is all ones
 
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00}; // 0xff is a hexidecimal number whose binary
                                                  // representation is all zeros
 
// You can set the individual segments to spell digits, words or create other symbols
// by performing bitwise OR operations of the segments you need to turn on:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
 
void setup() {
  // Clear the display:
  mySmolBoiDisplay.clear();
  delay(1000);
}
 
void loop() {
  // Set the brightness:
  mySmolBoiDisplay.setBrightness(7);
  // All segments on:
  mySmolBoiDisplay.setSegments(all_on);
  delay(2000);
  mySmolBoiDisplay.clear();
  delay(1000);
 
  // demonstrate counter:
  int i;
  for (i = 0; i <= 100; i++) {
    mySmolBoiDisplay.showNumberDec(i);  // this knows how to make decimal numbers
    delay(100);
  }
  delay(2000);
  mySmolBoiDisplay.clear();
  delay(1000);
  mySmolBoiDisplay.setSegments(done);
  while(1);  // after one pass, hang here forever...
}
