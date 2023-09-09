#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>

#define LED_PIN 13
#define MZ80_PIN 6
#define NUM_SENSORS 6

ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
unsigned int sensorValues[NUM_SENSORS];
unsigned int positionVal = 0;
int detectedObjects = 0;
bool objectDetected = false; 

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  pinMode(MZ80_PIN, INPUT);

  reflectanceSensors.init();
  unsigned long startTime = millis();
  while (millis() - startTime < 5000) {
    reflectanceSensors.calibrate();
  }
}

unsigned int mostLeftSensor() {
  if (sensorValues[0] < 600)
    return 1;
  else
    return 0;
}

unsigned int leftSensor() {
  if (sensorValues[1] < 600)
    return 1;
  else
    return 0;
}

unsigned int midLeftSensor() {
  if (sensorValues[2] < 600)
    return 1;
  else
    return 0;
}

unsigned int midRightSensor() {
  if (sensorValues[3] < 600)
    return 1;
  else
    return 0;
}

unsigned int rightSensor() {
  if (sensorValues[4] < 600)
    return 1;
  else
    return 0;
}

unsigned int mostRightSensor() {
  if (sensorValues[5] < 600)
    return 1;
  else
    return 0;
}


void leftBack() {
  motors.setSpeeds(-100, -300);
}
void turnRight() {
  motors.setSpeeds(270, -270);
}
void go() {
  motors.setSpeeds(200, 200);
}
void RightBack() {
  motors.setSpeeds(-100, -300);
}

void loop() {

  for(int i = 0; i < 360; i++) { 
    motors.setSpeeds(120, -120); 
    delay(10); 

    if (digitalRead(MZ80_PIN) == HIGH && !objectDetected) {
      detectedObjects++; 
      objectDetected = true; 
    } else if (digitalRead(MZ80_PIN) == LOW) {
      objectDetected = false; 
    }
  }

    for(int i = 0; i < detectedObjects; i++) {
    motors.setSpeeds(120, -120);
    digitalWrite(LED_PIN, LOW);  
    delay(1000);  
    digitalWrite(LED_PIN, HIGH); 
    delay(1000); 
    }
     motors.setSpeeds(0, 0);
     delay(5000); 

  while(1){
    
    positionVal = reflectanceSensors.readLine(sensorValues);
    if (mostLeftSensor()|| leftSensor()|| midLeftSensor()  == 1) {
      leftBack();
      delay(250);
    }
    if (mostRightSensor()|| rightSensor()|| midRightSensor() == 1) {
      RightBack();
      delay(250);
    }
    else{
       if (!digitalRead(MZ80_PIN)) {
         go();
      }
       else if (digitalRead(MZ80_PIN)){
        turnRight();
        }
    }
  }
}