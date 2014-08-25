
#include "pylon_camera/PylonCameraInterface.h"

#include <ros/ros.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

    ros::init(argc, argv, "pylon_node");
    ros::NodeHandle n;
    std::string  camera_identifier, camera_frame;
        
        
    n.param<std::string>("camera_identifier", camera_identifier, "*");
    n.param<std::string>("camera_frame", camera_frame, "GripperCam");
               
    PylonCameraInterface pylon_cam;

    if (!pylon_cam.openCamera(camera_identifier, camera_frame)){
        return 42;
    }

    int max_frame_rate = 30;

    ros::Rate r(max_frame_rate);
    while(ros::ok()){
        pylon_cam.sendNextImage();
        r.sleep();
        ros::spinOnce();
    }

    // pylon interface is closed in its own deconstructor
    return 0;
}



