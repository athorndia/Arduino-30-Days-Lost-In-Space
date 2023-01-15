         /*This example demonstrates how to independently illuminate 3 LEDs using a DIP switch. 
The circuit begins at 5v--BB(top right +), current travels down BB to 3 wires that connect BB(bottom right +++)--26h,27h,28h.
DIP Switch bridges R-L. Next, wires connect 26c,27c,28c--pins 4,3,2 respectively. 3 adjacent resisters connect to BBgnd.
Lastly, wires connects BBgnd(top left -) to HEROgnd */

int LED1 = 10; //pins 10-12 are to be LED OUTPUTS
int LED2 = 11;
int LED3 = 12; 
int Switch1 = 2; //pins 2-4 are to be switch inputs
int Switch2 = 3;
int Switch3 = 4;

void setup() {
  // now setup our INPUT and OUTPUT pins accordingly
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(Switch1, OUTPUT);
  pinMode(Switch2, OUTPUT);
  pinMode(Switch3, OUTPUT);

}

void loop() {
// now within loop() we'll take actions based on the status of the switches

// testing

  if (digitalRead(Switch1) == HIGH){ //check switch #1
    digitalWrite(LED1, HIGH); //turn LED ON
  }
  else {
    digitalWrite(LED1, LOW); //turn LED OFF
  }

  if (digitalRead(Switch2) == HIGH){ //check switch #2
    digitalWrite(LED2, HIGH); //turn LED ON
  }
  else {
    digitalWrite(LED2, LOW); //turn LED OFF
  }

  if (digitalRead(Switch3) == HIGH){ //check switch #3
    digitalWrite(LED3, HIGH); //turn LED ON
  }
  else {
    digitalWrite(LED3, LOW); //turn LED OFF 
  }
}
