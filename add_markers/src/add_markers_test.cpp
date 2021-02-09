#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <std_msgs/Bool.h>

// Define global pickup and dropoff variables and boolean values

// Create pickup pose and orientation variables
float pickup[3] = {-20.0, 3.0, 1.0};

// Create dropoff pose and orientation variables
float dropoff[3] = {-10.0, 8.5, 1.0};

// Create error vector to account for noise
// float error[2] = {0.3,0.1};

bool arrived_at_pickup = false;
bool arrived_at_dropoff = false;
bool completed_pickup = false;
bool completed_dropoff = false;
bool at_goal = false;
 
/*
// This callback function continuously compares the odometry against the pickup and drop off poses of the markers and makes them disappear and appear, respectively
void move_object_callback(const nav_msgs::Odometry::ConstPtr& msg){
  if(fabs(pickup[0] - msg->pose.pose.position.x) < error[0] && fabs(pickup[1] - msg->pose.pose.position.y)< error[0]){// && fabs(pickup[2] - msg.pose.pose.orientation.w) < error[1]){
    if(!arrived_at_pickup){
      ROS_INFO("At the pickup location");
      arrived_at_pickup = true;
    }
  }
  else{
      arrived_at_pickup = false;
  }
  if(fabs(dropoff[0] - msg->pose.pose.position.x) < error[0] && fabs(dropoff[1] - msg->pose.pose.position.y) < error[0]){ //&& fabs(dropoff[2] - msg.pose.pose.orientation.w) < error[1]){
    if(!arrived_at_dropoff){
      ROS_INFO("At the dropoff location");
      arrived_at_dropoff = true;
    }
  }
  else{
    arrived_at_dropoff = false;
  }
}*/
/*
// This callback function waits for a message to be published goal_pub defined in the pick_objects.cpp and uses that information to decide if it has reached the goal or not, and acts accordindly
void move_object_callback(const std_msgs::Bool::ConstPtr& msg){
  //ROS_INFO("I am in the callback function");
    
  at_goal = msg->data;

  //ROS_INFO("I received this: ", at_goal);
  if(at_goal == true){
    if(arrived_at_pickup == false){
      arrived_at_pickup = true;
    }
    else if(arrived_at_pickup == true)
      if(arrived_at_dropoff == false){
        arrived_at_dropoff = true;
    }
  }
  return;
}

*/
int main( int argc, char** argv ){
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  //ros::Subscriber pickobj_sub = n.subscribe("reached_goal", 100, move_object_callback);
  //ros::Subscriber odom_sub = n.subscribe("odom",100,move_object_callback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::SPHERE;

  //while(ros::ok()){
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "sphere";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pickup pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = pickup[0];
    marker.pose.position.y = pickup[1];
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = pickup[2];

    // Set the pickup scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration(); 

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);
    
    ROS_INFO("Marker should be published");
    
    ros::Duration(5.0).sleep();
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Marker should be gone");
    ros::Duration(5.0).sleep();
    
    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD; 
    marker.pose.position.x = dropoff[0];
    marker.pose.position.y = dropoff[1];
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = dropoff[2];
      
    marker_pub.publish(marker);
    ROS_INFO("Marker should be published again");
    ros::Duration(5.0).sleep();
    r.sleep();
  //}
  return 0;
}
