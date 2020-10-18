#include <Servo.h> 

Servo servo[3];
int angle = 0;
boolean switchDirection[3];

void setup() {
  Serial.begin(9600);

  for(int i=0;i<3;i++){
    pinMode(10 + i,OUTPUT);
    servo[i].attach(10 + i);
    servo[i].write(90);
  }
  switchDirection[0] = false;
  switchDirection[1] = true;
  switchDirection[2] = false;
  
}

void loop() {
  if (Serial.available() > 2) {
    for(int i=0;i<3;i++){
      angle = Serial.read();
      //if(switchDirection[i])angle = 180 - angle;
      servo[i].write(angle);
    }
  }
}
