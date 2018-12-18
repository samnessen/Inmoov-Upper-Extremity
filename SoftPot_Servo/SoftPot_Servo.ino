/******************************************************************************
SoftPot_Example.ino
Example sketch for SparkFun's soft membrane potentiometer
  (https://www.sparkfun.com/products/8680)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

- Connect the softpot's outside pins to 5V and GND (the outer pin with an arrow
indicator should be connected to GND). 
- Connect the middle pin to A0.

As the voltage output of the softpot changes, a line graph printed to the
serial monitor should match the wiper's position.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
#include <Servo.h> 

const int SOFT_POT_PIN = A7; // Pin connected to softpot wiper
//const int GRAPH_LENGTH = 40; // Length of line graph
Servo servoThumb;

void setup() 
{
  Serial.begin(9600);
  pinMode(SOFT_POT_PIN, INPUT);
  servoThumb.attach(13);
}

void loop() 
{
  // Read in the soft pot's ADC value
  int softPotADC = analogRead(SOFT_POT_PIN);
  // Map the 0-1023 value to 0-40
  int softPotPosition = map(softPotADC, 0, 1023, 0, 180); //changed graph_length to 180
  softPotPosition = constrain(softPotPosition, 0, 180);

  servoThumb.write(softPotPosition);
 
  Serial.print("soft pot: ");
  Serial.print(softPotADC);
  Serial.print("\nSERVO THUMB: ");
  Serial.println(softPotPosition);
    Serial.print("\n\n");
  
  /* Print a line graph:
  Serial.print("<"); // Starting end
  for (int i=0; i<GRAPH_LENGTH; i++)
  {
    if (i == softPotPosition) Serial.print("|");
    else Serial.print("-");
  }
  Serial.println("> (" + String(softPotADC) + ")");

  delay(500);*/
}
