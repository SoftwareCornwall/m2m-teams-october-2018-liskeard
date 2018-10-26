// NOTE - Configured for Alan.

/* 
 *  DEMO:
 *  1. drives up the ramp and not off the edge.
 *  2. turn around 180 degrees
 *  3. once off the ramp it detects a box and 90 degrees left.
 *  4. it goes forwards and draws a box.
 *  5. It opens up a portal and drives out onto the martian surface.
 */
 
// Download NewPing library for ultrasonic sensors
#include <NewPing.h>

// Initialise control pins for PWM measures.
const int Left_Motor_Feedback = 2;
const int Right_Motor_Feedback = 3;

// Initialise control pins for the forward ultrasonic sensors
const int Sonic_Crash_Trigger = 4;
const int Sonic_Crash_Echo = 5;

//Initialise control pins for left motor control.
const int Left_Motor_Reverse = 7;
const int Left_Motor_Forward = 8;
const int Left_Motor_Enable = 9;

// Initialise control pins for right motor control.
const int Right_Motor_Enable = 10;
const int Right_Motor_Reverse = 11;
const int Right_Motor_Forward = 12;

// Initialise control pins for the down ultrasonic sensors
const int Sonic_Fall_Trigger = 13;
const int Sonic_Fall_Echo = 17;


// NewPing setup of pins and maximum distance.
NewPing sonarCrash(Sonic_Crash_Trigger, Sonic_Crash_Echo, 200);
NewPing sonarFall(Sonic_Fall_Trigger, Sonic_Fall_Echo, 200);

// Pulse interrupt variables measure the number of times each hall effect sensor has fired for PWM calculation.
volatile unsigned int left_count = 0;
volatile unsigned int right_count = 0;


// Motor Speeds
volatile int left_speed = 0;
volatile int right_speed = 0;

// These two functions will increment left_count and right_count by 1 respectivly when called.
void leftPulseInterrupt() {
  left_count++;
}

void rightPulseInterrupt() {
  right_count++;
}
// ---------------------------------------------------------------------------------------------------
void setup() {

  // Motor Setups
  pinMode(Left_Motor_Reverse, OUTPUT);
  pinMode(Left_Motor_Forward, OUTPUT);

  pinMode(Right_Motor_Reverse, OUTPUT);
  pinMode(Right_Motor_Forward, OUTPUT);

  pinMode(Left_Motor_Enable, OUTPUT);
  pinMode(Right_Motor_Enable, OUTPUT);

  enableMotors();

  // Sets up hall effect sensors to call the left and right pulse interrupt functions when they fire.

  pinMode(Left_Motor_Feedback, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Left_Motor_Feedback), leftPulseInterrupt, RISING);

  pinMode(Right_Motor_Feedback, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Right_Motor_Feedback), rightPulseInterrupt, RISING);
}

void loop() {
  /*driveBoxRight(80);
  delay(1000);
  driveBoxLeft(74);
  delay(1000);
  reverseDriveBoxRight(80);
  delay(1000);
  reverseDriveBoxLeft(72);
  delay(1000);*/
  straightForward(200);
  turnRight(180);
  straightForward(250);
  drawEdge(40);
  driveBoxRight(80);
  turnRight(80);
  exit(0);
}
// --------------------------------------------------------------------------------------------------
// Control Functions

// This function sets pwm on each motor to the current value of the variables left_speed and right_speed.
void enableMotors() {
  analogWrite(Right_Motor_Enable, right_speed);
  analogWrite(Left_Motor_Enable, left_speed);
}

// This function sets PWM to the max value it can be, using digitalWrite.
void fullMotors() {
  digitalWrite(Right_Motor_Enable, HIGH);
  digitalWrite(Left_Motor_Enable, HIGH);
}

// This function turns both motors on in the forward direction.
void fullForwardOn() {
  digitalWrite(Left_Motor_Forward, HIGH);
  digitalWrite(Left_Motor_Reverse, LOW);
  digitalWrite(Right_Motor_Forward, HIGH);
  digitalWrite(Right_Motor_Reverse, LOW);
}

// This function turns both motors off.
void motorsOff() {
  digitalWrite(Left_Motor_Forward, LOW);
  digitalWrite(Left_Motor_Reverse, LOW);
  digitalWrite(Right_Motor_Forward, LOW);
  digitalWrite(Right_Motor_Reverse, LOW);
}

// This function turns both motor on in both directions to bring the rover to an abrupt stop for 1 second.
// NOTE - It works the same as motorsOff in practise.
void brakesOn() {
  digitalWrite(Left_Motor_Forward, HIGH);
  digitalWrite(Left_Motor_Reverse, HIGH);
  digitalWrite(Right_Motor_Forward, HIGH);
  digitalWrite(Right_Motor_Reverse, HIGH);
  delay(1000);
}

// This function turns both motors on in reverse.
void fullReverseOn() {
  digitalWrite(Left_Motor_Forward, LOW);
  digitalWrite(Left_Motor_Reverse, HIGH);
  digitalWrite(Right_Motor_Forward, LOW);
  digitalWrite(Right_Motor_Reverse, HIGH);
}

/* This function will bring the rover to the speed given, with constant acceleration. Accelerates at 1 pwm every 5 milliseconds until 
   until it reaches the given speed. */
void slowStart(int vic_speed) {
  for (int i = 0; i <= vic_speed; i++) {
    left_speed = i;
    right_speed = i;
    enableMotors();
    delay(5);
  }
}

