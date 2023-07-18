/**
 * @file Interface.h
 * @author Kuldip Kundu (2020CSB022)
 * @brief Header file that contains relevant function definations, macros and other useful things for implementing a file-system.
 * @date 23-03-18
*/
#ifndef __INTERFACE__
#define __INTERFACE__

#include <inttypes.h>

#define SUPERBLOCK_SIZE 1024      //Size of the file-system descriptor in bytes
#define BLOCK_SIZE 4096           //Size of each block in bytes
#define NUMBER_OF_BLOCKS 2048     //Total number of blocks in the system

/**
 * @struct superblock
 * @brief This is a structure that contains information about the file system.
 */
typedef struct {
    int n;              //Total number of blocks
    int s;              //Size of each block
    int ubn;            //Number of used blocks
    int fbn;            //Number of free blocks
    uint8_t ub[256];    //Bitmap whose corresponding bit represent if the block is free or not
} superblock;

/**
 * @brief This function checks the sanctity of the file-system.
 * It reads the first 1024 bytes and does tests to ensure that the file-system is consistent.
 * 
 * @param fname The name of the file on which tests need to be run
 * 
 * @return 0 when the file-system is consistent, -1 otherwise.
 */
int check_fs(const char *fname);

/**
 * @brief This function creates a file with name 'fname' in the present working directory.
 * The file will contain 'bno' number of blocks each of size 'bsize' bytes.
 * Additionally, there are 1024 bytes in the begining which store information about the file-system.
 * 
 * @param fname Name of the file
 * @param bsize Size of each block
 * @param bno Total number of blocks in the file
 * 
 * @return 0 when successful, -1 otherwise.
 */
int init_File_dd(const char *fname,int bsize,int bno);

/**
 * @brief This function searches for the first free block in the bitmap of file with name 'fname'.
 * On finding a free block, it sets the corresponding bit in the bitmap, updates ubn and fbn accordingly.
 * It also fills the block with all 1's.
 * @see struct superblock
 * 
 * @param fname Name of the file for which a free block has to be found
 * 
 * @return Block-number of the free block if such is found, -1 otherwise.
 */
int get_freeblock(const char *fname);

/**
 * @brief This function frees the block with block-number 'bno' of the file 'fname'.
 * It updates ubn, fbn and also unsets the particular bit in the bitmap.
 * Then it fills the block with all 0's.
 * @see struct superblock
 * 
 * @param fname Name of the file whose block has to be freed
 * @param bno The block-number of the block which has to be freed
 * 
 * @return 0 if the required block could be freed, -1 otherwise.
*/
int free_block(const char *fname,int bno);

#endif   //__INTERFACE__