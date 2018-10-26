const int left_motor_enable = 9; // lables the interger as the variable name
const int right_motor_enable = 10;
const int left_motor_forwards = 8;
const int right_motor_forwards = 12;
const int left_motor_backwards = 7;   //In2=backwards
const int right_motor_backwards= 11; 
const int left_feedback_pin = 2;
const int right_feedback_pin = 3;
volatile unsigned int left_count = 0;
volatile unsigned int right_count = 0;
int speed_left = 213;
int speed_right = 170;
int start_rover_time = 0;
int end_rover_time = 10000;
int current_rover_time;




void setup() {
  // put your setup code here, to run once:
    pinMode(left_motor_enable, OUTPUT);
  pinMode(right_motor_enable, OUTPUT);
  pinMode(left_motor_forwards , OUTPUT);
  pinMode(right_motor_forwards , OUTPUT);
  pinMode(left_motor_backwards, OUTPUT);
  pinMode(right_motor_backwards, OUTPUT);
  pinMode(left_feedback_pin, INPUT_PULLUP);
Serial.begin(115200);
}




void loop() {
  // put your main code here, to run repeatedly:
turn_right(90);

}





void square_edge(int length_edge) // edge of square
{

  Serial.println("Straight line");
  Serial.println(length_edge);
}





void turn_right(int length_edge)
{
  Serial.println("Turn Right"); 
    if (left_count >= length_edge)
  {
    brake(); 
    left_count = 0;
    right_count = 0;
    Serial.println("brake");
  }
  
  digitalWrite(left_motor_forwards, LOW); 
  digitalWrite(right_motor_forwards, HIGH); 
  digitalWrite(right_motor_backwards, LOW);
  digitalWrite(left_motor_backwards, LOW);
  analogWrite(left_motor_enable,speed_left); 
  analogWrite(right_motor_enable,speed_right);
}




void brake()
{
  digitalWrite(left_motor_enable, LOW); 
  digitalWrite(right_motor_enable, LOW); 
  digitalWrite(left_motor_forwards, LOW); 
  digitalWrite(right_motor_forwards, LOW); 
  digitalWrite(right_motor_backwards, LOW);
  digitalWrite(left_motor_backwards, LOW); 
}


