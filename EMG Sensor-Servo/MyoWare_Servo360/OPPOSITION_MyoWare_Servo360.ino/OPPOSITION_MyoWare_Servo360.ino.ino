//Written by sparkFun
//Modified by Samuel Nessenthaler


#include <Servo.h>

//Threshold for servo motor control with muscle sensor
//Threshold set to max and min values of the muscle sensor
#define BICEP_THRESHOLD 850
#define TRICEP_THRESHOLD 850
#define BICEP_EMG_PIN 6
#define TRICEP_EMG_PIN 5
#define BICEP_SERVO_PIN 5

Servo servoBicep;

void setup() {
  Serial.begin(9600);
  servoBicep.attach(BICEP_SERVO_PIN);
}
void loop() {
  int bicepADC = analogRead(BICEP_EMG_PIN);
  int tricepADC = analogRead(BICEP_EMG_PIN);
    if (bicepADC > BICEP_THRESHOLD){ servoBicep.writeMicroseconds(2500); }
     else if (tricepADC > TRICEP_THRESHOLD){ servoBicep.writeMicroseconds(1300); }
      else    { servoBicep.writeMicroseconds(1800); } 
  Serial.println(bicepADC);
  Serial.println(tricepADC);

}
