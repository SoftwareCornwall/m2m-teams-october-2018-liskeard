// Left Pins
const int motorLE = 9;              //Left Motor Enable
const int motorLB = 7;              //Left Motor Backwards
const int motorLF = 8;              //Left Motor Forwards

// Right Pins
const int motorRE = 10;             //Right Motor Enable
const int motorRF = 12;             //Right Motor Forwards
const int motorRB = 11;             //Right Motor Backwards


void setupPins() {
  pinMode(motorLE, OUTPUT);        //These set up the motor variables as outputs.
  pinMode(motorLB, OUTPUT);        //As they're outputs, the motors on the rover will start or stop according to the code.
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
  digitalWrite(motorRF, HIGH);        //Having 'HIGH' and 'LOW' values sets these up to either not run, or to have the motors at their full speed of 255.
  digitalWrite(motorLF, HIGH);        //This 255 is not changeable within this.
}

void forward(int rms, int lms) {     //The use of 'rms' and 'lms' sets up the rover to be moving at the specific speeds dictated by us or the surroundings via these integer inputs of the motor speeds.
  digitalWrite(motorLE, HIGH); 
  digitalWrite(motorRE, HIGH);
  digitalWrite(motorRB, LOW);
  digitalWrite(motorLB, LOW);
  analogWrite(motorRF, rms);        //Due to this being parts of the forwards function, the 'rms and 'lms' is only applied to the forward motor variables.
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
  digitalWrite(motorLF, LOW);     //As this is only stopping the rover, there is no need for specific speed values.
}


/*This function will move the rover backwards.
With this, both motors are enabled The backwards motors are enabled. 
However the forwards aren't, resulting in a reverse.*/
void reverse() {
  digitalWrite(motorLE, HIGH); 
  digitalWrite(motorRE, HIGH);
  digitalWrite(motorRB, HIGH);        //This is the generic reverse function, the reverses are simply 'HIGH' for full speed.
  digitalWrite(motorLB, HIGH);
  digitalWrite(motorRF, LOW);
  digitalWrite(motorLF, LOW);  
}

void rightTurn() {                   //We've been using a right turn that is a right-angle. We've kept this as a separate function to give us the option of a right-angle or a different dictated angle to the right.
  rightTurn(812);                    //'812' is the number value we've found to consistently produce a right-angle.
}

void rightTurn(int amount){         //In comparison, the time turned is optional here and can be chnaged to fit a specific task.
  digitalWrite(motorLE, HIGH); 
  digitalWrite(motorRE, HIGH);
  digitalWrite(motorRB, HIGH);
  digitalWrite(motorLB, LOW); 
  digitalWrite(motorRF, LOW);  
  digitalWrite(motorLF, HIGH); 
  delay(amount);
}

void leftTurn() {                  //This reflects how we structured the right turn, with a particular value ('708') that we know to turn at a right-angle.
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
