
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <Ultrasonic.h>
#include <Kalman.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     13

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

Kalman kalman(0, 1023, 2, 0.125);

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);

sensor_msgs::Range range_msg_K;
ros::Publisher pub_range_K( "/Kalman_ultrasound", &range_msg_K);

char frameid[] = "/ultrasound";

float getRange_Ultrasound(int pin_num){
  
  float cmMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  return cmMsec;
}

void setup()
{
  
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(pub_range);
  nh.advertise(pub_range_K);
  
  
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 15/57.2958;  // fake
  range_msg.min_range = 2.0;
  range_msg.max_range = 400.0;
  
  range_msg_K.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg_K.field_of_view = 15/57.2958;  // fake
  range_msg_K.min_range = 2.0;
  range_msg_K.max_range = 400.0;
  range_msg_K.header.frame_id = "/Kalman_ultrasound";
}


long range_time;

void loop()
{
  
  //publish the adc value every 50 milliseconds
  //since it takes that long for the sensor to stablize
  if ( millis() >= range_time ){
    int r =0;

    range_msg.range = getRange_Ultrasound(5);
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);

    range_msg_K.range = kalman.execute(range_msg.range);
    range_msg_K.header.stamp = nh.now();
    pub_range_K.publish(&range_msg_K);
    range_time =  millis() + 50;
  }
  
  nh.spinOnce();
}
