#include <Servo.h>
#include <math.h>
//#include<Arduino.h>

//pins
const int input_val_x=A0;
const int input_val_y=A1;
const int servo1= 4;
const int servo2=3;

double s1_angle =90;
double s2_angle=0; 
double theta=0;
double h=0;
double l1=10 ,l2=10;
Servo s1,s2;

void init_set()
{
  s1.attach(servo1);
  s2.attach(servo2);

  s1.write(s1_angle);
  s2.write(s2_angle);
}

void move(double x,double y)
{
  // x=map(analogRead(input_val_x),0,1023,0,l1+l2);
  // y=map(analogRead(input_val_y),0,1023,0,l1+l2);
  h=sqrt((x*x)+(y*y));

  double angle_rad = acos(((l1*l1)+(l2*l2)-(h*h))/(2*l1*l2));
  s2_angle = angle_rad * 57.2958; 
  angle_rad = acos(((l1*l1)+(h*h)-(l2*l2))/(2*l1*h));
  s1_angle = angle_rad * 57.2958;
  angle_rad= atan(y/x) * 57.2958;
  s1_angle = s1_angle + angle_rad;

  s1.write(s1_angle);
  s2.write(s2_angle);
  
  Serial.print(s1_angle);
  Serial.print("\t");
  Serial.println(s2_angle);
  delay(200);
}


void setup() {
  pinMode(input_val_x,INPUT);
  pinMode(input_val_y,INPUT);
  pinMode(servo1,OUTPUT);
  pinMode(servo2,OUTPUT);
	Serial.begin(9600);
  init_set();
}

void loop() {
  double i=0,j=0;
  Serial.println("X axis starts");
  while(i!=l1+l2)
  {
    i++;
    move(i,j);
  }
  Serial.println("Curve starts");
  while(i!=0)
  {
    i--;
    j=sqrt((l1+l2)*(l1+l2) - (i*i));
    move(i,j);
  }
  Serial.println("Y axis starts");
  while(j!=0)
  {
    j--;
    move(i,j);
  }
}
