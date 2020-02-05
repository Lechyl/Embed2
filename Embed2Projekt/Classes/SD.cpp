
#include "SD.h"
/*
*
*
*   @author: Long and Nilas
*   @date: 21/1-20
*   @brief: This is a class for reading and writing to SD card. with SDBlockDeviceDISCOF746NG Library which is only useable by mbed os 5.9 >= 5.0 
            while we use version 5.15 We tried to make it useable by mbed os 5.15. 
            Only Write and readable  by FAT volume/system on SD.
*   @parameters: @threshold = indikator for when it's night and day in float, @isItDay is a bool variable which check if it's day = true/night = false.
*   
*
*/

SD::SD(){
    fs = new FATFileSystem("fs");
}
void SD::CreateFile(const char* path){


    printf("Start\n");
 

    /// Mounting the sd to FatFileSystem
    printf("Mounting the filesystem on \"/fs\". ");
    error = fs->mount(&bd);
    return_error(error);
    wait(15);
    if (error) {
        /// Reformat if we can't mount the filesystem
        /// this should only happen on the first boot
        printf("No filesystem found, formatting... ");
        
        error = fs->reformat(&bd);
        printf("%s\n", (error ? "Fail :(" : "OK"));
        if (error) {
            printf("error: %s (%d)\n", strerror(-error), error);
        }
    }


    
    
    printf("Opening a new path. %s ",path);
    
    FILE* fd = fopen(path, "w");
    errno_error(fd);
    wait(15);

    printf("Writing something to file done.\r\n");
    int i = fprintf(fd, "bananer");
 
    printf("Closing file. %i ",i);
    fclose(fd);
    printf(" done.\r\n");
 
    printf("Unmounting ");
    error = fs->unmount();
    return_error(error);
    wait(15);
    printf("Filesystem complete, You can now safely remove the sd card.\r\n");

}
bool SD::ReadPassword(string passwordIn){

    hasError= false;

    ///Mounting the SD to FatFileSystem
    printf("Mounting the filesystem on \"/fs\". ");
    error = fs->mount(&bd);
    return_error(error);
    wait(15);
    if(!hasError){
        
        printf("Reading file /fs/password.txt ");
        FILE* fd = fopen("/fs/password.txt", "r");
        errno_error(fd);
        
        if(!hasError){
            printf("Dumping file to screen.\r\n");


        /// Read From file in specific blocks size and insert into the buffer
        char buff[16];
        while(!feof (fd)){
            int size = fread(&buff[0], 1, 15, fd);
             fwrite(&buff[0], 1, size, stdout);
        }
    printf(("password input = "+ passwordIn).c_str());

        ///Compare input and output password
        if(passwordIn.c_str() ==(string)&buff[0] ){
            printf(" Correct Password \n");
            validPassword = true;
        }
        printf("Closing file.");
        fclose(fd);
        printf(" done.\r\n");
        }


    }
        printf("Unmounting ");
        error = fs->unmount();
        return_error(error);
        wait(15);
        printf("Filesystem complete, You can now safely remove the sd card.\r\n");

    return validPassword;
}