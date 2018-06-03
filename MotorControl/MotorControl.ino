
//Controlling Servo motors using ROS Twist keyboard
//rosrun rosserial_python serial_node.py /dev/ttyACM0
//rosrun teleop_twist_keyboard teleop_twist_keyboard.py


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#include <stdlib.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <Servo.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle nh;
geometry_msgs::Twist msg;

float move1;
float move2;


Servo leftServo;
Servo rightServo;

/// Servo servo;

void left_servo_cb( const std_msgs::UInt16& cmd_msg)
{
  leftServo.write(cmd_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}


void right_servo_cb( const std_msgs::UInt16& cmd_msg)
{
  rightServo.write(cmd_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}

void callback(const geometry_msgs::Twist& cmd_vel)
{
  move1 = cmd_vel.linear.x;
  move2 = cmd_vel.angular.z;
  if (move1 > 0 && move2 == 0)
  {
    front();
  }
  else if (move1 > 0 && move2 > 0 )
  {
    left();
  }
  else if (move1 > 0 && move2 < 0 )
  {
    right();
  }
  else if (move1 < 0)
  {
    back();
  }
  else
  {
    die();
  }
}

ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel", callback);
int PauseTime = 2580;

void setup() {

  nh.initNode();
  nh.subscribe(sub);  
  rightServo.attach(9);
  leftServo.attach(10);

}

void loop() {
  nh.spinOnce();
  delay(1);
}

void front()
{
  leftServo.write(180);
  rightServo.write(0);
  delay(PauseTime);
  die();

}
void back()
{
  leftServo.write(0);
  rightServo.write(180);
  delay(PauseTime);
  die();
}
void left()
{
  leftServo.write(45);
  rightServo.write(45);
  delay(PauseTime);
  die();

}
void right()
{
  leftServo.write(135);
  rightServo.write(135);
  delay(PauseTime);
  die();
}
void die()
{
  leftServo.write(85);
  rightServo.write(85);
}
