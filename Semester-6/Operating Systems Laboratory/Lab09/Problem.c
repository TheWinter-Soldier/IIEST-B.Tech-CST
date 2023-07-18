#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>          //for lseek() and read()
#include <sys/types.h>       //for open() and lseek()
#include <sys/stat.h>        //for open()
#include <fcntl.h>           //for open()

#include "Interface.h"

const char *Path = "/home/kuldip/Desktop/OS_Lab/Lab09/dd1";     //File-system to be created here

//A direct-access array for effecient and fast printing of bytes in binary format
const char *bit_rep[16] = {[ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
                           [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
                           [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
                           [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111"};

/**
 * @brief This function can print one byte at a time in binary format.
 * 
 * @param byte A single byte data
 */
void print_byte(uint8_t byte) {
    printf("%s%s | ",bit_rep[byte >> 4],bit_rep[byte & 0x0F]);
}

int main() {
    int fd, i=0;

    init_File_dd(Path,BLOCK_SIZE,NUMBER_OF_BLOCKS);

    get_freeblock(Path);
    get_freeblock(Path);
    get_freeblock(Path);

    free_block(Path,1);

    get_freeblock(Path);
    get_freeblock(Path);
    get_freeblock(Path);

    free_block(Path,3);

    fd = open(Path,O_RDONLY);

    //while(i<8389632) {
    while(i<1024) {
        char buf;

        if(lseek(fd,i,SEEK_SET) == -1) {
            perror("lseek() failed");
            exit(EXIT_FAILURE);
        }
        if(read(fd,&buf,1) == -1) {
            perror("read() failed");
            exit(EXIT_FAILURE);
        }

        print_byte(buf);

        if((i%4 == 3) && (i<16)) printf("\n");
        if(i==15) printf("\n");
        
        i++;
    } 
    printf("\n");

    close(fd);

    return 0;
}