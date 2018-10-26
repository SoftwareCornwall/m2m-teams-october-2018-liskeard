/*These etsbalish the motor variables as outputs.
Therefore the motors or LEDs will be outputting.*/
void setup() {
  setupPins(); 
  Serial.begin(115200);
}


void loop() {
 forward();
 delay(10000);
 stop();
 delay(1000);
 reverse();
 delay(1000);
}
