#include "ros/ros.h"
#include "std_msgs/String.h"

#include <termios.h>
#include <sstream>

int getch() {
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);           // save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON);                 // disable buffering
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

    char c = getchar();  // read character (non-blocking)

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
    return c;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "keypubber");
    ros::NodeHandle n;

    ros::Publisher keypubber = n.advertise<std_msgs::String>("chatter", 1000);

    ros::Rate loop_rate(10);

    while (ros::ok()) {
        char in = getch();

        std_msgs::String msg;

        switch(in) {
            case 'r':
                msg.data = "r";
                break;
            case 'f':
                msg.data = "f";
                break;
            case 'n':
                msg.data = "n";
                break;
        }

        keypubber.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}

