const int motorLFeedback = 2;       //Left Motor Feedback
const int motorRFeedback = 3;       //Right Motor Feedback

volatile int leftCount = 0;
volatile int rightCount = 0;
int startingSpeed = 150;            //The starting speed is quite low and it slowly increments so as to prevent any jolting when the rover first begins to move. The actual acceleration code is within the primary loop.
int rms = startingSpeed;
int lms = startingSpeed;
int baseSpeed = 180;

#include <NewPing.h>

#define TRIGGER_PIN  4     // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5     // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void leftPulse(){
    leftCount++;
}
                          //These pulses count teh interrupts caused by the motor turning. With each pulse, the left/rightCount increments. This allows us a measuring-stick of sorts for the distance travelled.
void rightPulse(){
    rightCount++;
}

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
then the rover stops and makes a 90-degree right turn. 
*/
void loop() {
 delay(100);
 int cm = sonar.ping_cm();
 if((cm < 20) && (cm > 0)){       //If the rover's sonar returns from in between 20 and 0cms away, i.e. when an object is close, the rover stops.
  stop();                         //The rover then stops, so it doesn't crash, and we aren't charged more.
  delay(1000);
  rightTurn();                    //After a single second delay to prevent any skidding or inconsistencies, the rover then makes a turn in preparation for heading in another direction.
  delay(10000000);                //There is a long delay to ensure the rover won't start moving again.
 }
 check();                         //We keep 'check' in this particular code so that the rover head stowards any objects in a staright line.
 forward(rms, lms);
 if (startingSpeed < baseSpeed){
  startingSpeed += 2;             //This section gradually increments the starting speed of '150' until its equals the basespeed of '180'. However, this loop runs often enough that this acceleration is actaully quite quick, but still enough to prevent any jolts at the start.
 }
}


/*This is the 'check' function mentioned above, which, dependent upon the left and right count values, 
will adapt the left and right motor speeds to correct the pace of the rover.*/
void check() {
  if (rightCount == leftCount) {  //When the two values are equal, the motors will be moving at their 'startingSpeed', which is equal.
    rms = startingSpeed;
    lms = startingSpeed;
  }
  if (rightCount > leftCount) {   //When the right count is greater than the left, the left motor speed is incremented until the counts are balanced out once more.
    lms = startingSpeed + 75;
    rms = startingSpeed;
  }
  if (leftCount > rightCount) {   //Much like the above 'if' statement, if the left count is too great, then the right motor speed is increased.
    rms = startingSpeed + 75;
    lms = startingSpeed;
  }
}
