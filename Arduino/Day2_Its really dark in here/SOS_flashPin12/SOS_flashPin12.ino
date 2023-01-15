/* Example that demonstrates the use of analog output (PWM) to flash an LED. 
 (1) A wire is used to connect Hero Board [Digital Pulse Width Modulation (PWM), 12] to Breadboard [6b]. *wires are used to connect circuits.
     Vcc: V stands for 'supply voltage at the common collector' while cc indicates voltage is positive. Positive supply voltage is labeled Vcc. 
     If the charge is positive, it's circuit is a neg-pos-neg circuit. The common collector is responsible for the power coming from the base and the collector, while OUTPUT is from the emitter-collector circuit. 
     
     PWM is a technique for getting analog (on/off) results with digital means. Digital control is used to create a square wave, a signal switched between on and off.
     In this example, the ON-OFF pattern can simulate voltages in between the full Vcc of the board (e.g., ON = 5v on UNO) and OFF = 0 Volts by changing the portion of time the signal spends ON verses the time that the signal spends OFF.
     CODE: Setup and Loops are statements that control the Hero Board to provide voltage to a particular location. 

     Step 1: Define variable named 'Light' that has a value of 12, which is an assigned Hero Board pin location. 
     Reminder: Light is a synonym for the pin number 12 and will refer to this location if called via statements. 
     
     Step 2: Use command pinMode 
     Setup section turns Light variable ON and loop commands Hero Board to turn Light variable OFF for 2 seconds, then ON for 1/10th seconds, repeating etc. 
     If wire was connected to [Power 5v], LED illuminates bright constant light.
     If wire was connected to [Power 3.3v], LED illuminates dull constant light. 
      flash an LED. 
     
 (2) The current passes through a 220 OHM Resister at Breadboard slots [6e]-[10e].
     Equation: CURRENT = VOLTAGE/RESISTANCE -> 0.023 Amperes = 5 Volts/220 OHM Resister. 
     0.023 Amps is enough for LED to convert electrical energy into light without burning the diode.
     
 (3) LEDs only work if current flows in a particular direction that is IN through the long prong [HIGH volgage side 5v, Breadboard 10c] and OUT through the short prong [LOW voltage side 0v, Breadboard 11c].
 
 (4) Another wire is used to connect BreadBoard [11a] to HERO Board [Power GND]. This completes the circuit. 

*/

// Assign Variables
int Light = 12; //Hero board pin 12

void setup() {
  // initialize the HERO...put your setup code here, to run once:
  pinMode(Light, OUTPUT); //initialize a digital pin as an output, then set its value to HIGH (5 volts)
  digitalWrite(Light, HIGH);
  
}

void loop() {
  // the code placed here will run repeatedly until HERO is turned off...put your main code here, to run repeatedly:
  digitalWrite(Light, LOW);
  delay(2000);
  digitalWrite(Light, HIGH);
  delay(100);
}
