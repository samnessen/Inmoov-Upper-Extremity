/*********************************************************************
 * **** INMOOV ON NANO 1 ****
 * Code is applied to INMOOV, an open source robot 
 * and the movement of its right upper extremity.
 * 
 * Code uses five flex sensors to control 
 * five HS-422 servo motors at theta 0 - 180 deg.
 *
 * One soft potentiometer controls the wrist
 * with HS-422 servo motor at theta 0-180 deg.
 * 
 * 4 modified servos control the upper arm by 
 * a potentiometer stalling at 1800 milliseconds
 * using various components for motion in -+THETA:
 *
 * Two Myoware EMG sensors control the shoulder rotation 
 * internally and externally with HS-805BB modified 
 * continuous rotation at theta (-360, +360). 
 *
 * Shoulder Flexion and Extension are controled by  
 * two push buttons for theta in negative and positive direction.
 *
 * Shoudler Abbduction and Adduction are
 * controlled by a on board potentiometer located on motor.
 *
 * Bicep is controled by two push buttons for 
 * theta in negative and positive direction.
 *
 * Battery used was 7.2v @3000mAh pwoering both MCU and servos.
 * 1 Arduino Nano powerd by battery and 5v for data transmission.
 *
 * x2 RJ45 cables where used for data transmission between control glove
 * and robot where two seperate lines running common and VCC.
 *
 * Code written by: Samuel Nessenthaler
 * Date: 12-15-18
 ********************************************************************/
#include <Servo.h> 

/** EMG SENSOR LIMITS FOR MOTION ACTIVATION*/ 
#define SHOULDER_EXT_THRESHOLD 850
#define SHOULDER_FLX_THRESHOLD 850
/** BICEP PINS FOR MOTION */
#define BIFLX_PIN_MOVE 13
#define BIEXT_PIN_MOVE 2
/** SHOULDER PINS FOR MOTION */
#define SHINTERNAL_PIN_MOVE 6
#define SHEXTERNAL_PIN_MOVE 7

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;
Servo servoBicep;
Servo servoExtFlex;
Servo servoRot;
//Servo servoABAD;

/** ASSIGN ANALOG PINS */
const int flexThumb = A0; 
const int flexIndex = A1;
const int flexMiddle = A2;
const int flexRing = A3;
const int flexPinky = A4;
//Servo servoWrist;
//const int softPotPin = A7;
const int shoudlerExt_ADC = A5;
const int shoudlerFlex_ADC = A6;

void setup() 
{ 
  Serial.begin(9600);
  /** SERVO: FINGERS */  
  servoThumb.attach(11);
  servoIndex.attach(12);
  servoMiddle.attach(9);
  servoRing.attach(10);
  servoPinky.attach(8);
  //servoWrist.attach(13);
  
 /** FOR CONTINUOUS MOTION OF MODIFIED SERVO 
  * STALL POINT IS AT 1800 milliSeconds   
  * ( 1300 < MID_POINT < 2500 ) */
  servoExtFlex.attach(5);
  servoRot.attach(4);
  servoBicep.attach(3);

  /** BICEP: EXTENSION & FLEXION PIN ASSIGNMENT AND INITIAL MOVEMENT */
  servoBicep.writeMicroseconds(1800);  
  pinMode(BIFLX_PIN_MOVE, INPUT);
  pinMode(BIEXT_PIN_MOVE, INPUT); 
  
  /** SHOULDER: ROTATION INTERNAL/ EXTERNAL @MIDPOINT */
  servoRot.writeMicroseconds(1800);
  pinMode(SHINTERNAL_PIN_MOVE, INPUT);
  pinMode(SHEXTERNAL_PIN_MOVE, INPUT
  );
  
  /** SHOULDER: ABBDUCTION/ ADDUCTION @MIDPOINT*/
  //servoABAD.writeMicroseconds(1800);
} 

