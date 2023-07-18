/**
 * @file FileSystem.c
 * @author Kuldip Kundu (2020CSB022)
 * @brief A modest effort to implement an interface that works like file-system as maintained by OS.
 * @date 2023-03-17
 */
#include <stdio.h>           //for dprintf()
#include <stdlib.h>          //for exit()
#include <string.h>          //for memset()

#include <unistd.h>          //for lseek(), read() and write()
#include <sys/types.h>       //for open() and lseek()
#include <sys/stat.h>        //for open()
#include <fcntl.h>           //for open()

#include <inttypes.h>

#include "Utilities.h"       //for decodeSuperblock()
#include "Interface.h"

#include <errno.h>           //for perror()

const int get_bit[2] = {[0] = 0, [1] = 1};                      //A direct-access array to check bits at particular positions in a byte

int check_fs(const char *fname) {
    int workfd;
    superblock *metadata = (superblock *)malloc(sizeof(superblock));

    if((workfd = open(fname,O_RDONLY)) == -1) {  //error ENOENT
        perror("open() failed");
        return -1;
    }

    decodeSuperblock(workfd,metadata);

    if(metadata->fbn + metadata->ubn != metadata->n) return -1;

    if(metadata->ubn > 0) {
        int i=0, count=0;
        while(i<256) {
            if(get_bit[metadata->ub[i] >> 7] == 1) {                 //Checking MSB ('x'xxxxxxx)
                count++;
            }
            if(get_bit[(metadata->ub[i] >> 6) & 0b01] == 1) {        //Checking 2nd MSB (x'x'xxxxxx)
                count++;
            }
            if(get_bit[(metadata->ub[i] >> 5) & 0b001] == 1) {       //Checking 3rd MSB (xx'x'xxxxx)
                count++;
            }
            if(get_bit[(metadata->ub[i] >> 4) & 0x1] == 1) {         //Checking 4th MSB (xxx'x'xxxx)
                count++;
            }
            if(get_bit[(metadata->ub[i] >> 3) & 0b00001] == 1) {     //Checking 5th MSB (xxxx'x'xxx)
                count++;
            }
            if(get_bit[(metadata->ub[i] >> 2) & 001] == 1) {         //Checking 6th MSB (xxxxx'x'xx)
                count++;
            }
            if(get_bit[(metadata->ub[i] >> 1) & 0b0000001] == 1) {   //Checking 7th MSB (xxxxxx'x'x)
                count++;
            }
            if(get_bit[metadata->ub[i] & 0x01] == 1) {               //Checking LSB (xxxxxxx'x')
                count++;
            }

            i++;
        }

        if(count != metadata->ubn) return -1;
    }

    free(metadata);

    close(workfd);

    return 0;
}

int init_File_dd(const char *fname,int bsize,int bno) {
    int fsize, workfd;
    uint8_t last = 0;
    superblock *metadata = (superblock *)malloc(sizeof(superblock));
    
    workfd = open(fname,O_RDWR|O_CREAT,S_IRWXU|S_IRGRP|S_IROTH);
    if(workfd<0) {
        perror("open() failed");
        return -1;
    }
    
    metadata->n = bno;
    metadata->s = bsize;
    metadata->ubn = 0;
    metadata->fbn = bno;
    memset(metadata->ub,0,(256*sizeof(uint8_t)));

    if(lseek(workfd,0,SEEK_SET) == -1) {         //Creation of superblock
        perror("lseek() failed");
        return -1;
    }
    if(write(workfd,(void *)metadata,sizeof(superblock)) == -1) {
        perror("write() failed");
        return -1;
    }

    fsize = SUPERBLOCK_SIZE + (NUMBER_OF_BLOCKS * BLOCK_SIZE);
    if(lseek(workfd,fsize-1,SEEK_SET) == -1) {   
        perror("lseek() failed");
        return -1;
    }
    if(write(workfd,&last,1) == -1) {
        perror("write() failed");
        return -1;
    }
    
    free(metadata);

    close(workfd);

    return 0;
}

