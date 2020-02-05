#include "EthernetClass.h"

Ethernet::Ethernet(){
    /*
    _eth.connect();
    _eth.get_ip_address();
    _ntp(_eth);
     */
}
Ethernet::~Ethernet(){

}

time_t GetTime(){
    EthernetInterface eth;
    eth.connect();
     eth.get_ip_address();
    NTPClient ntp(&eth);

    return ntp.get_timestamp();
}