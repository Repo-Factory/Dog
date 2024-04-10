#include "unitree_legged_sdk.h"
#include <math.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "warning.h"
#include "udp_handler.h"

const float UPDATE_RATE = .002f;
const float SAFE_VELOCITY = 0.2f;
const char* loop_name = "control_loop";

void walk(UDP_Handler& udp_handler)
{
    UNITREE_LEGGED_SDK::HighCmd cmd = {0};
    cmd.mode = 2;
    cmd.gaitType = 1;
    cmd.velocity[0] = 0.2f;
    udp_handler.SetSend(cmd);
}

int determine_cycles(const float update_rate, const float desired_distance, const float velocity)
{
    const float time_to_walk = desired_distance/velocity;
    return time_to_walk/update_rate;
}

void send_command(const int times, std::function<void()> callback)
{
    int i = 0;
    while (i++ < times)
    {
        callback();
    }
}

class WalkService
{
    public:
        WalkService(const UDP_Handler& udp_handler) : 
            _udp_handler(udp_handler)
        {}
        void walk_distance(const float desired_distance)
        {
            const int cycles = (determine_cycles(UPDATE_RATE, desired_distance, SAFE_VELOCITY));
            send_command(cycles, [&](){walk(this->_udp_handler);});
        }
    private:
        const UDP_Handler& _udp_handler;
}

class StopService
{
    public:
        StopService(const UDP_Handler& udp_handler) : 
            _udp_handler(udp_handler)
        {}
        void stop_robot()
        {
            UNITREE_LEGGED_SDK::HighCmd cmd = {0};
            this->_udp_handler.SetSend(cmd);
        }
    private:
        const UDP_Handler& _udp_handler;
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
