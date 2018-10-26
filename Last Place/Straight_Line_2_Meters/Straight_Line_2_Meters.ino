int motorLFeedback = 2;             //Left Motor Feedback
int motorRFeedback = 3;             //Right Motor Feedback

volatile int leftCount = 0;
volatile int rightCount = 0;
int startingSpeed = 150;
int rms = startingSpeed;
int lms = startingSpeed;
int baseSpeed = 180;

void leftPulse(){
    leftCount++;
}

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

void loop() {
 check();
 forward();
 if ((rightCount >= 1168) || (leftCount >= 1168)){
    stop();
    delay(10000);
 }
 
 delay(500);
 if (startingSpeed < baseSpeed){
  startingSpeed += 2;
 }
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
