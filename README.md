# ROS_Robot
ROS based robot with Arduino as a node

To test various features, Upload the appropriate arduino code to arduino, and do the following

### General Procedure.

Run each of the following commands in a new window:

roscore

rosrun rosserial_python serial_node.py /dev/ttyACM0 

#### Twist Teleop

rosrun teleop_twist_keyboard teleop_twist_keyboard.py

Use keyboard keys to operate the robot. Makr sure the teleop window is active while you give commands.

#### MotorControl

This program controls a vehicle powered by 2 continuous rotation servos. The robot motion is controlled via subscribing to the twist commands topic. For example:

rostopic pub -1 cmd_vel geometry_msgs/Twist -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, 1.8]'

#### Locomotive Robotic Arm

This code intgrates Locomotion and Robotic arm. The locomotion is acheived by 2 DC motors in differential drive configuration. The motors are controlled via Motor driver. The arm is a 3 DOF arm with a gripper. which makes up a total of 4 servo motors to control. This code is tested on Raspberry pi running ROS kinetic.

The Locomotion commands are published on "Navigation" topic 
The Servo angles are published on their own differnt Topics.

This is a work in progress. More updates and upgrades comming up.
