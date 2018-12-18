/*
InMoov and Glove Controller Implementation

With this Program I have made it so that you can now switch between the automatic
demonstration and control via the Glove Controller. When the switch is on the 0, the 
 program will be running.

Created by Travis Malo on 25 April 2017.
Updated by Travis Malo on 25 April 2017.
Modified by Jim Heffernan on September 27 2017
*/

#include <Servo.h>      
int WristPin = 0;       //Names the pins for each flex resistors according to function
int PinkyPin = 1;
int RingPin = 2;
int MiddlePin = 3;
int IndexPin = 4;
int ThumbPin = 5;       
int SelectorPin = 8;
Servo ThumbServo;       //Names the servos to their corresponding function
Servo IndexServo;
Servo MiddleServo;
Servo RingServo;
Servo PinkyServo;
Servo WristServo;

int maxThumbValue = 0;
int maxIndexValue = 0;
int maxMiddleValue = 0;
int maxRingValue = 0;
int maxPinkyValue = 0;
int maxWristValue = 0;

int minThumbValue = 1023;
int minIndexValue = 1023;
int minMiddleValue = 1023;
int minRingValue = 1023;
int minPinkyValue = 1023;
int minWristValue = 1023;

void setup() 
{
  ThumbServo.attach(2);        //Defines which pin is assigned to each servo
  IndexServo.attach(3);
  MiddleServo.attach(4);
  RingServo.attach(5);
  PinkyServo.attach(6);
  WristServo.attach(7);

  pinMode(SelectorPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() 
{
  bool currentSelectorState = digitalRead(SelectorPin);

  if (currentSelectorState)  // If the selector switch is TRUE, mark time of transition and run control program.
  {
    control();   // Run control program
  }

  else  // If the selector switch input is NOT TRUE, run demo.
  {
    demo();   
  }
}

void demo()
{
  Serial.println("Start of demo cycle.");
  PinkyServo.write(45);
  RingServo.write(25);
  MiddleServo.write(45);
  IndexServo.write(45);
  ThumbServo.write(65);
  WristServo.write(0);
  delay(500);
  WristServo.write(180);
  delay(500);
  WristServo.write(0);
  delay(500);
  WristServo.write(180);
  delay(500);
  WristServo.write(90);
  delay(2000);
  PinkyServo.write(180);
  RingServo.write(180);
  MiddleServo.write(180);
  IndexServo.write(180);
  ThumbServo.write(180);
  delay(2000);
  PinkyServo.write(45);
  RingServo.write(25);
  MiddleServo.write(45);
  IndexServo.write(45);
  ThumbServo.write(65);
  delay(2000);
  PinkyServo.write(180);
  delay(2000);
  PinkyServo.write(45);
  delay(2000);
  RingServo.write(180);
  delay(2000);
  RingServo.write(25);
  delay(2000);
  MiddleServo.write(180);
  delay(2000);
  MiddleServo.write(45);
  delay(2000);
  IndexServo.write(180);
  delay(2000);
  IndexServo.write(45);
  delay(2000);
  ThumbServo.write(180);
  delay(2000);
  ThumbServo.write(65);
  delay(2000);
  RingServo.write(180);
  MiddleServo.write(180);
  IndexServo.write(180);
  delay(100);
  WristServo.write(0);
  delay(500);
  WristServo.write(180);
  delay(500);
  WristServo.write(0);
  delay(500);
  WristServo.write(180);
  delay(500);
  WristServo.write(90);
  Serial.println("End of demo cycle.");
  delay(2000);
}

void control()
{
  int ThumbValue, IndexValue, MiddleValue, RingValue, PinkyValue, WristValue;
  int ThumbPWM, IndexPWM, MiddlePWM, RingPWM, PinkyPWM, WristPWM;

  ThumbValue = analogRead(ThumbPin);
  IndexValue = analogRead(IndexPin);
  MiddleValue = analogRead(MiddlePin);
  RingValue = analogRead(RingPin);
  PinkyValue = analogRead(PinkyPin);
  WristValue = analogRead(WristPin);

  if (ThumbValue > maxThumbValue) maxThumbValue = ThumbValue;
  if (IndexValue > maxIndexValue) maxIndexValue = IndexValue;
  if (MiddleValue > maxMiddleValue) maxMiddleValue = MiddleValue;
  if (RingValue > maxRingValue) maxRingValue = RingValue;
  if (PinkyValue > maxPinkyValue) maxPinkyValue = PinkyValue;
  if (WristValue > maxWristValue) maxWristValue = WristValue;

  if (ThumbValue < minThumbValue) minThumbValue = ThumbValue;
  if (IndexValue < minIndexValue) minIndexValue = IndexValue;
  if (MiddleValue < minMiddleValue) minMiddleValue = MiddleValue;
  if (RingValue < minRingValue) minRingValue = RingValue;
  if (PinkyValue < minPinkyValue) minPinkyValue = PinkyValue;
  if (WristValue < minWristValue) minWristValue = WristValue;

  int offset = 20;  // Offset used for mapping to ensure max value reaches actual max.

  ThumbPWM = map(ThumbValue, maxThumbValue, minThumbValue, 65-offset, 180+offset);
  ThumbPWM = constrain(ThumbPWM, 65, 180);

  IndexPWM = map(IndexValue, maxIndexValue, minIndexValue, 45-offset, 180+offset);
  IndexPWM = constrain(IndexPWM, 45, 180);

  MiddlePWM = map(MiddleValue, maxMiddleValue, minMiddleValue, 45-offset, 180+offset);
  MiddlePWM = constrain(MiddlePWM, 45, 180);

  RingPWM = map(RingValue, maxRingValue, minRingValue, 25-offset, 180+offset);
  RingPWM = constrain(RingPWM, 25, 180);

  PinkyPWM = map(PinkyValue, maxPinkyValue, minPinkyValue, 45-offset, 180+offset);
  PinkyPWM = constrain(PinkyPWM, 45, 180);

  WristPWM = map(WristValue, maxWristValue, minWristValue, 0-offset, 180+offset);
  WristPWM = constrain(WristPWM, 0, 180);

  ThumbServo.write(ThumbPWM);
  IndexServo.write(IndexPWM);
  MiddleServo.write(MiddlePWM);
  RingServo.write(RingPWM);
  PinkyServo.write(PinkyPWM);
  
  Serial.print("Flex Readings: T= "); 
  Serial.print(ThumbValue);
  Serial.print(", I= ");
  Serial.print(IndexValue);
  Serial.print(", M= ");
  Serial.print(MiddleValue);
  Serial.print(", R= "); 
  Serial.print(RingValue);
  Serial.print(", P= ");
  Serial.print(PinkyValue);
  Serial.print(", W= ");
  Serial.println(WristValue);
  Serial.print("; Servo Positions: T= "); 
  Serial.print(ThumbPWM);
  Serial.print(", I= ");
  Serial.print(IndexPWM);
  Serial.print(", M= ");
  Serial.print(MiddlePWM);
  Serial.print(", R= "); 
  Serial.print(RingPWM);
  Serial.print(", P= ");
  Serial.print(PinkyPWM);
  Serial.print(", W= ");
  Serial.println(WristPWM);

  delay(10);

}

