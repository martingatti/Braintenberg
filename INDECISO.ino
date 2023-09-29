#include <Servo.h>

#define TRIG 49
#define ECHO 48

int duration;
int distance;
int pos = 0;    // variable to store the servo position
int vpt=0;

int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

int pwm1 = 9;
int pwm2 = 10;

int velocity = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);

  // setup for motors
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(pwm1, OUTPUT); 
  pinMode(pwm2, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

}


// Return distance from audio distance sensor in centimeters
int distanceSensor() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration=pulseIn(ECHO, HIGH);
  distance = duration * (0.034/2); // s = t * (0.034/2) m/s
  
  return distance;
}

void driveForward(int v) {
  //Controlling speed (0 = off and 255 = max speed):
  analogWrite(pwm1, v); //ENA pin
  analogWrite(pwm2, v); //ENB pin 
  
  //Controlling spin direction of motors:
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void driveBackward(int v) {
  //Controlling speed (0 = off and 255 = max speed):
  analogWrite(pwm1, v); //ENA pin
  analogWrite(pwm2, v); //ENB pin 
  
  //Controlling spin direction of motors:
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void stopMovement() {
  //Controlling speed (0 = off and 255 = max speed):
  analogWrite(pwm1, 0); //ENA pin
  analogWrite(pwm2, 0); //ENB pin 
}

//acá es donde yo deberia empezar a modificar 
int behavior(int dist) {
  if (dist < 25) {
    vpt=160;
    return vpt;
  } else if (dist > 60) {
    return 180;
  }
  return dist;
}

void loop() { 
  // put your main code here, to run repeatedly:
  distance = distanceSensor();
  Serial.println(distance);
  
   velocity = behavior(distance); 
   if (velocity == 160) {
  
  //Controlling speed (0 = off and 255 = max speed):
    analogWrite(pwm1, velocity); //ENA pin
    analogWrite(pwm2, velocity); //ENB pin 
  
  //Controlling spin direction of motors:
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
  
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
} 

  else { 
   velocity = behavior(distance);
  }
  driveForward(velocity);
  //delay(1000);
  //stopMovement();
  //delay(1000);
  //driveBackward(50);
  //delay(1000);
  //stopMovement();
  delay(1000);


}
