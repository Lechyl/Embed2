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

/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: Get timestamp since 1. january 1970
*/
time_t GetTime(){
    //Get ethernet connection
    EthernetInterface eth;
    //Connect to internet and get ip address
    eth.connect();
    eth.get_ip_address();

    //Instanciate the ntp client class
    NTPClient ntp(&eth);
    //Get timestamp
    time_t timestamp = ntp.get_timestamp();
    //Close connection
    eth.disconnect();
    return timestamp;
}