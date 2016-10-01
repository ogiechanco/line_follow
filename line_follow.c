// Code developed by RAF Leeming Hackspace
// Line Following Robot for 90SU Cross Brief Hackathon

// Define pin connections

// LED
int LED_RED = 9;      // PWM capable pin
int LED_GREEN  = 10;  // PWM capable pin
int LED_BLUE = 11;    // PWM capable pin

// Motor 1 - EN sets speed, N pins set direction - N1 = N2 > brake, N1 != N2 > drive
int ENA = 6;          // PWM capable pin
int N1 = 14;          // Pin 14 = A0, 15 = A1 etc
int N2 = 15;

// Motor 2
int ENB = 9;          // PWM capable pin
int N3 = 16;
int N4 = 17;

// Sensors
int LEFT = 3;
int MID = 4;
int RIGHT = 5;

// Speed Constants

int SPEED_STRAIGHT = 300;
int SPEED_TURN = 150;

// Global Variables

int leftStatus;
int midStatus;
int rightStatus;

// the setup function runs once when you press reset or power the board
void setup() {
  
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  
  pinMode(ENA,OUTPUT);
  pinMode(N1,OUTPUT);
  pinMode(N2,OUTPUT);
  
  pinMode(ENB,OUTPUT);
  pinMode(N3,OUTPUT);
  pinMode(N4,OUTPUT);
  
  pinMode(LEFT,INPUT);
  pinMode(MID,INPUT);
  pinMode(RIGHT,INPUT);
  
  straight();
}

// the loop function runs over and over again forever
void loop() {
  
  leftStatus = digitalRead(LEFT);   // Read status of sensor into variable - HIGH = BLACK
  midStatus = digitalRead(MID);
  rightStatus = digitalRead(RIGHT);
  
  delay(50);    //  50ms delay to ensure smooth motion
  
  if (midStatus == HIGH) {        // Middle sensor is on black AND
    if (leftStatus == LOW) {      //  Left sensor is on white THEN
      straight;                   //    We're on the left edge of the black line so go straight
    }                             //  Otherwise
    else {                        //  Left sensor is on black
      left();                     //    We've moved over the line so need to turn left to correct
    }
  }                               // Otherwise
  else {                          // Middle sensor is on white THEN
    right();                      //  We've moved off the line so need to turn right to correct
  }
  
}

void straight() {                 // Function to drive straight
  
  analogWrite(ENA,SPEED_STRAIGHT);  // Set motor speed
  digitalWrite(N1,HIGH);            // N1 HIGH, N2 LOW = drive forward
  digitalWrite(N2,LOW);
  
  analogWrite(ENB,SPEED_STRAIGHT);
  digitalWrite(N3,HIGH);
  digitalWrite(N4,LOW);

}

void right() {                    // Function to turn right
  
  
}

void left() {                     // Function to turn left  
  
   
  
}