int get_freeblock(const char *fname) {
    if(check_fs(fname) == -1) {
        dprintf(STDERR_FILENO,"There is inconsistency in the file-system.\n");
        exit(EXIT_FAILURE);
    }

    int workfd, freeBlockNo, i=0;
    superblock *metadata = (superblock *)malloc(sizeof(superblock));

    if((workfd = open(fname,O_RDWR)) == -1) {  //error ENOENT
        perror("open() failed");
        return -1;
    }

    decodeSuperblock(workfd,metadata);

    if(metadata->fbn > 0) {
        while(i<256) {
            if(metadata->ub[i] != 0xFF) {   //Enters only when all bits aren't set and starts searching for an unset bit from the most significant one
                if(get_bit[metadata->ub[i] >> 7] == 0) {                       //Checking MSB ('x'xxxxxxx)
                    metadata->fbn --;
                    metadata->ubn ++;
                    metadata->ub[i] ^= 0x80;     //Why XOR? Because there is only 1 Kuldip in this world.

                    freeBlockNo = (8*i + 0);

                    break;
                }
                else if(get_bit[(metadata->ub[i] >> 6) & 0b01] == 0) {         //Checking 2nd MSB (x'x'xxxxxx)
                    metadata->fbn --;
                    metadata->ubn ++;
                    metadata->ub[i] ^= 0x40;

                    freeBlockNo = (8*i + 1);

                    break;
                }
                else if(get_bit[(metadata->ub[i] >> 5) & 0b001] == 0) {        //Checking 3rd MSB (xx'x'xxxxx)
                    metadata->fbn --;
                    metadata->ubn ++;
                    metadata->ub[i] ^= 0x20;

                    freeBlockNo = (8*i + 2);

                    break;
                }
                else if(get_bit[(metadata->ub[i] >> 4) & 0x1] == 0) {          //Checking 4th MSB (xxx'x'xxxx)
                    metadata->fbn --;
                    metadata->ubn ++;
                    metadata->ub[i] ^= 0x10;

                    freeBlockNo = (8*i + 3);

                    break;
                }
                else if(get_bit[(metadata->ub[i] >> 3) & 0b00001] == 0) {      //Checking 5th MSB (xxxx'x'xxx)
                    metadata->fbn --;
                    metadata->ubn ++;
                    metadata->ub[i] ^= 0x08;

                    freeBlockNo = (8*i + 4);

                    break;
                }
                else if(get_bit[(metadata->ub[i] >> 2) & 001] == 0) {          //Checking 6th MSB (xxxxx'x'xx)
                    metadata->fbn --;
                    metadata->ubn ++;
                    metadata->ub[i] ^= 0x04;

                    freeBlockNo = (8*i + 5);

                    break;
                }
                else if(get_bit[(metadata->ub[i] >> 1) & 0b0000001] == 0) {    //Checking 7th MSB (xxxxxx'x'x)
                    metadata->fbn --;
                    metadata->ubn ++;
                    metadata->ub[i] ^= 0x02;

                    freeBlockNo = (8*i + 6);

                    break;
                }
                else if(get_bit[metadata->ub[i] & 0x01] == 0) {                //Checking LSB (xxxxxxx'x')
                    metadata->fbn --;
                    metadata->ubn ++;
                    metadata->ub[i] ^= 0x01;

                    freeBlockNo = (8*i + 7);

                    break;
                }
            }
            else i++;
        }

        if(lseek(workfd,0,SEEK_SET) == -1) {          //Updating the superblock
            perror("lseek() failed");
            return -1;
        }
        if(write(workfd,(void *)metadata,sizeof(superblock)) == -1) {
            perror("write() failed");
            return -1;
        }
        free(metadata);

        if(lseek(workfd,SUPERBLOCK_SIZE + (freeBlockNo * BLOCK_SIZE),SEEK_SET) == -1) {
            perror("lseek() failed");
            return -1;
        }
        for(int j=0;j < BLOCK_SIZE;j++) {
            if(write(workfd,"1",1) == -1) {
                perror("write() failed");
                return -1;
            }
        }

        close(workfd);

        return freeBlockNo;
    }
    else return -1;
}

int free_block(const char *fname,int bno) {
    if(check_fs(fname) == -1) {
        dprintf(STDERR_FILENO,"There is inconsistency in the file-system.\n");
        exit(EXIT_FAILURE);
    }

    int workfd, set_no, set_offset;
    superblock *metadata = (superblock *)malloc(sizeof(superblock));

    if((workfd = open(fname,O_RDWR)) == -1) {  //error ENOENT
        perror("open() failed");
        return -1;
    }

    decodeSuperblock(workfd,metadata);

    set_no = bno/8;
    set_offset = bno%8;

    if(set_offset == 0) {         //Need to unset MSB
        metadata->ub[set_no] &= 0x7F;

        metadata->fbn ++;
        metadata->ubn --;
    }
    else if(set_offset == 1) {    //Need to unset second MSB
        metadata->ub[set_no] &= 0xBF;

        metadata->fbn ++;
        metadata->ubn --;
    }
    else if(set_offset == 2) {    //Need to unset third MSB
        metadata->ub[set_no] &= 0xDF;

        metadata->fbn ++;
        metadata->ubn --;
    }
    else if(set_offset == 3) {    //Need to unset fourth MSB
        metadata->ub[set_no] &= 0xEF;

        metadata->fbn ++;
        metadata->ubn --;
    }
    else if(set_offset == 4) {    //Need to unset fifth MSB
        metadata->ub[set_no] &= 0xF7;

        metadata->fbn ++;
        metadata->ubn --;
    }
    else if(set_offset == 5) {    //Need to unset sixth MSB
        metadata->ub[set_no] &= 0xFB;

        metadata->fbn ++;
        metadata->ubn --;
    }
    else if(set_offset == 6) {    //Need to unset seventh MSB
        metadata->ub[set_no] &= 0xFD;

        metadata->fbn ++;
        metadata->ubn --;
    }
    else {                        //Need to unset LSB
        metadata->ub[set_no] &= 0xFE;

        metadata->fbn ++;
        metadata->ubn --;
    }

    if(lseek(workfd,0,SEEK_SET) == -1) {         //Updating the superblock
        perror("lseek() failed");
        return -1;
    }
    if(write(workfd,(void *)metadata,sizeof(superblock)) == -1) {
        perror("write() failed");
        return -1;
    }
    free(metadata);

    if(lseek(workfd,SUPERBLOCK_SIZE + (bno * BLOCK_SIZE),SEEK_SET) == -1) {
        perror("lseek() failed");
        return -1;
    }
    for(int i=0;i < BLOCK_SIZE;i++) {
        if(write(workfd,"0",1) == -1) {
            perror("write() failed");
            return -1;
        }
    }

    close(workfd);

    return 0;
}