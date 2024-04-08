#include "udp_handler.h"

const int   local_port  = 8090;
const char* target_ip   = "192.168.123.161";
const int   target_port = 8082;

UDP_Handler::UDP_Handler()
    : udp_handler(UNITREE_LEGGED_SDK::HIGHLEVEL, local_port, target_ip, target_port)
{
    UNITREE_LEGGED_SDK::HighCmd cmd = {0};
    this->udp_handler.InitCmdData(cmd);
    this->UDPLoop();
}

const int UPDATE_RATE = 1/100;
void UDP_Handler::UDPLoop()
{
    UNITREE_LEGGED_SDK::LoopFunc loop_udpSend("udp_send", UPDATE_RATE, 3, [&](){this->udp_handler.Send();});
    UNITREE_LEGGED_SDK::LoopFunc loop_udpRecv("udp_recv", UPDATE_RATE, 3, [&](){this->udp_handler.Recv();});
    loop_udpSend.start();
    loop_udpRecv.start();
}

void UDP_Handler::SetSend(UNITREE_LEGGED_SDK::HighCmd &cmd)
{
    this->udp_handler.SetSend(cmd);
}
