

/*These etsbalish the motor variables as outputs.
Therefore the motors or LEDs will be outputting.*/
void setup() {
  pinMode(motorLE, OUTPUT);
  pinMode(motorLB, OUTPUT);
  pinMode(motorLF, OUTPUT);
  pinMode(motorRE, OUTPUT);
  pinMode(motorRB, OUTPUT);
  pinMode(motorRF, OUTPUT);

  Serial.begin(115200);
}

void loop() {
 forward();
 delay(1000);
 stop();
 rightTurn();
 forward();
 delay(1000);
 stop();
 rightTurn();
 forward();
 delay(1000);
 rightTurn();
 forward();
 delay(2050);

 stop();
 leftTurn();
 forward();
 delay(1000);
 stop();
 leftTurn();
 forward();
 delay(1000);
 leftTurn();
 forward();
 delay(1050);
 stop();
 delay(10000);
}
