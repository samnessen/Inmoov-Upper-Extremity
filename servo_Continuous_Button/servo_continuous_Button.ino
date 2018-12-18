/** CODE IS USED WITH INTERRUPT FUNCTION OF TWO PUSH BUTTONS 
  * FOR THE CONTROL OF CONTINUOUS MOTION OF A MODIFIED SERVO
  * 
  * VOID LOOP AND PINMODE CAN BE COMMENTED FOR THE SOLE USE
  * OF A POTIENTIOMETER CONTROLLING MOTION
  * 
  * CODE WRITTEN BY: SAMUEL NESSENTHALER
  * DATE: 12-04-18
  */

#include<Servo.h>

Servo servo;
//DEFINE PINS FOR ARDUINO
#define PIN_RIGHT_MOVE A6
#define PIN_LEFT_MOVE A5
#define SERVO 5

void setup() 
{
  servo.attach(SERVO);
  servo.writeMicroseconds(1800);
  /** THETA DIRECTION WHERE 1800 IS MIDPOINT
      ( 1300 < 1800 < 2500 ) 
  */
  //ASSIGN PINS AND THEIR FUNCTIONALITY
  pinMode(PIN_RIGHT_MOVE, INPUT);
  pinMode(PIN_LEFT_MOVE, INPUT);
}

void loop() 
{
  //COMMENT OUT IF/ ELSE IF ONLY USING POT TO CONTROL DIRECTION
  if ( digitalRead(PIN_RIGHT_MOVE) == HIGH) 
    { servo.writeMicroseconds(2500);  }
  else if ( digitalRead(PIN_LEFT_MOVE) == HIGH) 
    { servo.writeMicroseconds(1300);  }
  else { servo.writeMicroseconds(1800); }
}
/**END*/
