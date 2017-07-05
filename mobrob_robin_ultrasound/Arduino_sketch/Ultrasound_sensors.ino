#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Range.h>
#define SENSOR_COUNT 7

ros::NodeHandle  nh;
sensor_msgs::Range ultrasonic;
ros::Publisher distance_pub_1("ultrasound/sensor1", &ultrasonic);
ros::Publisher distance_pub_2("ultrasound/sensor2", &ultrasonic);
ros::Publisher distance_pub_3("ultrasound/sensor3", &ultrasonic);
ros::Publisher distance_pub_4("ultrasound/sensor4", &ultrasonic);
ros::Publisher distance_pub_5("ultrasound/sensor5", &ultrasonic);
ros::Publisher distance_pub_6("ultrasound/sensor6", &ultrasonic);
ros::Publisher distance_pub_7("ultrasound/sensor7", &ultrasonic);
int trig_pins[] = {-1,10,4,6,8,-1,12}; // -1 indicates that an analoge Pin is used
int echo_pins[] = {2,11,5,7,9,3,13}; 
int sensor_ids[] ={1, 6, 3, 4, 5, 2, 7}; 


long ultraschall_echo_time(int i) {
  
  if (sensor_ids[i] == 1 || sensor_ids[i] == 2) { // Analog Pins are used for the Trigger Impulse as there are not enough Digital Pins
    if (sensor_ids[i] == 1) {
      digitalWrite(A0, LOW);
      delayMicroseconds(2);
      digitalWrite(A0, HIGH);
      delayMicroseconds(10);
      digitalWrite(A0, LOW);
    } else {
      digitalWrite(A1, LOW);
      delayMicroseconds(2);
      digitalWrite(A1, HIGH);
      delayMicroseconds(10);
      digitalWrite(A1, LOW);
    }
    
  } else {
    digitalWrite(trig_pins[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pins[i], LOW);
  }
  
  long duration = pulseIn(echo_pins[i], HIGH, 18122); // Timeout for 3 meters and offset compensation as the timout 
  return duration;                                    // includes the time it needs to wait until the echo_pin gets high (the time it takes from the end of the trigger signal 
}                                                     // to the time the ultrasonic is deployed and the echo_pin switches to high)

void setup() {
  nh.initNode();
  nh.advertise(distance_pub_1);
  nh.advertise(distance_pub_2);
  nh.advertise(distance_pub_3);
  nh.advertise(distance_pub_4);
  nh.advertise(distance_pub_5);
  nh.advertise(distance_pub_6);
  nh.advertise(distance_pub_7);

  ultrasonic.radiation_type = 0;
  ultrasonic.field_of_view = 15.0/180.0 *3.1415;
  ultrasonic.min_range = 0.05;                // set so that roomba doesnt have a collision if it passes an obstacle really close
  ultrasonic.max_range = 3.0;      

  for(int i=0; i < SENSOR_COUNT; i++) {
    if(trig_pins[i]!=-1) {
      pinMode(trig_pins[i], OUTPUT);
      }
    pinMode(echo_pins[i], INPUT); 
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  
  delay(100);
}

 

void loop()
{   
  for(int i=0; i < SENSOR_COUNT; i++){
    long duration = ultraschall_echo_time(i);
    
    if( duration == 0) {
      ultrasonic.range = ultrasonic.max_range;
    } else {
      ultrasonic.range = 343.500 * duration / 2000000;
    }
    
    ultrasonic.header.stamp = nh.now();
    
    switch (i) {
      case 0: 
      ultrasonic.header.frame_id = "US1_link";
      distance_pub_1.publish(&ultrasonic);
      break;
      case 1: 
      ultrasonic.header.frame_id = "US6_link";
      distance_pub_6.publish(&ultrasonic);
      break;
      case 2: 
      ultrasonic.header.frame_id = "US3_link";
      distance_pub_3.publish(&ultrasonic);
      break;
      case 3: 
      ultrasonic.header.frame_id = "US4_link";
      distance_pub_4.publish(&ultrasonic);
      break;
      case 4: 
      ultrasonic.header.frame_id = "US5_link";
      distance_pub_5.publish(&ultrasonic);
      break;
      case 5: 
      ultrasonic.header.frame_id = "US2_link";
      distance_pub_2.publish(&ultrasonic);
      break;
      case 6: 
      ultrasonic.header.frame_id = "US7_link";
      distance_pub_7.publish(&ultrasonic);
      break;
      
    }
    
    nh.spinOnce();
  }
}
