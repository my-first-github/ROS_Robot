/* Author: Darshan Shah
    This ROS node subscribes to ServoAngles topic and Navigation topic and actuates the servos or DC motors accordingly
    Send the Servo Angle int values from Serial Monitor in the following format
 *      rostopic pub Servo1 std_msgs/UInt16 90
 *      
 *      IN terminal, type roscore
 *      in new terminal rosrun rosserial_python serial_node.py /dev/ttyACM0
 *      
*/


#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

Servo s1;  //Servo 1
Servo s2;  //Servo 2

int pos1 = 0;
int pos2 = 0;
const int LeftMotor1 = 2;
const int LeftMotor2 = 3;
const int RightMotor1 = 4;
const int RightMotor2 = 5;
int PauseTime = 1000;


void Servo1_cb(const std_msgs::UInt16& Servo1) {
  s1.write(Servo1.data);
  nh.loginfo("Servo 1 actuating");
}

void Servo2_cb(const std_msgs::UInt16& Servo2) {
  s2.write(Servo2.data);
  nh.loginfo("Servo 2 actuating");
  front();
}


void Navigate_cb(const std_msgs::UInt16& Navigate){
  nh.loginfo("Going Straight");
  if (Navigate.data == 1){
    nh.loginfo("Going Straight");
  front();
  }
  else if (Navigate.data == 2){
    nh.loginfo("Going Back");
  back();
  }
  else if(Navigate.data == 3){
    nh.loginfo("Going Left");
    left();
  }
  else if (Navigate.data == 4){
    nh.loginfo("Going right");
  right();
  }
  else {
    nh.loginfo("Stopping");
    die();
  }
  
}

ros::Subscriber<std_msgs::UInt16> S3("Navigate", Navigate_cb);
ros::Subscriber<std_msgs::UInt16> S1("Servo1", Servo1_cb);
ros::Subscriber<std_msgs::UInt16> S2("Servo2", Servo2_cb);


void setup() {
  s1.attach(9);
  s2.attach(6);

  nh.initNode();
  nh.subscribe(S3);
  nh.subscribe(S1);
  nh.subscribe(S2);
  
  pinMode(LeftMotor1,OUTPUT);
  pinMode(LeftMotor2,OUTPUT);
  pinMode(RightMotor1,OUTPUT);
  pinMode(RightMotor2,OUTPUT);

}

void loop() {
  nh.spinOnce();
  delay(3);
}


void front()
{
  
  digitalWrite(LeftMotor1,HIGH);
  digitalWrite(LeftMotor2,LOW);
  digitalWrite(RightMotor1, HIGH);
  digitalWrite(RightMotor2, LOW);
  delay(PauseTime);
  die();
}


void back()
{
  digitalWrite(LeftMotor1,LOW);
  digitalWrite(LeftMotor2,HIGH);
  digitalWrite(RightMotor1, LOW);
  digitalWrite(RightMotor2, HIGH);
  delay(PauseTime);
  die();
}

void left()
{
  digitalWrite(LeftMotor1,LOW);
  digitalWrite(LeftMotor2,LOW);
  digitalWrite(RightMotor1, HIGH);
  digitalWrite(RightMotor2, LOW);
  delay(PauseTime);
  die();

}
void right()
{
  digitalWrite(LeftMotor1,HIGH);
  digitalWrite(LeftMotor2,LOW);
  digitalWrite(RightMotor1, LOW);
  digitalWrite(RightMotor2, LOW);
  delay(PauseTime);
  die();
}
void die()
{
  digitalWrite(LeftMotor1,LOW);
  digitalWrite(LeftMotor2,LOW);
  digitalWrite(RightMotor1, LOW);
  digitalWrite(RightMotor2, LOW);
}

