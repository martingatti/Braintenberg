//include library for servo
#include <Servo.h>

//define name of the servo motors
Servo upDownServo;
Servo rightLeftServo;

//define position name and value
#define left 145
#define right 45
#define middle 90

#define closed 90
#define fullOpen 170
#define halfOpen 130

#define eyeSpeed 20
#define increment 2

#define waitTime 600

int vertPos;
int horiPos;


void moveRight(int setpoint) {
  int startPoint = horiPos;
  for (horiPos = startPoint; horiPos >= setpoint; horiPos -= increment) {
    rightLeftServo.write(horiPos);
    delay(eyeSpeed);
  }
}

void moveLeft(int setpoint) {
  int startPoint = horiPos;
  for (horiPos = startPoint; horiPos <= setpoint; horiPos += increment) {
    rightLeftServo.write(horiPos);
    delay(eyeSpeed);
  }
}

void moveUp(int setpoint) {
  int startPoint = vertPos;
  for (vertPos = startPoint; vertPos <= setpoint; vertPos += increment) {
    upDownServo.write(vertPos);
    delay(eyeSpeed*3); //me habia confundido y le puse /2 pero eso significa un delay mas chico por ende mas rapido y no gusta eso :) 
  }
}

void moveDown(int setpoint) {
  int startPoint = vertPos;
  for (vertPos = startPoint; vertPos >= setpoint; vertPos -= increment) {
    upDownServo.write(vertPos);
    delay(eyeSpeed*3);
  }
}

void moveHorizontal(int setpoint) {
  int startPoint = horiPos;
  int dir = setpoint - startPoint;
  if (dir > 0) {
    moveLeft(setpoint);
  } else {
    moveRight(setpoint);
  }
}

void moveVertical(int setpoint) {
  int startPoint = vertPos;
  int dir = setpoint - startPoint;
  if (dir > 0) {
    moveUp(setpoint);
  } else {
    moveDown(setpoint);
  }
}



void setup(){
  //pin de los servos
  upDownServo.attach(6);
  rightLeftServo.attach(5);

  //posicion inicial 
  vertPos = closed; // modes: closed, halfOpen, fullOpen
  horiPos = middle; // modes: right, left, middle
  
  delay(10);
  upDownServo.write(vertPos);
  rightLeftServo.write(horiPos);
}

void loop(){
  
  delay(2000); // wait two seconds before starting movement
  moveVertical(halfOpen);
  delay(waitTime);
  moveHorizontal(right);
  delay(waitTime);
  moveHorizontal(left);
  delay(waitTime);
  moveHorizontal(right);
  delay(waitTime);
  moveHorizontal(left);
  delay(waitTime);
  moveHorizontal(middle);
  delay(100);
  moveVertical(fullOpen);
  delay(waitTime);
  moveVertical(halfOpen);
  delay(waitTime);
  moveVertical(closed);
  delay(waitTime);

}
