/*This examples demonstrates how to monitor battery levels using percentages, conditional logic statements, 
a photoresistor, RGB LED, and PWM pins. 
Shining a light on the photoresistor will speed up charging rate. */

int sensorPin = A0; // select the *analog zero* input pin for probing the photoresistor. 
int sensorValue = 0; // variable that we'll use to store the value reading from the sensor.

int red = 11; // these are our output pins for three LED colors
int green = 10;
int blue = 9;

unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;
unsigned int ticks = 0;
unsigned int wait = 100;
double PercentFull;

//***************************************************************

void setup() {
  // declare the RGB LED pins as outputs:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  // start serial monitor:
  Serial.begin(9600);
}

//***************************************************************

void RGB_color(int red_value, int green_value, int blue_value) {
// custom function to set three PWM color channels to any given mixture
// it returns No numerical result (void)
  
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
}

//***************************************************************

double getBatteryPercentage() {
// custom function calculates battery charge percentage
// and returns the result as a double precision number

  return (((double)batteryLevel / (double)batteryCapacity)*100);
}

//***************************************************************

void showBatteryPercentage () {
// send battery results to both serial and LED outputs

  PercentFull=getBatteryPercentage();

// print the elapsed time
  Serial.print(ticks);
  Serial.print(" ms   charge at ");
// print the percent charge
  Serial.print(PercentFull);
// print a percent character and line return...
  Serial.println("%");

// now let's light the LED with the appropriate color...

  if (PercentFull > 0 && PercentFull <= 25) {
    RGB_color(125, 0, 0); // Red
  }

  else if (PercentFull > 25 && PercentFull <= 50) {
    RGB_color(125, 80, 0); // Yellow-ish
  }

  else if (PercentFull > 50 && PercentFull <= 75) {
    RGB_color(0, 125, 125); // Blue-ish
  }

  else if (PercentFull > 75 && PercentFull < 100) {
    RGB_color(125, 125, 125); // White
  }
}
//***************************************************************

void loop() {
  sensorValue = analogRead(sensorPin); // read the value from the sensor pin (0-1023):
  batteryLevel += sensorValue; // shorthand for "Take battery level and add sensor value to it and put back in battery level".
  ticks += wait; // shorthand for "Take ticks and add wait time value to it and put it back in ticks". 

  if(batteryLevel >= batteryCapacity) {
    Serial.print(ticks);
    Serial.print(" ms   ");
    Serial.println("FULLY CHARGED");
    batteryLevel = batteryCapacity; // to prevent integer from continuing to increase
    ticks = 0;
    RGB_color(0, 125, 0); // Green for charging complete
    delay(30000); //long pause
  }

  else {
    showBatteryPercentage();
  }

  delay(wait);
}
