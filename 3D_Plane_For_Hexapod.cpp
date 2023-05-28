#include <Servo.h>
#include <math.h>
//#include<Arduino.h>

const int servo1_pin= 4;        //servo pins
const int servo2_pin=3;
const int servo3_pin=5;
const int x1=A0, y1=A1, z1=A2; //input pins

double s1_initial_angle=90, s2_initial_angle=90, s3_initial_angle=90; //initial angles
double s1_angle =0, s2_angle=0, s3_angle=0, angle_rad=0;
double h1=0, h2=0;             //length of diagonal
double l1=10 ,l2=10;           //length of arms
double i=0, j=0, k=0;           //temporary variables
double x_in=0,y_in=0,z_in=0;     //input readings
Servo s1,s2,s3;                 //servo objects

void init_set()
{
  //attach servo
  s1.attach(servo1_pin);
  s2.attach(servo2_pin);
  s3.attach(servo3_pin);

    //set initial angles
  s1.write(s1_initial_angle);
  s2.write(s2_initial_angle);
  s3.write(s3_initial_angle);
}

void move(double x,double y,double z)
{
  //calculate length of diagonals
  h1=sqrt((x*x)+(y*y));
  h2=sqrt((z*z) + (h1*h1));
  Serial.print("\t");
  Serial.print(h1);
  Serial.print("\t");
  Serial.print(h2);
  Serial.print("\t");

  //calculate MOTOR angles and setb according to it
  angle_rad= acos(((x*x)+(h2*h2) - (z*z))/(2*x*h2));
  angle_rad = angle_rad * 57.2958;
  if(z>=0)
    s3_angle = s3_initial_angle - angle_rad;    //s3 angle
  else
    s3_angle = s3_initial_angle + angle_rad;    //s3 angle

  angle_rad = acos(((l1*l1)+(l2*l2)-(h2*h2))/(2*l1*l2));
  s2_angle = (angle_rad * 57.2958);     //s2 angle

  angle_rad = acos(((l1*l1)+(h2*h2)-(l2*l2))/(2*l1*h2));
  s1_angle = angle_rad * 57.2958;
  angle_rad= atan(y/x) * 57.2958;     //slope of line to origin
  s1_angle += angle_rad;
  if(y>0)
    {
      s1_angle = s1_initial_angle + s1_angle ;      //s1 angle
    }
  else
    {
      s1_angle = s1_initial_angle - s1_angle;     //s1 angle
    }

  s3.write(s3_angle);
  s2.write(s2_angle);
  s1.write(s1_angle);
  
  Serial.print(s1_angle);
  Serial.print("\t");
  Serial.print(s2_angle);
  Serial.print("\t");
  Serial.println(s3_angle);
  delay(200);
}

void setup() {
  
  pinMode(servo1_pin,OUTPUT);
  pinMode(servo2_pin,OUTPUT);
  pinMode(servo3_pin,OUTPUT);
  pinMode(x1,INPUT);
  pinMode(y1,INPUT);
  pinMode(z1,INPUT);
	Serial.begin(9600);
  init_set();
}

void loop() {
  x_in= map(analogRead(x1),0,1023,0,(l1+l2));
  y_in= map(analogRead(y1),0,1023,-(l1+l2),(l1+l2));
  z_in= map(analogRead(z1),0,1023,-(l1+l2),(l1+l2));

  Serial.print(x_in);
  Serial.print("\t");
  Serial.print(y_in);
  Serial.print("\t");
  Serial.print(z_in);
  

  move(x_in,y_in,z_in);
}
