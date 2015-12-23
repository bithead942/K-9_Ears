/* 
K9 Ears Sketch
by Bithead942

Board:  Arduino Uno

Controls the movement of K9's ears.  During normal operation, the ears move back and forth
in opposite directions.  When a noise is heard, both ears point to the direction of the sound 
temporarily, then revert back to normal operation.  A "volume knob" is used to adjust the 
sensitivity to sound.  

For the ear sensors, I selected the Adafruit Electret Microphone Amplifier - MAX9814 with Auto 
Gain Control.  It helps automatically adjust the sensitivity for minor adjustments.
https://www.adafruit.com/products/1713

Pins:
   0 - Serial TX
   1 - Serial RX
   3 - Left Ear Servo
   5 - Right Ear Servo

  A0 - Right Ear microphone
  A1 - Left Ear microphone
  A2 - 10K Potentiometer to adjust microphone sensitivity

 */

#include <Servo.h>

const int _TICK = 9;
const int _SOUNDDETECT = 2500;
const int _RightEarSensor = A0;    //Analog Pin 0
const int _LeftEarSensor = A1;   //Analog Pin 1
const int _ThresholdPin = A2;      //Analog Pin 2
const int _LeftEarServo = 3;
const int _RightEarServo = 5;

int iState = 0;
int EarInVal = 0;
int iEar = 0;
int Threshold = 600;

Servo LeftEar;  
Servo RightEar;

void setup() {

 pinMode(_LeftEarServo, OUTPUT);  //Left ear servo
 pinMode(_RightEarServo, OUTPUT);  //Right ear servo
 pinMode(_LeftEarSensor, INPUT);  //Left ear sensor
 pinMode(_RightEarSensor, INPUT);  //Left ear sensor
 pinMode(_ThresholdPin, INPUT);  //pot

 LeftEar.attach(_LeftEarServo);
 RightEar.attach(_RightEarServo);
 //Serial.begin(9600);
}

void loop() {
  
  for(iEar = 0; iEar < 180; iEar += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    LeftEar.write(iEar);              // tell servo to go to position in variable 'iEar' 
    RightEar.write(180-iEar);
    Threshold = analogRead(_ThresholdPin);
    //Serial.println(Threshold);
    EarInVal = analogRead(_LeftEarSensor); 
    if (EarInVal >= Threshold) ListenLeft();
    EarInVal = analogRead(_RightEarSensor);    
    if (EarInVal >= Threshold) ListenRight();
    delay(_TICK);                       // waits for the servo to reach the position 
  } 
  for(iEar = 180; iEar>=1; iEar-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    LeftEar.write(iEar);              // tell servo to go to position in variable 'iEar' 
    RightEar.write(180-iEar);
    Threshold = analogRead(_ThresholdPin);
    //Serial.println(Threshold);
    EarInVal = analogRead(_LeftEarSensor); 
    if (EarInVal >= Threshold) ListenLeft();
    EarInVal = analogRead(_RightEarSensor);    
    if (EarInVal >= Threshold) ListenRight();
    delay(_TICK);                       // waits for the servo to reach the position 
  } 
}

void ListenLeft() {    //Point both ears to the left
    LeftEar.write(0);
    RightEar.write(0);
    iEar = 0;
    delay(_SOUNDDETECT);
}
void ListenRight() {   //Point both ears to the right
    LeftEar.write(180);
    RightEar.write(180);
    iEar = 180;
    delay(_SOUNDDETECT);
}
