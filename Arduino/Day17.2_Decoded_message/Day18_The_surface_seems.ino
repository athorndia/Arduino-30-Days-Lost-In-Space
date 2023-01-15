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
-- Be sure to #define the CLK and DIO pins correctly! You should be able to then just upload and run it.
-- Arduino.h is found deep within the Arduino.app package: Local Disk (C:) > Program Files (x86) > Arduino > hardware > arduino > avr > cores > arduino > Arduino.h
--- You can also see the Arduino.h file at https://github.com/arduino/ArduinoCore-avr/tree/master/cores/arduino 
*/

// Define numbers:
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9

// Include the 7-segment display library
#include <Arduino.h> 
#include <TM1637Display.h> 

// Module connection pins (Digital Pins)
#define CLK 6
#define DIO 5

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000
 
// Create display object of type TM1637Display:
TM1637Display mySmolBoiDisplay = TM1637Display(CLK, DIO);

//******************************************************************************************************//
 
void setup() {
}
 
void loop() {
 mySmolBoiDisplay.setBrightness(0x0f); // hex 0f is the same as decimal 15
 uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 }; //all segments off
 mySmolBoiDisplay.setSegments(data);
 
 int code1 = TWO*10+THREE ;
 mySmolBoiDisplay.showNumberDec(code1, false, 3, 1); // first code
 //  false doesn't show leading zeros, 3 means show three digits,
 //  1 means start in position one (where the first position is zero)
 delay(TEST_DELAY);
 mySmolBoiDisplay.setSegments(data);
 
 
 int code2 = THREE*100+FIVE*10+THREE ;
 mySmolBoiDisplay.showNumberDec(code2, true, 3, 1); //second code
 delay(TEST_DELAY);
 mySmolBoiDisplay.setSegments(data);
 
 int code3 = 1000+SIX*100+EIGHT*10+EIGHT ;
 mySmolBoiDisplay.showNumberDec(code3, true, 4, 0); //third code
 delay(TEST_DELAY);
}
