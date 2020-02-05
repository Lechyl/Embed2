#ifndef EthernetClass_Nilas
#define EthernetClass_Nilas

#include "mbed.h"
#include "EthernetInterface.h"
#include "ntp-client/NTPClient.h"


class Ethernet{
    private:
    public:
        Ethernet();
        ~Ethernet();
        time_t getTime();

};
#endif