/*******************************************
Using a flex sensor to move a motor 180 deg

Created by: SparkFun Inventor's Kit for Arduino
            Example sketch 09
Modiefied by: Samuel Nessenthaler
Date: 10-07-18
********************************************/

#include <Servo.h> 

Servo servoThumb;
const int flexThumb = A2; 

void setup() 
{ 
  Serial.begin(9600);
  //Attach to pin on Arduino
  servoThumb.attach(9);
} 

void loop() 
{ 
  int flexPosition; 
  int servoPosition; 
  //Assign analog pin to flexPosition
  flexPosition = analogRead(flexThumb);

  //All stable values from flex to motor 
  servoPosition = map(flexPosition, 730, 870, 0, 180); // (600,900)
  servoPosition = constrain(servoPosition, 0, 180);
  
  //Servo move to position
  servoThumb.write(servoPosition);
 
  Serial.print("FLEX SENSOR: ");
  Serial.print(flexPosition);
  Serial.print("\nSERVO THUMB: ");
  Serial.println(servoPosition);
    Serial.print("\n\n");
  
  
}
/** END */
