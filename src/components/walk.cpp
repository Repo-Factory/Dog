#include "unitree_legged_sdk.h"
#include <math.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "warning.h"
#include "udp_handler.h"

const int UPDATE_RATE = 1/100;
const char* loop_name = "control_loop";

void walk(UDP_Handler& udp_handler)
{
    UNITREE_LEGGED_SDK::HighCmd cmd = {0};
    cmd.mode = 2;
    cmd.gaitType = 1;
    cmd.velocity[0] = 0.2f;
    udp_handler.SetSend(cmd);
}

int main(void) 
{
    Warning::warning_message();
    UDP_Handler udp_handler = UDP_Handler();
    UNITREE_LEGGED_SDK::LoopFunc loop_control(loop_name, UPDATE_RATE, [&](){walk(udp_handler);});
    loop_control.start();
    return 0; 
}
