/*This example demonstrates ***

The circuit starts with wire connecting 5v -- right BB20f. Photoresistor is located 20j -- 18j. 220 ohm resistor is placed 18h -- 15h.
Another wire connects 15f -- HERO digital gnd. Then connected wire from HERO power gnd -- 20h (returns 1023).
If that wire is connected to 15j it returns 0. 
The onboard LED corresponding to output 13 is now flashing at a rate that's determined by the light falling on the photoresistor.
If you shine a flashlight the LED is on/off for a long time. When light is gone, it blinks more rapidly (on/off shorter). 
*/

int sensorPin = A0; // select the *analog zero* input pin for probing the photoresistor
int onboardLED = 13; // select the pin for the HERO's built-in LED
int sensorValue = 0; // variable that we'll use to store the value reading from the sensor

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // sends us info at a rate of 9600 bits per second or 9600 baud.
  pinMode(onboardLED, OUTPUT);
}

void loop() {
  // Pulse the builtin LED for a time determined by the sensor output
  sensorValue = analogRead(sensorPin); //measure using analogRead the value of the voltage on sensorPin (0-1023). 
  digitalWrite(onboardLED, HIGH);
  delay(sensorValue); // if light is bright the LED will stay on for a long time.
  digitalWrite(onboardLED, LOW);
  delay(sensorValue); // if light is dim the LED will be on for a shorter time. 
  
  // Read the analog sensor value and send it to serial. 
  Serial.println(sensorValue);
  delay(500);
}
