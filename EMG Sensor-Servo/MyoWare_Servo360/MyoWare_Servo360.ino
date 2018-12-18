//Written by SparkFun
//Modified by Samuel Nessenthaler


#include <Servo.h>

//Threshold for servo motor control with muscle sensor
//Threshold set to max and min values of the muscle sensor
#define BICEP_THRESHOLD 850
#define BICEP_EMG_PIN 0
#define BICEP_SERVO_PIN 3

Servo servoBicep;

void setup() {
  Serial.begin(9600);
  servoBicep.attach(BICEP_SERVO_PIN);
}

void loop() {
  int bicepADC = analogRead(BICEP_EMG_PIN);
  if (bicepADC > BICEP_THRESHOLD){ servoBicep.writeMicroseconds(2500); }
    else if (bicepADC > (BICEP_THRESHOLD - 500) && bicepADC < BICEP_THRESHOLD) 
        { servoBicep.writeMicroseconds(1300); }
    else { servoBicep.writeMicroseconds(1800); }
  Serial.println(bicepADC);
}
