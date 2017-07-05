#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Range.h>
#define SENSOR_COUNT 8

ros::NodeHandle  nh;
sensor_msgs::Range ultrasonic;
ros::Publisher distance_pub_0("Ultrasound/Sensor0", &ultrasonic);
ros::Publisher distance_pub_1("Ultrasound/Sensor1", &ultrasonic);
ros::Publisher distance_pub_2("Ultrasound/Sensor2", &ultrasonic);
ros::Publisher distance_pub_3("Ultrasound/Sensor3", &ultrasonic);
ros::Publisher distance_pub_4("Ultrasound/Sensor4", &ultrasonic);
ros::Publisher distance_pub_5("Ultrasound/Sensor5", &ultrasonic);
ros::Publisher distance_pub_6("Ultrasound/Sensor6", &ultrasonic);
ros::Publisher distance_pub_7("Ultrasound/Sensor7", &ultrasonic);

int trig_pins[] = {A3,A2,A1,A0,6,8,10,12}; // -1 indicates that an analoge Pin is used
int echo_pins[] = {2,3,4,5,7,9,11,13}; 
int sensor_ids[] = {0,4,1,5,7,3,6,2};  //order to trigger the sensor to avoid reflections



long ultraschall_echo_time(int i) {
  
  digitalWrite(trig_pins[i], LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pins[i], HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pins[i], LOW);
  
  
  long duration = pulseIn(echo_pins[i], HIGH, 20000); // Timeout for 3 meters and offset compensation as the timout 18122
  if(duration == 0){
      pinMode(echo_pins[i], OUTPUT); // Then we set echo pin to output mode
      digitalWrite(echo_pins[i], LOW); // We send a LOW pulse to the echo pin
      delayMicroseconds(200);
      pinMode(echo_pins[i], INPUT); // And finaly we come back to input mode
  }  
  return duration;                                    // includes the time it needs to wait until the echo_pin gets high (the time it takes from the end of the trigger signal 
}                                                     // to the time the ultrasonic is deployed and the echo_pin switches to high)

void setup() {
  nh.initNode();
  nh.advertise(distance_pub_0);
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
  delay(100);
} 

void loop()
{   
  for(int i=0; i < SENSOR_COUNT; i++){
    int sensor_id = sensor_ids[i];
    long duration = ultraschall_echo_time(sensor_id);
    
    if( duration == 0) {
      ultrasonic.range = ultrasonic.max_range;
    } else {
      ultrasonic.range = 343.500 * duration / 2000000;
    }
    
    ultrasonic.header.stamp = nh.now();
    
    switch (sensor_id) {
      case 0: 
      ultrasonic.header.frame_id = "US0_link";
      distance_pub_0.publish(&ultrasonic);
      break;
      case 1: 
      ultrasonic.header.frame_id = "US1_link";
      distance_pub_1.publish(&ultrasonic);
      break;
      case 2: 
      ultrasonic.header.frame_id = "US2_link";
      distance_pub_2.publish(&ultrasonic);
      break;
      case 3: 
      ultrasonic.header.frame_id = "US3_link";
      distance_pub_3.publish(&ultrasonic);
      break;
      case 4: 
      ultrasonic.header.frame_id = "US4_link";
      distance_pub_4.publish(&ultrasonic);
      break;
      case 5: 
      ultrasonic.header.frame_id = "US5_link";
      distance_pub_5.publish(&ultrasonic);
      break;
      case 6: 
      ultrasonic.header.frame_id = "US6_link";
      distance_pub_6.publish(&ultrasonic);
      break;
      case 7: 
      ultrasonic.header.frame_id = "US7_link";
      distance_pub_7.publish(&ultrasonic);
      break;
      
    }
    
    nh.spinOnce();
  }
}
