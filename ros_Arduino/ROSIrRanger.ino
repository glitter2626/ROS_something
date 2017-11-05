#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <Kalman.h>

ros::NodeHandle  nh;

Kalman kalman(0, 1023, 2, 0.125);


sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/IR", &range_msg);

sensor_msgs::Range range_msg_K;
ros::Publisher pub_range_K( "/Kalman_IR", &range_msg_K);

const int analog_pin = 0;
unsigned long range_timer;

char frameid[] = "/ir_ranger";

void setup()
{
  pinMode(A0, INPUT);

  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(pub_range);
  nh.advertise(pub_range_K);

  range_msg.radiation_type = sensor_msgs::Range::INFRARED;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.01;
  range_msg.min_range = 0.02;
  range_msg.max_range = 1.5;

  range_msg_K.radiation_type = sensor_msgs::Range::INFRARED;
  range_msg_K.header.frame_id =  "/Kalman_IR";
  range_msg_K.field_of_view = 0.01;
  range_msg_K.min_range = 0.02;
  range_msg_K.max_range = 1.5;
}

void loop()
{
  // publish the range value every 50 milliseconds
  //   since it takes that long for the sensor to stabilize
  if ( millis() >= range_timer) {
    int val = analogRead(A0); // read the sensor
    float data = (10650.08 * pow(val, -0.935) - 10) / 100.0;
    range_msg.range = data;
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);

    range_msg_K.range = kalman.execute(data);
    range_msg_K.header.stamp = nh.now();
    pub_range_K.publish(&range_msg_K);

    range_timer =  millis() + 50;
  }
  nh.spinOnce();
}

