/* This example demonstrates how to remotely activate the circuit that illuminates the LED by providing a signal INPUT into pin 2 of the HERO.
HERO makes a decision based on inputs provided to it's input pin.

TERMS:
 * digitalWrite(pin, value) is a 'Digital I/O Function' that allows you to assign a HIGH (5v) or LOW (0v, GND) value to a digital pin. 
 * pinMode(pin, mode) is a 'Digital I/O Function' that allows you to configure a specified pin to behave as an INPUT, OUTPUT, or INPUT_PULLUP.
 * digitalRead(pin) is a 'Digital I/O Function' that allows you read the value from a specified digital pin, returning either HIGH or LOW. 
 * Dual Inline Plastic (DIP) Switch is a discrete Breadboard component that acts as an electrical drawbridge when switched to ON. 

   The circuit begins at pin 12 and connects to BB12a. Current then travels through 220 OHM resister to positive terminal of LED BB12j(long prong) and out BB11j (negative terminal, short prong).
   Next a return path wire connects 11h to BBgnd (-), then a another wire connects BBgnd (-) to HEROgnd. The entire BBgnd (-) row is GND as a result. 
   The other circuit controls the HERO with an INPUT from Switch1. Starts at 5v to BB23h, Switch1 23f-e, input to HERO BB23b-HERO pin 2, resister 23a to BBgnd(-). 

OBSERVATIONS:
 * If Switch1 is OFF and you remove adjacent resister, LED starts flashing.
 * If Switch1 is ON and you remove adjacent resister, LED continues flashing. 
   The resulting current would be huge, probably more than the current the HERO can supply. HERO input pin2 has indeterminate voltage, creates short circuit, pssible damage wire or HERO.  
 * If switch is closed, the resister in the switch circuit functions as a current limiting resistor. Prevents short circuit and results in 5v at pin 2. 
 * If switch is open, the resister in the switch circuit functions as a pull-down resistor. Resistor pulls the voltage at pin 2 down to 0v.  
 * Flashing lights conserve battery power better than constant light.
*/

int LED = 12;
int Switch1 = 2; //pin 2 will be attached to our switch. 

void setup() {
  // setup both an output AND an input on the HERO. 
  pinMode(LED, OUTPUT);
  pinMode(Switch1, INPUT);
}

void loop() {
  // now within loop() we'll take actions based on the status of the input switch.

  // this is a conditional test...

  if (digitalRead(Switch1) == HIGH){
    digitalWrite(LED, LOW);       // turn LED OFF
    delay(1000);                  // wait 1 second
    digitalWrite(LED, HIGH);      // turn LED ON
    delay(100);                   // wait 1/10 of a second
    digitalWrite(LED, LOW);       // turn LED OFF
    delay(100);                   // wait 1/10 of a second
    digitalWrite(LED, HIGH);      // turn LED ON
    delay(100);                   // wait 1/10 of a second
  }
  else {
    digitalWrite(LED, LOW); // turn LED OFF
  }
}
