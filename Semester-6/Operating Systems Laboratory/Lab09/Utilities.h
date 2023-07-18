/**
 * @file Utilities.h
 * @author Kuldip Kundu (2020CSB022)
 * @brief Header file that contains defination of functions used by the methods that manipulate the file-system.
 * @date 23-03-18
*/
#ifndef __UTILITIES__
#define __UTILITIES__

#include "Interface.h"

/**
 * @brief This function reads the first 1024 bytes from the abstraction and stores the information about the file-system in a structure.
 * 
 * @param _fd File-descriptor whose information has to be extracted
 * @param sb Pointer to a structure of type superblock where the extracted information will be stored
 */
void decodeSuperblock(int _fd,superblock *sb);

#endif   //__UTILITIES__