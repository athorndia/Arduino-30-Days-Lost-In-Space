/* This example demonstrates how a RBG LED changes from RED to YELLOW to GREEN according to battery level.
RED is low charge (0-50). YELLOW is moderate charge (51-95). GREEN is high charge (96-100).*/

// Variables
int green = 11; 
int red = 9;
int sensorPin = A0;
int sensorValue = 0; // variable that we'll use to store the value reading from the sensor
unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;
unsigned int ticks = 0;
unsigned int wait = 100;
double PercentFull;
double PercentLow;

void setup() {
  // put your setup code here, to run once:
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600);
}

void RGB_color(int green_value, int red_value) {
// custom function to set three PWM color channels to any given mixture
  analogWrite(green, green_value);
  analogWrite(red, red_value);
}

void PrintBatteryPercentage() {
// print the elasped time
  Serial.print(ticks); // prints the value of ticks/whatever the time is that's elapsed. 
  Serial.print(" ms   charge at ");

// convert the integers to decimal numbers, devide them and print...
  PercentFull = 100*((double)batteryLevel / (double)batteryCapacity);
  Serial.print(PercentFull);
  PercentLow < PercentFull;
  Serial.print(PercentLow);

// print a percent character and line return...
  Serial.println("%");
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin); // read the value from the sensor pin (0-1023):
  batteryLevel += sensorValue; // shorthand for "Take battery level and add sensor value to it and put back in battery level".
  ticks += wait; // shorthand for "Take ticks and add wait time value to it and put it back in ticks". 

  if(batteryLevel >= batteryCapacity) {
    Serial.print(ticks);
    Serial.print(" ms   ");
    Serial.println("FULLY CHARGED");
    batteryLevel = batteryCapacity; // to prevent integer from continuing to increase
    ticks = 0;
    RGB_color(0, 125, 0); // Green
    delay(20000); //long pause
  }

  else (batteryLevel < batteryCapacity) {
    Serial.print(ticks);
    Serial.print(" ms   ");
    RGB_color(125, 0, 0); // Red
    PrintBatteryPercentage();
    delay(800);
    Serial.println("LOW CHARGE");
    ticks = 0;
  }

  delay(wait);
}