void loop() 
{ 
  /** ANALOG PIN TO READ ADC VALUE */
  int flexPositionT = analogRead(flexThumb); 
  int flexPositionI = analogRead(flexIndex);
  int flexPositionM = analogRead(flexMiddle);
  int flexPositionR = analogRead(flexRing);
  int flexPositionP = analogRead(flexPinky);
  //int softPotWrist = analogRead(softPotPin);
  int shoudlerEx_ADC = analogRead(shoudlerExt_ADC);
  int shoudlerFx_ADC = analogRead(shoudlerFlex_ADC);

  /** ADC VALUES FROM 0-1023 CONVERTING TO 0-180 FOR SERVO OBJECTS */
  int servoPositionT = map(flexPositionT, 700, 850, 0, 180); 
      servoPositionT = constrain(servoPositionT, 0, 180);
  int servoPositionI = map(flexPositionI, 600, 900, 0, 180); 
      servoPositionI = constrain(servoPositionI, 0, 180);
  int servoPositionM = map(flexPositionM, 730, 870, 0, 180); 
      servoPositionM = constrain(servoPositionM, 0, 180);
  int servoPositionR = map(flexPositionR, 600, 900, 0, 180); 
      servoPositionR = constrain(servoPositionR, 0, 180);
  int servoPositionP = map(flexPositionP, 600, 900, 0, 180); 
      servoPositionP = constrain(servoPositionP, 0, 180);
  //int softPotPositionW = map(softPotWrist, 0, 1023, 0, 180); 
  //  softPotPositionW = constrain(softPotPositionW, 0, 180);
  
  /** SERVOS WIRTE GIVING ADC VALUE TO MOVE THETA 0-180 */
  servoThumb.write(servoPositionT);
  servoIndex.write(servoPositionI);
  servoMiddle.write(servoPositionM);
  servoRing.write(servoPositionR);
  servoPinky.write(servoPositionP);
  //servoWrist.write(softPotPositionW);

/** Servo for upper arm are continuous rotation at ( 1300 < midPoint@1800 < 2500 )
 *  Onboard potentiometer is part of a servo hack to modify continuous 
 *    rotation of theta in both positive and negative direction where midpoint is set.
 *  - BICEP and TRICEP, SHOULDER ROTATION at INTERNAL/EXTERNAL 
 *    are opposing movements using pushbuttons.
 *  - SHOULDER EXTENSION/ FLEXION  are opposing movements are controlled by EMG sensors. 
 *    uses onboard potentiometer where its set at 1800
 *    All three servos are set at a STALL POSITION 
 *    using potentiometer (1800 milliSec). Two buttons when pressed will rotate at max
 *    speed in either theata negative or theat positve direction respectfully.  
 */
  /** SHOULDER EXTENSION AND FLEXION */
  if (shoudlerEx_ADC > SHOULDER_EXT_THRESHOLD){ servoExtFlex.writeMicroseconds(2200); }
  else if (shoudlerFx_ADC > SHOULDER_FLX_THRESHOLD){ servoExtFlex.writeMicroseconds(1300); }
  else  { servoExtFlex.writeMicroseconds(1800); } 
      
  /** BICEP EXTENSION AND FLEXION */
    if ( digitalRead(BIFLX_PIN_MOVE) == HIGH) 
       { servoBicep.writeMicroseconds(2200);  }
    else if ( digitalRead(BIEXT_PIN_MOVE) == HIGH) 
       { servoBicep.writeMicroseconds(1300);  }
    else { servoBicep.writeMicroseconds(1800); }
    
  /** SHOULDER ROTATION - INTERNAL AND EXTERNAL */
    if ( digitalRead(SHINTERNAL_PIN_MOVE) == HIGH) 
       { servoBicep.writeMicroseconds(2200);  }
    else if ( digitalRead(SHEXTERNAL_PIN_MOVE) == HIGH) 
       { servoBicep.writeMicroseconds(1300);  }
    else { servoBicep.writeMicroseconds(1800); }
  //servoABAD.writeMicroseconds(1800);

  /** TERMINAL OUTPUT */
  Serial.print("FLEX SENSOR THUMB: ");
     Serial.print(flexPositionT);
      Serial.print("\nSERVO THUMB: ");
       Serial.println(servoPositionT);
        Serial.println("\n\n");
    Serial.print("FLEX SENSOR INDEX: ");
     Serial.print(flexPositionI);
      Serial.print("\nSERVO INDEX ");
       Serial.println(servoPositionI);
        Serial.println("\n\n");
    Serial.print("FLEX SENSOR MIDDLE: ");
     Serial.print(flexPositionM);
      Serial.print("\nSERVO MIDDLE: ");
       Serial.println(servoPositionM);
        Serial.println("\n\n");
    Serial.print("FLEX SENSOR RING: ");
     Serial.print(flexPositionR);
      Serial.print("\nSERVO RING: ");
       Serial.println(servoPositionR);
        Serial.println("\n\n");
    Serial.print("FLEX SENSOR PINKY: ");
     Serial.print(flexPositionP);
      Serial.print("\nSERVO PINKY: ");
       Serial.println(servoPositionP);
        Serial.println("\n\n"); 
 /*Serial.print("SOFT POT WRIST: ");
      Serial.print(softPotWrist);
        Serial.print("\nSERVO WRIST: ");
          Serial.println(softPotPositionW);
            Serial.print("\n\n"); */
   Serial.print("SHOULDER EXTENSION ADC VALUE: ");
    Serial.println(shoudlerEx_ADC);
      Serial.print("SHOULDER FLEXION ADC VALUE: ");
       Serial.println(shoudlerFx_ADC);
  
}
/** END */