/* This function turns the left motor on in the forwards direction and the right motor on in the reverse direction for the given number of
   interrupts in order to rotate to the right, then comes to a stop. */
void turnRight(int pulses) {
  int start_count = left_count;
  left_speed = 200;
  right_speed = 200;
  enableMotors();
  digitalWrite(Left_Motor_Forward, HIGH);
  digitalWrite(Left_Motor_Reverse, LOW);
  digitalWrite(Right_Motor_Forward, LOW);
  digitalWrite(Right_Motor_Reverse, HIGH);
  while(left_count < start_count + pulses) {
    delay(5);
  }
  brakesOn();
}

/* This function turns the right motor on in the forwards direction and the left motor on in the reverse direction for the given number of
   interrupts in order to rotate to the left, then comes to a stop. */
void turnLeft(int pulses) {
  int start_count = right_count;
  left_speed = 200;
  right_speed = 200;
  enableMotors();
  digitalWrite(Left_Motor_Forward, LOW);
  digitalWrite(Left_Motor_Reverse, HIGH);
  digitalWrite(Right_Motor_Forward, HIGH);
  digitalWrite(Right_Motor_Reverse, LOW);
  while(right_count < start_count + pulses) {
    delay(5);
  }
  brakesOn();
}

// This function makes the rover travel in a straight line for a specified distance in cm.
// TO DO - Calibrate this function.
void straightForward(int distance) {
  left_speed = 0;
  right_speed = 0;
  delay(100);
  enableMotors();
  fullForwardOn();
  slowStart(150);

  int crashCount = 0;
  int fallCount = 0;


  bool breakFree = true;
  while (right_count <= (distance*4.52) and breakFree)
  {
    crashCount = dontCrash(crashCount);
    if (crashCount >= 3)
    {
      turnLeft(80);
      brakesOn();
    }
    fallCount = dontFall(fallCount);
    if (fallCount >= 3)
    {
      brakesOn();
      drawEdge(-800);
      breakFree = false;
    }
    if (breakFree)
    {
      if (left_speed < 100) {
        left_speed = right_speed;
      }
  
      if ((right_count / left_count) * left_speed <= 100) {
        delay(50);
      }
  
      else {
        left_speed = (right_count / left_count) * left_speed;
        enableMotors();
        delay(50);
      }
    }
  }
  brakesOn();
}


// This function takes a value which is used for the amount of time it travels. Postive values move forwards and negative values move backwards
void drawEdge(int len) {
  if (len > 0) {
    left_speed = 200;
    right_speed = 200;
    enableMotors(); 
    fullForwardOn();
    delay(len);
    brakesOn();
  }
  if (len < 0) {
    len -= 2*len;
    left_speed = 200;
    right_speed = 200;
    enableMotors();
    fullReverseOn();  
    delay(len);
    brakesOn();
    }
}

/* This function drives the rover in a box. First it goes forwards for 1 second then turns right 90 degrees. It repeats this 3 times.
   Finally, it drives forward for 1.3 second and stops. */

void driveBoxRight(int angle) // Angle stands for the number of pulses.
{
  drawEdge(1000);
  turnRight(angle);
  drawEdge(1000);
  turnRight(angle);
  drawEdge(1000);
  turnRight(angle);
  drawEdge(1300);
}

/* This function drives the rover in a box. First it goes forwards for 1 second then turns left 90 degrees. It repeats this 3 times.
   Finally, it drives forward for 1 second and stops. */
void driveBoxLeft(int angle) // Angle stands for the number of pulses.
{
  drawEdge(1000);
  turnLeft(angle);
  drawEdge(1000);
  turnLeft(angle);
  drawEdge(1000);
  turnLeft(angle);
  drawEdge(1200);
}

/* This function drives the rover in a box in reverse. First it goes backwards for 1 second then turns right 90 degrees. It repeats this
   3 times. Finally, it drives backward for 1 second and stops. */
void reverseDriveBoxLeft(int angle) // Angle stands for the number of pulses.
{
  drawEdge(-1000);
  turnLeft(angle);
  drawEdge(-1000);
  turnLeft(angle);
  drawEdge(-1000);
  turnLeft(angle);
  drawEdge(-1000);
}

/* This function drives the rover in a box reverse. First it goes backwards for 1 second then turns left 90 degrees. It repeats this 3 times.
   Finally, it drives backward for 1 second and stops. */
void reverseDriveBoxRight(int angle) // Angle stands for the number of pulses.
{
  drawEdge(-1000);
  turnRight(angle);
  drawEdge(-1000);
  turnRight(angle);
  drawEdge(-1000);
  turnRight(angle);
  drawEdge(-980);
}

// This function calls the two box functions in order to draw a figure 8.
void forwardEight() {
  driveBoxRight(80);
  delay(3000);
  driveBoxLeft(74);
  delay(3000);
  }

// This function calls the the two reverse box functions in order to draw a reverse figure 8
// TO DO - Calibrate this.
void reverseEight() {
  reverseDriveBoxRight(78);
  delay(5000);
  reverseDriveBoxLeft(70);
  delay(5000);
}


int dontCrash(int count) {
  int reading = sonarCrash.ping_cm();
  if (reading <= 25 and reading != 0) {
    count ++;
    return count;
  }
  else {
    return 0;
  }
}

int dontFall(int count) {
  int reading = sonarFall.ping_cm();
  if (reading >= 13 and reading != 0) {
    count ++;
    return count;
  }
  else {
    return 0;
  }
}
