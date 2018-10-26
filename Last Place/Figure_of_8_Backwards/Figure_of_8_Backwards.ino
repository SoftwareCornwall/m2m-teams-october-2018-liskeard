/*These etsbalish the motor variables as outputs.
Therefore the motors or LEDs will be outputting.*/
void setup() {
  setupPins();
  
  Serial.begin(115200);
}

/*This loop creates two squares, which form a figure of eight.
It then does reverse manoeuvre.*/
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
 delay(2150);

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
 delay(1000);

 reverse();
 delay(1000);
 stop();
 rightTurn(800);
 reverse();
 delay(1000);
 stop();
 rightTurn(800);
 reverse();
 delay(1000);
 rightTurn(800);
 reverse();
 delay(1950);
 
 leftTurn(730);
 reverse();
 delay(1000);
 stop();
 leftTurn(730);
 reverse();
 delay(1100);
 stop();
 leftTurn(730);
 reverse();
 delay(800);
 stop();
 delay(10000);
}
