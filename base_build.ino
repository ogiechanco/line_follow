// Code developed by RAF Leeming Hackspace
// Line Following Robot for 90SU Cross Brief Hackathon

// Define pin connections
// LED
int LED_RED = 9;      // Pulse Width Modulation (PWM) capable pin
int LED_GREEN  = 10;  // PWM capable pin
int LED_BLUE = 11;    // PWM capable pin

// Right Motor - pin 5 sets speed, pins 7 & 8 set direction if equal brake, if different drive wheels
int RIGHT_POWER = 5;  // PWM capable pin, connected to Motor Board input ENA
int RIGHT_BKWD = 7;   // connected to Motor Board N1         
int RIGHT_FWD = 8;    // connected to Motor Board N2

// Left Motor
int LEFT_POWER = 6;   // PWM capable pin, connected to Motor Board input ENB
int LEFT_BKWD = 12;   // connected to Motor Board N3
int LEFT_FWD = 13;    // connected to Motor Board N4

// Optical Sensors
int LEFT = 14;        // Pin 14 = A0, 15 = A1 etc
int MID = 15;
int RIGHT = 16;

// Define Speed Constants (constant values names are defined in CAPITALS)
int SPEED_STRAIGHT = 100;     // Set the speed to be used on straights and turns
int SPEED_TURN = 150;         // 255 is the most power, 0 is least

// Global Variables (variables that can change are named in lower case)
int leftStatus;
int midStatus;
int rightStatus;

int LEDBrightness = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  
  pinMode(RIGHT_POWER,OUTPUT);
  pinMode(RIGHT_BKWD,OUTPUT);
  pinMode(RIGHT_FWD,OUTPUT);
  
  pinMode(LEFT_POWER,OUTPUT);
  pinMode(LEFT_BKWD,OUTPUT);
  pinMode(LEFT_FWD,OUTPUT);
  
  pinMode(LEFT,INPUT);
  pinMode(MID,INPUT);
  pinMode(RIGHT,INPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  leftStatus = digitalRead(LEFT);   // Read status of optical sensors into variables - HIGH = BLACK
  midStatus = digitalRead(MID);
  rightStatus = digitalRead(RIGHT);
  
  if (midStatus == HIGH) {        // Middle sensor is on black AND
    if (leftStatus == LOW) {      // Left sensor is on white THEN
      straight();                 // We're on the left edge of the black line so go straight
    }                             // Otherwise
    else {                        // Left sensor is on black
      left();                     // We've moved over the line so need to turn left to correct
    }
  }                               // Otherwise
  else {                          // Middle sensor is on white THEN
    right();                      // We've moved off the line so need to turn right to correct
  }
 
  LEDBrightness = LEDBrightness + 1;  // Add 1 to the value of the integer 'LED Brightness'
  
  if(LEDBrightness > 255){        // If the value of 'LEDBrightness' is over 255 (maximum value the LED will take) 
    LEDBrightness = 0;            // Reset the value to 0
  }
 
  analogWrite(LED_RED, LEDBrightness);    // Set the LED output to the current value of 'LEDBrightness' 
  analogWrite(LED_GREEN, LEDBrightness);
  analogWrite(LED_BLUE, LEDBrightness);
  
  delay(10);
}

void straight() {                          // Function to drive straight
  
  analogWrite(RIGHT_POWER,SPEED_STRAIGHT); // Set right motor speed
  digitalWrite(RIGHT_FWD,HIGH);            // Set to drive forwards (Forwards > Backwards)    
  digitalWrite(RIGHT_BKWD,LOW);            
  
  analogWrite(LEFT_POWER,SPEED_STRAIGHT);  // Set left motor speed
  digitalWrite(LEFT_FWD,HIGH);             // Set to drive forwards (Forwards > Backwards) 
  digitalWrite(LEFT_BKWD,LOW);           
  
}

void right() {                             // Function to turn right
  
  analogWrite(RIGHT_POWER,SPEED_TURN);     // Set right motor speed
  digitalWrite(RIGHT_FWD,LOW);             // Set to drive Backward (Forwards < Backwards) 
  digitalWrite(RIGHT_BKWD,HIGH);           
  
  analogWrite(LEFT_POWER,SPEED_TURN);      // Set left motor speed
  digitalWrite(LEFT_FWD,HIGH);             // Set to drive forwards (Forwards > Backwards) 
  digitalWrite(LEFT_BKWD,LOW);             
  
}

void left() {                              // Function to turn left  
  
  analogWrite(RIGHT_POWER,SPEED_TURN);     // Set right motor speed
  digitalWrite(RIGHT_FWD,HIGH);            // Set to drive forwards (Forwards > Backwards) 
  digitalWrite(RIGHT_BKWD,LOW);            
  
  analogWrite(LEFT_POWER,SPEED_TURN);      // Set left motor speed
  digitalWrite(LEFT_FWD,LOW);              // Set to drive Backward (Forwards < Backwards) 
  digitalWrite(LEFT_BKWD,HIGH);             
  
}

