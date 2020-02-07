#include "mbed.h"
#include "FATFileSystem.h"
#include "SDBlockDeviceDISCOF746NG.h"
#include <stdio.h>
#include <errno.h>
#include <string>


class SD{
    private:
        bool validPassword = false;
        SDBlockDeviceDISCOF746NG bd;
        FATFileSystem *fs;
        int error = 0;
    public:
       bool hasError;
        SD();
       void CreateFile(const char* t);
       bool ReadPassword(string passwordIn);
       void
return_error (int ret_val)
{
    if(ret_val){
        printf ("Failure. %d\r\n", ret_val);
        hasError = true;

    }
    else{

        printf ("done.\r\n");
    }
}
 
void
errno_error (void* ret_val)
{
    if(ret_val == NULL){

        printf (" Failure. %d \r\n", errno);
        hasError = true;
    }
    else{

        printf (" done.\r\n");
    }
}
};