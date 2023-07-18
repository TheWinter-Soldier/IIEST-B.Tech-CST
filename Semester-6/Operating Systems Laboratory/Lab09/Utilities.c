#include <stdio.h>      //for perror()
#include <stdlib.h>     //for exit()

#include <unistd.h>     //for lseek() and read()
#include <sys/types.h>  //for open() and lseek()
#include <sys/stat.h>   //for open()
#include <fcntl.h>      //for open()

#include <inttypes.h>

#include "Utilities.h"

#include <errno.h>

void decodeSuperblock(int _fd,superblock *sb) {
    int n;
    uint8_t buffer[256];

    if(lseek(_fd,0,SEEK_SET) == -1) {       //Getting the total number of blocks
        perror("lseek() failed");
        exit(EXIT_FAILURE);
    }
    if(read(_fd,&n,4) == -1) {
        perror("read() failed");
        exit(EXIT_FAILURE);
    }
    sb->n = n;

    if(lseek(_fd,4,SEEK_SET) == -1) {       //Getting the size of each block
        perror("lseek() failed");
        exit(EXIT_FAILURE);
    }
    if(read(_fd,&n,4) == -1) {
        perror("read() failed");
        exit(EXIT_FAILURE);
    }
    sb->s = n;

    if(lseek(_fd,8,SEEK_SET) == -1) {       //Getting the number of used blocks
        perror("lseek() failed");
        exit(EXIT_FAILURE);
    }
    if(read(_fd,&n,4) == -1) {
        perror("read() failed");
        exit(EXIT_FAILURE);
    }
    sb->ubn = n;

    if(lseek(_fd,12,SEEK_SET) == -1) {      //Getting the number of free blocks
        perror("lseek() failed");
        exit(EXIT_FAILURE);
    }
    if(read(_fd,&n,4) == -1) {
        perror("read() failed");
        exit(EXIT_FAILURE);
    }
    sb->fbn = n;

    for(int i=0;i<256;i++) {                //Getting the bitmap
        if(lseek(_fd,16+i,SEEK_SET) == -1) {
            perror("lseek() failed");
            exit(EXIT_FAILURE);
        }
        if(read(_fd,&buffer[i],1) == -1) {
            perror("read() failed");
            exit(EXIT_FAILURE);
        }
        sb->ub[i] = buffer[i];
    }
}