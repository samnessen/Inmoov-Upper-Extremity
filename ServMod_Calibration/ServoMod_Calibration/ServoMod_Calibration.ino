/*************************
 * HACKED SERVO FOR CONTINUOUS ROATATION
 * TO FIND STALL A STALL POSITION
 ************************/

#include<Servo.h>

#define SERVO 5
Servo servo;

void setup() 
{
  servo.attach(SERVO);
  servo.writeMicroseconds(1800);
  /** THETA DIRECTION WHERE 1800 IS MIDPOINT
      ( 1300 < 1800 < 2500 ) 
  */
}

void loop() 
{
  servo.writeMicroseconds(1800); 
}
/**END*/
