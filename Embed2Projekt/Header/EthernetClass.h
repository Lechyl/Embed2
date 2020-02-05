#ifndef EthernetClass_Nilas
#define EthernetClass_Nilas

#include "mbed.h"
#include "EthernetInterface.h"
#include "ntp-client/NTPClient.h"


class Ethernet{
    private:
        //  EthernetInterface _eth;
        //NTPClient _ntp;

    public:
        Ethernet();
        ~Ethernet();
        time_t getTime();

};
#endif