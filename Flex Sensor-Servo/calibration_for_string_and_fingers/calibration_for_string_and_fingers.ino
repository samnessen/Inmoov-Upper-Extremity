/********************************************
calibrate servo for string placement
written by: samuel nessenthaler 
*********************************************/
#include <Servo.h> 

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;
Servo servoWrist;

void setup() 
{ 
  Serial.begin(9600);
  //Attach servos to digital pins on Arduino
  servoThumb.attach(11);
  servoIndex.attach(12);
  servoMiddle.attach(9); //PINKY, THUMB
  servoRing.attach(10); 
  servoPinky.attach(8);
  servoWrist.attach(7);
    //start motors at position = open hand 
    servoThumb.write(180);
    servoIndex.write(180);
    servoMiddle.write(180);
    servoRing.write(180);
    servoPinky.write(180);
    servoWrist.write(180);
} 

void loop() 
{ 

  //Servos for finger dexterity theta 0-180
  servoThumb.write(180);
  servoIndex.write(180);
  servoMiddle.write(180);
  servoRing.write(180);
  servoPinky.write(180);
  servoWrist.write(180);
   delay(1000);
    servoThumb.write(0);
    servoIndex.write(0);
    servoMiddle.write(0);
    servoRing.write(0);
    servoPinky.write(0);
    servoWrist.write(0);
    delay(1000);
}
/** END */
