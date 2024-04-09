#include "unitree_legged_sdk.h"
#include <math.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "warning.h"
#include "udp_handler.h"

const float UPDATE_RATE = .002;
const char* loop_name = "control_loop";

void walk(UDP_Handler& udp_handler)
{
    UNITREE_LEGGED_SDK::HighCmd cmd = {0};
    cmd.mode = 2;
    cmd.gaitType = 1;
    cmd.velocity[0] = 0.2f;
    udp_handler.SetSend(cmd);
}

void init_app(UDP_Handler udp_handler, const std::function<void(UDP_Handler&)> loop)
{
    UNITREE_LEGGED_SDK::LoopFunc loop_udpRecv("udp_recv", UPDATE_RATE, 3, [&](){udp_handler.Recv();});
    UNITREE_LEGGED_SDK::LoopFunc loop_udpSend("udp_send", UPDATE_RATE, 3, [&](){udp_handler.Send();});
    UNITREE_LEGGED_SDK::LoopFunc loop_control(loop_name,  UPDATE_RATE, 0, [&](){loop(udp_handler);});
    loop_udpSend.start();
    loop_udpRecv.start();
    loop_control.start();
    for(;;) {sleep(10);};
}

int main(void) 
{
    Warning::warning_message();
    UDP_Handler udp_handler = UDP_Handler();
    init_app(udp_handler, &walk);
    return 0; 
}
