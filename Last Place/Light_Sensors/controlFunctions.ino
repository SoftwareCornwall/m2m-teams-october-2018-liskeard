// Left Pins
const int motorLE = 9;              //Left Motor Enable
const int motorLB = 7;              //Left Motor Backwards
const int motorLF = 8;              //Left Motor Forwards

// Right Pins
const int motorRE = 10;             //Right Motor Enable
const int motorRF = 12;             //Right Motor Forwards
const int motorRB = 11;             //Right Motor Backwards


void setupPins() {
  pinMode(motorLE, OUTPUT);
  pinMode(motorLB, OUTPUT);
  pinMode(motorLF, OUTPUT);
  pinMode(motorRE, OUTPUT);
  pinMode(motorRB, OUTPUT);
  pinMode(motorRF, OUTPUT);  
}

/* This function will move the rover forwards.
With this, both motors are enabled
The backwards motors are off and the forwards are on. 
Therefore the rover moves forwards.*/
void forward() {
  digitalWrite(motorLE, HIGH); 
  digitalWrite(motorRE, HIGH);
  digitalWrite(motorRB, LOW);
  digitalWrite(motorLB, LOW);
  digitalWrite(motorRF, HIGH);
  digitalWrite(motorLF, HIGH);
}

void forward(int rms, int lms) {
  digitalWrite(motorLE, HIGH); 
  digitalWrite(motorRE, HIGH);
  digitalWrite(motorRB, LOW);
  digitalWrite(motorLB, LOW);
  analogWrite(motorRF, rms);
  analogWrite(motorLF, lms);
}


/* This function will stop the rover.
With this, both motors are enabled, however
Neither the forwards or backwards are on
so it doesn't move at all.*/
void stop() {
  digitalWrite(motorLE, HIGH); 
  digitalWrite(motorRE, HIGH);
  digitalWrite(motorRB, LOW);
  digitalWrite(motorLB, LOW); 
  digitalWrite(motorRF, LOW);  
  digitalWrite(motorLF, LOW);  
}


/*This function will move the rover backwards.
With this, both motors are enabled The backwards motors are enabled. 
However the forwards aren't, resulting in a reverse.*/
void reverse() {
  digitalWrite(motorLE, HIGH); 
  digitalWrite(motorRE, HIGH);
  digitalWrite(motorRB, HIGH);
  digitalWrite(motorLB, HIGH);
  digitalWrite(motorRF, LOW);
  digitalWrite(motorLF, LOW);  
}

void rightTurn() {
  rightTurn(812);  
}

void rightTurn(int amount){
  digitalWrite(motorLE, HIGH); 
  digitalWrite(motorRE, HIGH);
  digitalWrite(motorRB, HIGH);
  digitalWrite(motorLB, LOW); 
  digitalWrite(motorRF, LOW);  
  digitalWrite(motorLF, HIGH); 
  delay(amount);
}

void leftTurn() {
  leftTurn(708);
}

void leftTurn(int amount){
  digitalWrite(motorLE, HIGH); 
  digitalWrite(motorRE, HIGH);
  digitalWrite(motorRB, LOW);
  digitalWrite(motorLB, HIGH); 
  digitalWrite(motorRF, HIGH);  
  digitalWrite(motorLF, LOW); 
  delay(amount);
}
