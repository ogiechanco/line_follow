// Laser Gate Code for 90SU Hackathon
// (C) 2016 Dave Collins

int laser = 3;
int sensor = 19;
int lapCount = 0;
int sensorOff = 0;
int sensorOffTime = 0;

int lastBool = 0;
int lastTime = 0;

int lapMin[4];
int lapSec[4];
int lapTen[4];

void setup(){
  
 pinMode(laser, OUTPUT); 
 pinMode(sensor, INPUT);
 
 Serial.begin(9600);
 
 digitalWrite(laser, HIGH);
  
 lastTime = millis();
  
}

void loop(){
  
  int sensorValue = analogRead(sensor);
  
  int sensorBool = 0;
  
  if (sensorValue < 100){
    
    sensorBool = 0;
    
  }
  else{
    
    sensorBool = 1;
    
  }
  
  if (sensorBool == 1 && sensorOff == 0){
    if (lastBool == 0){
    
      // Rising Edge
      
      lapCount++;
      
      sensorOff = 1;
      sensorOffTime = 0;
      
    }
  }  
  
  sensorOffTime++;
  
  if(sensorOffTime > 50){
    
    sensorOff = 0;
    
  }
  
  
  lapTen[lapCount]++;
  
  if(lapTen[lapCount] == 10){
   
    lapTen[lapCount] = 0;
    lapSec[lapCount]++;
    
    if(lapSec[lapCount] == 60){
      
      lapSec[lapCount] == 0;
      lapMin[lapCount]++;
    }
    
  }
  
  printScreen();
  
  lastBool = sensorBool;
  
  while((lastTime + 100) < millis()){
    delay(5);
  }
  
  lastTime = millis();
}

void printScreen(){
  
  Serial.write(12);
  
  String lapString = "";
  
  for(int n = 1; n < 4; n++){
   
    
    lapString = "Lap " + n;
    lapString = lapString + ": ";
    lapString = lapString + lapMin[n];
    lapString = lapString + ":";
    lapString = lapString + lapSec[n];
    lapString = lapString + ".";
    lapString = lapString + lapTen[n];
    
    Serial.println(lapString);
      
  }
  
  
}
