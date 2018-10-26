const int left_motor_feedback = 2; // lables the interger as the variable name
const int right_motor_feedback = 3;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(left_motor_feedback, OUTPUT);
  pinMode(right_motor_feedback, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(left_motor_feedback, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                                // wait for a second
  digitalWrite(left_motor_feedback, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(right_motor_feedback, HIGH); 
  delay(1000);                      
  digitalWrite(right_motor_feedback, LOW);
}
