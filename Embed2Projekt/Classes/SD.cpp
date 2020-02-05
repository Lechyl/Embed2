
#include "SD.h"


SD::SD(){
    fs = new FATFileSystem("fs");
}
void SD::CreateFile(const char* t){


    printf("Start\n");
 

 
    printf("Mounting the filesystem on \"/fs\". ");
    error = fs->mount(&bd);
    return_error(error);
    wait(15);
    if (error) {
        // Reformat if we can't mount the filesystem
        // this should only happen on the first boot
        printf("No filesystem found, formatting... ");
        
        error = fs->reformat(&bd);
        printf("%s\n", (error ? "Fail :(" : "OK"));
        if (error) {
            printf("error: %s (%d)\n", strerror(-error), error);
        }
    }


    
    
    printf("Opening a new path. %s ",t);
    
    FILE* fd = fopen(t, "w");
    errno_error(fd);
    wait(15);
    
    int i = fprintf(fd, "bananer");
    printf("Writing decimal numbers to a file (20/20) done.\r\n");
 
    printf("Closing file. %i ",i);
    fclose(fd);
    printf(" done.\r\n");
 
    printf("Unmounting ");
    error = fs->unmount();
    return_error(error);
    wait(15);
    printf("Filesystem complete, You can now safely remove the sd card.\r\n");
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

 
}
bool SD::ReadPassword(string passwordIn){
    hasError= false;
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
            char buff[16];
            
           
        while(!feof (fd)){
            int size = fread(&buff[0], 1, 15, fd);
             fwrite(&buff[0], 1, size, stdout);
        }
    printf(("password input = "+ passwordIn).c_str());

       // string test = &buff[0];
      //  printf(" %i == %i ",*passwordIn,&buff[0] );
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

/*    printf("Opening root directory.");
    DIR* dir = opendir("/fs/");
    errno_error(fd);
 
    struct dirent* de;
    printf("Printing all filenames:\r\n");
    while((de = readdir (dir)) != NULL) {
        printf("  %s\r\n", &(de->d_name)[0]);
    }
 
    printf("Closeing root directory. ");
    error = closedir(dir);
    return_error(error); 
*/
    return validPassword;
}