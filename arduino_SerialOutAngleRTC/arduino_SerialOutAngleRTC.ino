#include <Servo.h> 

Servo servo[3];
int angle_upper = 0;
float angle_lower = 0;
float angle = 0;
boolean switchDirection[3];
float upperLimit[3];
float lowerLimit[3];

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

  upperLimit[0] = 2500;
  lowerLimit[0] = 500;
  upperLimit[1] = 2500;
  lowerLimit[1] = 500;
  upperLimit[2] = 2500;
  lowerLimit[2] = 500;
}

void loop() {
  if (Serial.available() > 5) {
    for(int i=0;i<3;i++){
      angle_upper = Serial.read() * 10;
      angle_lower = Serial.read() / 10;
      angle = angle_upper + angle_lower;
      if(switchDirection[i])angle = 180.0 - angle;
      angle = map(angle,0,180,lowerLimit[i],upperLimit[i]);
      servo[i].writeMicroseconds(int(angle));
    }
  }
}
