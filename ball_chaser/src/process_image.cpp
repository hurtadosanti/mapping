#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    if (!client.call(srv)){
        ROS_ERROR("Failed to drive robot");
    }
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    //ROS_INFO_STREAM("Image size"+std::to_string(img.data.size())+"-"+std::to_string(img.height)+"-"+std::to_string(img.width)+"-"+std::to_string(img.step));
    int position = 0;
    int white_pixel = 255;
    bool white_pixel_found = false;   
    // Loop through each pixel in the image and check if there's a bright white one
    // Actual matrix data, size is (step * rows)
    // rows = height
    for(int i=0;i<img.data.size();i+=3){
        if(img.data[i]==white_pixel&&img.data[i+1]==white_pixel&&img.data[i+2]==white_pixel){
            white_pixel_found=true;
            position = (i/img.width)%3;
        }
    }
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

    if(white_pixel_found){
        if(position==0){
            drive_robot(0.0,0.5);
        }else if(position==1){
            drive_robot(0.2,0.0);
        }else if(position==2){
            drive_robot(0.0,-0.5);
        }
        else{
            ROS_WARN("Another position");
        }
    }else{
        drive_robot(0.0,0.0);
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}