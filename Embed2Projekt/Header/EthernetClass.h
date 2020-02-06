#ifndef EthernetClass_Nilas
#define EthernetClass_Nilas

#include "mbed.h"
#include "EthernetInterface.h"
#include "ntp-client/NTPClient.h"
//#include "time.h"


class Ethernet{
    private:
    public:
        Ethernet();
        ~Ethernet();
        char* GetTime();

};
#endif