#ifndef UDP_HANDLER_H 
#define UDP_HANDLER_H 

#include "unitree_legged_sdk.h"

class UDP_Handler
{
    public:
        UDP_Handler();
        void SetSend(UNITREE_LEGGED_SDK::HighCmd &cmd);
        void GetRecv(UNITREE_LEGGED_SDK::HighState &state);
        void Send();
        void Recv();
    private:
        UNITREE_LEGGED_SDK::UDP udp_handler;
};

#endif