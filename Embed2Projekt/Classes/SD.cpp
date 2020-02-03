
#include "SD.h"

void SD::Test(){
SDBlockDeviceDISCOF746NG bd;
FATFileSystem fs ("fs");

     printf("Start\n");
 
    int error = 0;
   // printf("Welcome to the filesystem example.\r\n"
     //      "Formatting a FAT, RAM-backed filesystem. ");
    //error = FATFileSystem::format(&bd);
    //return_error(error);
 
    printf("Mounting the filesystem on \"/fs\". ");
    error = fs.mount(&bd);
    wait(10);
    if (error) {
        // Reformat if we can't mount the filesystem
        // this should only happen on the first boot
        printf("No filesystem found, formatting... ");
        fflush(stdout);
        error = fs.reformat(&bd);
        printf("%s\n", (error ? "Fail :(" : "OK"));
        if (error) {
            printf("error: %s (%d)\n", strerror(-error), error);
        }
    }


    return_error(error);
    
    printf("Opening a new file, numbers.txt.");
    FILE* fd = fopen("/fs/work.txt", "w");
    errno_error(fd);
    wait(10);
    /*for (int i = 0; i < 20; i++) {
        printf("Writing decimal numbers to a file (%d/20)\r", i);
        fprintf(fd, "%d\r\n", i);
    }*/
    int i = fprintf(fd, "bananer");
    printf("Writing decimal numbers to a file (20/20) done.\r\n");
 
    printf("Closing file. %i ",i);
    fclose(fd);
    printf(" done.\r\n");
 
     printf("Unmounting ");
    error = fs.unmount();
    return_error(error);
    wait(10);
    printf("Filesystem Demo complete.\r\n");
   /* printf("Re-opening file read-only.");
    fd = fopen("/fs/numbers.txt", "r");
    errno_error(fd);
 
    printf("Dumping file to screen.\r\n");
    char buff[16] = { 0 };
    while(!feof (fd)) {
        int size = fread(&buff[0], 1, 15, fd);
        fwrite(&buff[0], 1, size, stdout);
    }
    printf("EOF.\r\n");
 
    printf("Closing file.");
    fclose(fd);
    printf(" done.\r\n");
 
    printf("Opening root directory.");
    DIR* dir = opendir("/fs/");
    errno_error(fd);
 
    struct dirent* de;
    printf("Printing all filenames:\r\n");
    while((de = readdir (dir)) != NULL) {
        printf("  %s\r\n", &(de->d_name)[0]);
    }
 
    printf("Closeing root directory. ");
    error = closedir(dir);
    return_error(error); */

    while(true){

    }
 
}