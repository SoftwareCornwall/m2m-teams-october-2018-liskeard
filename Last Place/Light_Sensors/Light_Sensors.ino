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
}


void loop() {
  Serial.println(leftReading());
  Serial.println(rightReading());
  Serial.println(centreReading());

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
  
  delay(100);
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
