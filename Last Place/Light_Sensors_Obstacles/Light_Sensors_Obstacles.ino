const int motorLFeedback = 2;
const int motorRFeedback = 3;
volatile int leftCount = 0;
volatile int rightCount = 0;
int startingSpeed = 150;
int rms = startingSpeed;   //The rms/lms is the left and right motor speeds, whose values will change thorughout the code accoridng to whther we want the rover to 
int lms = startingSpeed;   //accelerate, increment under a set of parameters or remain the same.
int baseSpeed = 180;
const int lightSensorLeft = 14;
const int lightSensorMiddle = 15;
const int lightSensorRight = 16;
int threshold = 200;
boolean foundLight = false;

#include <NewPing.h>

#define TRIGGER_PIN  4     // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5     // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonarF(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#define TRIGGER_PIN_D  13 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_D    17  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE_D 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonarD(TRIGGER_PIN_D, ECHO_PIN_D, MAX_DISTANCE_D); // NewPing setup of pins and maximum distance.


void leftPulse(){
    leftCount++;
}

void rightPulse(){
    rightCount++;
}


void setup() {
  setupPins();
  pinMode(motorLFeedback, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motorLFeedback), leftPulse, RISING);
  pinMode(motorRFeedback, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motorRFeedback), rightPulse, RISING);
  Serial.begin(115200);

  sonarF.ping_cm();
  sonarD.ping_cm();
}


void loop() {
  delay(100);

  if ((leftReading() < threshold) || (rightReading() < threshold) || (centreReading() < threshold)){
    foundLight = true;
  }
  else {
    foundLight = false;
    stop();
  }

  
  if (foundLight) {
    if ((centreReading() < leftReading()) && (centreReading() < rightReading())) {
      forward(150,200);
    }
    else if (leftReading() > centreReading()) {
      forward(0, 200);
    }
    else if (rightReading() > centreReading()) {
      forward(150, 0);
    }
  }

  
  else {
    leftTurn(10);
  }
  
 int cm = sonarF.ping_cm();
  if ((cm < 8) && (cm > 0)) {
    stop();
    delay(3000);
    foundLight = false;
  }

  delay(50);

  int cm2 = sonarD.ping_cm();
  if (cm2 > 13) {
    stop();
    delay(3000);
    foundLight = false;
  }
}


float leftReading(){
  return analogRead(7);
}

float rightReading(){
  return analogRead(2);
}

float centreReading(){
  return analogRead(6);
}
