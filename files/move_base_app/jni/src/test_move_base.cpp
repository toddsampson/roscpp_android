#include <stdarg.h>
#include <stdio.h>
#include <sstream>
#include <map>
#include <string.h>
#include <errno.h>
#include <vector>
#include <set>
#include <fstream>
#include <android/log.h>
// %Tag(FULL_TEXT)%

// %Tag(ROS_HEADER)%
#include "ros/ros.h"
#include <move_base/move_base.h>
// %EndTag(ROS_HEADER)%

// %Tag(ANDROID_NATIVE_HEADER)%
#include <android_native_app_glue.h>
// %EndTag(ANDROID_NATIVE_HEADER)%

void log(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    __android_log_vprint(ANDROID_LOG_INFO, "MOVE_BASE_NDK_EXAMPLE", msg, args);
    va_end(args);
}


// %Tag(MAIN)%
void android_main(android_app *papp) {
    // Make sure glue isn't stripped
    app_dummy();

    int argc = 4;
    // TODO: don't hardcode ip addresses
    // %Tag(CONF_ARGS)%
    char *argv[] = {"nothing_important" , "__master:=http://192.168.1.100:11311",
                    "__ip:=192.168.1.101", "cmd_vel:=navigation_velocity_smoother/raw_cmd_vel"};
    // %EndTag(CONF_ARGS)%

    log("GOING TO ROS INIT");

    for(int i = 0; i < argc; i++){
        log(argv[i]);
    }

    // %Tag(ROS_INIT)%
    ros::init(argc, &argv[0], "move_base");
    // %EndTag(ROS_INIT)%

    log("GOING TO NODEHANDLE");

    // %Tag(ROS_MASTER)%
    std::string master_uri = ros::master::getURI();

    if(ros::master::check()){
        log("ROS MASTER IS UP!");
    } else {
        log("NO ROS MASTER.");
    }
    log(master_uri.c_str());

    ros::NodeHandle n;
    // %EndTag(ROS_MASTER)%

    log("GOING TO MOVE_BASE");
    tf::TransformListener tf(ros::Duration(10));
    move_base::MoveBase move_base(tf);

    log("GOING TO SPIN");

    ros::WallRate loop_rate(100);
    // %Tag(ROS_SPIN)%
    while(ros::ok() && !papp->destroyRequested){
        ros::spinOnce();
        loop_rate.sleep();
    }
    // %EndTag(ROS_SPIN)%
}
// %EndTag(MAIN)%
// %EndTag(FULL_TEXT)%
