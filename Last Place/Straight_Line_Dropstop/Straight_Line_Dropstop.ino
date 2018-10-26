/*This is a large group of variables that are being set up with their appropriate values.
For example, the motors are being enabled, and the forward and backwards for each are being 
assigned to their pins on the breadboard and the rover.*/
const int motorLFeedback = 2;
const int motorRFeedback = 3;
volatile int leftCount = 0;
volatile int rightCount = 0;
int startingSpeed = 150;
int rms = startingSpeed;   //The rms/lms is the left and right motor speeds, whose values will change thorughout the code accoridng to whther we want the rover to 
int lms = startingSpeed;   //accelerate, increment under a set of parameters or remain the same.
int baseSpeed = 180;

#include <NewPing.h>

#define TRIGGER_PIN  13 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     17  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void leftPulse(){
    leftCount++;
}

void rightPulse(){
    rightCount++;
}


/*This initialises the motor variables as outputs and the the counting of the pulses as inputs.*/
void setup() {
  setupPins();
  
  pinMode(motorLFeedback, INPUT_PULLUP);
  pinMode(motorRFeedback, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motorLFeedback), leftPulse, RISING);
  attachInterrupt(digitalPinToInterrupt(motorRFeedback), rightPulse, RISING);
  
  Serial.begin(115200);
}



/*Within this loop, the rover's sensors send and receive a signal.
If the signal is received and feeds back as the object being within 20cm of the rover
then the rover stops and makes a 90-degree right turn. */
void loop() {
 delay(100);
 int cm = sonar.ping_cm();
 
 if (cm > 13) {
  stop();
  int stopCount = rightCount;
  delay(1000);
  reverse();
  delay(300);
  stop();
  delay(100000);
 }
 
 check();
 forward(rms,lms);
 if (startingSpeed < baseSpeed){
  startingSpeed += 2;
 }                                //This is for a slow acceleration of the rover, rather than a jolting start.
}

void check() {
  if (rightCount == leftCount) {
    rms = startingSpeed;
    lms = startingSpeed;
  }
  if (rightCount > leftCount) {
    lms = startingSpeed + 75;
    rms = startingSpeed;
  }
  if (leftCount > rightCount) {
    rms = startingSpeed + 75;
    lms = startingSpeed;
  }
}

