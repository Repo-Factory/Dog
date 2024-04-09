#include "udp_handler.h"

const int   local_port  = 8090;
const char* target_ip   = "192.168.123.161";
const int   target_port = 8082;

UDP_Handler::UDP_Handler()
    : udp_handler(UNITREE_LEGGED_SDK::HIGHLEVEL, local_port, target_ip, target_port)
{
    UNITREE_LEGGED_SDK::HighCmd cmd = {0};
    this->udp_handler.InitCmdData(cmd);
}

void UDP_Handler::SetSend(UNITREE_LEGGED_SDK::HighCmd& cmd)
{
    this->udp_handler.SetSend(cmd);
}

void UDP_Handler::GetRecv(UNITREE_LEGGED_SDK::HighState& state)
{
    this->udp_handler.GetRecv(state);
}

void UDP_Handler::Send()
{
    this->udp_handler.Send();
}

void UDP_Handler::Recv()
{
    this->udp_handler.Recv();
}
