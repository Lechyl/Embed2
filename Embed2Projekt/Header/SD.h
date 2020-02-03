#include "mbed.h"
#include "FATFileSystem.h"
#include "SDBlockDeviceDISCOF746NG.h"
#include <stdio.h>
#include <errno.h>


class SD{

    public:

       void Test();

       void
return_error (int ret_val)
{
    if(ret_val)
        printf ("Failure. %d\r\n", ret_val);
    else
        printf ("done.\r\n");
}
 
void
errno_error (void* ret_val)
{
    if(ret_val == NULL)
        printf (" Failure. %d \r\n", errno);
    else
        printf (" done.\r\n");
}
};