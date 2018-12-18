/*  Open Bionics - MyoWare Sensor Test
*   Author - Olly McBride
*   Date - August 2016
*
*   This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*   To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*   Website - http://www.openbionics.com/
*   GitHub - https://github.com/Open-Bionics
*   Email - ollymcbride@openbionics.com 
*
*   MyoWare_Sensor_Test.ino
*
*/

// select the number of EMG channels to use (1 or 2)
#define NUM_EMG_CHANNELS  2

// select the hand/board that you are using by uncommenting one of the following
//#define ADA_HAND        // Almond PCB
#define BRUNEL_HAND     // Chestnut PCB







#if (NUM_EMG_CHANNELS < 1) || (NUM_EMG_CHANNELS > 2)
#error "This software only supports a maximum of 2 EMG channels"
#endif

#if defined(ADA_HAND)
#define MYSERIAL Serial
#elif defined(BRUNEL_HAND)
#define MYSERIAL SerialUSB
#else
#error "Please uncomment a board type on line 20/21"
#endif

// EMG PRINS
int EMGpin[NUM_EMG_CHANNELS];

void setup() 
{
  // initialise serial communications at 38400 baud
  MYSERIAL.begin(38400);


  // attach the pins based on the board being used
#if defined(ADA_HAND)
    EMGpin[0] = A6;
  #if (NUM_EMG_CHANNELS > 1)
    EMGpin[1] = A7;
  #endif
#elif defined(BRUNEL_HAND)
    EMGpin[0] = A4;
  #if (NUM_EMG_CHANNELS > 1)
    EMGpin[1] = A5;
  #endif
#endif
  
}

void loop() 
{
  int sensorValue;

  // count through the EMG channels
  for(int i = 0; i < NUM_EMG_CHANNELS; i++)
  {
    // read the analog in value:
    sensorValue = analogRead(EMGpin[i]);

    // print the results to the serial monitor
    MYSERIAL.print("Ch");
    MYSERIAL.print(i);
    MYSERIAL.print(": ");
    MYSERIAL.print(sensorValue);
    MYSERIAL.print("\t");
  }
  MYSERIAL.print("\n");

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last readings
  delay(2);
}
