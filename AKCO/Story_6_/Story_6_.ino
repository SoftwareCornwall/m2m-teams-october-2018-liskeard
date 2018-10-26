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


void left_pulse_interrupt()
{
  left_count++;
}

void right_pulse_interrupt()
{
  right_count++;
}


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  start_rover_time = millis();
  pinMode(left_motor_enable, OUTPUT);
  pinMode(right_motor_enable, OUTPUT);
  pinMode(left_motor_forwards , OUTPUT);
  pinMode(right_motor_forwards , OUTPUT);
  pinMode(left_motor_backwards, OUTPUT);
  pinMode(right_motor_backwards, OUTPUT);
  pinMode(left_feedback_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(left_feedback_pin), left_pulse_interrupt, RISING);
  Serial.begin(115200);
  pinMode(right_feedback_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(right_feedback_pin), right_pulse_interrupt, RISING);
}

// the loop function runs over and over again forever
void loop() //uses the functions created below 
{
  long_square_edge(100);
  Serial.println("Square edge finished");
  //zero_count();
  delay(2000);
  turn_right(1560);
  //zero_count();
  delay(2000);
  long_square_edge(100);
  //zero_count();
  delay(2000);
  turn_right(1585);
  //zero_count();
  delay(2000);
  long_square_edge(80);
  //zero_count();
  delay(2000);
  turn_right(1650);
  //zero_count();
  delay(2000);
  long_square_edge(133);
  //zero_count();
  delay(2000);
  turn_right(1700);
  //zero_count();
  delay(2000);
  brake();
  delay(100000);
  // need to make it turn right so use use the new functions created
  }


void long_square_edge(int length_edge) // edge of square
{
  left_count = 0;
  right_count = 0;
  while(left_count < length_edge){
      forward();
      Serial.println("forward function called");
      straight_line();
      Serial.println("Straight line");
      Serial.print("Length of edge  ");
      Serial.println(length_edge);
        if (left_count >= length_edge)
        { 
          Serial.println("left_count is greater than length edge");
          brake(); 
          left_count = 0;
          right_count = 0;
          Serial.println("brake");
          break;
        }
  }
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

void square_edge(int length_edge) // edge of square
{
  forward();
  Serial.println("forward function called");
  straight_line();
  Serial.println("Straight line");
  Serial.print("Length of edge  ");
  Serial.println(length_edge);
  if (left_count >= length_edge)
  { 
    Serial.println("left_count is greater than length edge");
    brake(); 
    left_count = 0;
    right_count = 0;
    Serial.println("brake");
  }
}

void straight_line()
{
  int differance = right_count - left_count;
  if (differance >= 10){ // if too fast left decresses the left and increases the right
    speed_left = 223;
    speed_right = 160; 
    Serial.println("correct left");
    }
    
   if (differance <= -10){ // if too fast right decresses the right and increases the left
    speed_left = 203;
    speed_right = 180;
    Serial.println("correct right"); 
   }
   
   if(differance > -10 or differance < 10) {
    speed_left = 213;
    speed_right = 170;
    Serial.println("speed reset");
   }
   
  delay(100);
  Serial.print("Left count  ");
  Serial.println(left_count);
  Serial.print("Right count  ");
  Serial.println(right_count);
  Serial.print("Left speed  ");
  Serial.println(speed_left);
  Serial.print("Right speed  ");
  Serial.println(speed_right);
  Serial.print("Difference  ");
  Serial.println(differance);
}


void forward() //Tell the rover to go forward
{
  analogWrite(left_motor_enable, speed_left); 
  analogWrite(right_motor_enable, speed_right); 
  digitalWrite(left_motor_forwards, HIGH); 
  digitalWrite(right_motor_forwards, HIGH); 
  digitalWrite(right_motor_backwards, LOW);
  digitalWrite(left_motor_backwards, LOW); 
}

void backward() //Tell the rover to go backwards
{
  digitalWrite(left_motor_forwards, LOW); 
  digitalWrite(right_motor_forwards, LOW); 
  digitalWrite(right_motor_backwards, HIGH);
  digitalWrite(left_motor_backwards, HIGH);
  analogWrite(left_motor_enable,speed_left); 
  analogWrite(right_motor_enable,speed_right);
}

void turn_right(int length_corner)
{
    /*left_count = 0;
    //right_count = 0;
    while (left_count < length_corner){
    Serial.println("Turn Right"); 
    Serial.print("turn right right_count  ");
    Serial.println(right_count);
    Serial.print("turn right left_count  ");
    Serial.println(left_count);
      if (left_count >= length_corner)
    {
        brake(); 
        //left_count = 0;
        //right_count = 0;
        Serial.println("brake in corner");
    }
    */
    digitalWrite(left_motor_forwards, HIGH); 
    digitalWrite(right_motor_forwards, LOW); 
    digitalWrite(right_motor_backwards, LOW);
    digitalWrite(left_motor_backwards, LOW);
    analogWrite(left_motor_enable,speed_left); 
    analogWrite(right_motor_enable,speed_right);
    delay(length_corner);
    brake();
  }





void zero_count()
{
  left_count = 0;
  right_count = 0;
}

