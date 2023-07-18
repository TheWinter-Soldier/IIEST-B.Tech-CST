/**
 * @file myfind.c
 * @author Kuldip Kundu (2020CSB022)
 * @brief Assignment 8 Question 1
 * An attempt to recreate the 'find' command-line utility of linux with reduced and modified features
 * 
 * @date 2023-02-21
 */
#include <stdio.h>      //for sprintf()
#include <stdlib.h>     //for atoi()
#include <stdbool.h>
#include <string.h>     //for memset(), strcmp(), strcpy(), strstr() and strtok_r()

#include <sys/types.h>  //for opendir(), closedir() and lstat()
#include <unistd.h>     //for lstat() and getcwd()
#include <sys/stat.h>   //for lstat()
#include <dirent.h>     //for opendir(), readdir() and closedir()

#include <time.h>       //for clock_gettime() and struct timespec

#include <errno.h>      //for perror()

#define minimumOf(a,b) ((a<b) ? a : b)

#define MAX_LEAFandINTERMEDIATE_NODE 2048             //This is the maximum number of Intermediate-nodes and leafs inside a given directory
#define MAX_CONTENT MAX_LEAFandINTERMEDIATE_NODE
#define MAX_STAR_COUNT 9                              //Maximum number of stars allowed in the target string
#define OLDEST_MODIFICATION 100                       //This is the limit upto how many days checking will be done when only "mtime +n" is provided
#define MIN_TO_SEC 60
#define HOUR_TO_SEC (60*MIN_TO_SEC)
#define DAY_TO_SEC (24*HOUR_TO_SEC)

/**
 * @struct formatInfo
 * @brief Contains information about the naming format of a file or directory to be searched.
 */
struct formatInfo {
    int subStringCount;                //Contains the number of sub-strings that need to be matched
    char *toMatch[MAX_STAR_COUNT+1];   //Contains the sub-strings sequentially
    bool starAtEnd;                    //A boolean variable that remains true if there is a star at the end
};

/**
 * @struct options
 * @brief Holds values and information about what options have been given in the command line.
 */
struct options {
    char *startingDir;            //Contains the absolute path of the starting directory
    int duration[2];              //duration[0] stores the 'greater than' and duration[1] stores the 'lesser than' values of parameters passed to '-mtime'
    int perm;                     //The permission value
    char *target;                 //Target string that is to be matched
    bool recursionEnabled;        //This boolean field denotes if recursive search is enabled [Set to true by default]
    bool if_mtime;                //This boolean filed is true if 'mtime' type of option is present
    bool if_perm;                 //This boolean field is true if 'perm' option is present
    bool if_search;               //This boolean field is true if 'name' option is present
};

/*
struct dirent {
    ino_t          d_ino;         //Inode number
    off_t          d_off;         //Not an offset
    unsigned short d_reclen;      //Length of this record 
    unsigned char  d_type;        //Type of file; not supported by all file-system types 
    char           d_name[256];   //Null-terminated filename 
};

struct stat {
    dev_t     st_dev;             //ID of device containing file
    ino_t     st_ino;             //Inode number
    mode_t    st_mode;            //File type and mode
    nlink_t   st_nlink;           //Number of hard links
    uid_t     st_uid;             //User ID of owner
    gid_t     st_gid;             //Group ID of owner
    dev_t     st_rdev;            //Device ID (if special file)
    off_t     st_size;            //Total size, in bytes
    blksize_t st_blksize;         //Block size for filesystem I/O
    blkcnt_t  st_blocks;          //Number of 512B blocks allocated

                                  //Since Linux 2.6, the kernel supports nanosecond precision for the following timestamp fields. For the details before Linux 2.6, see NOTES.

    struct timespec st_atim;      //Time of earliest access
    struct timespec st_mtim;      //Time of earliest modification
    struct timespec st_ctim;      //Time of earliest status change

    #define st_atime st_atim.tv_sec    //Backward compatibility
    #define st_mtime st_mtim.tv_sec
    #define st_ctime st_ctim.tv_sec
};

struct timespec {
    time_t  tv_sec;               //Seconds
    long    tv_nsec;              //Nanoseconds
};
*/

/**
 * @brief This is a lower-level function called by the checkModTime() function.
 * It helps in comparing if a file's last modification time is within a specified interval or not.
 * It has the precision of nanoseconds.
 * 
 * @param[in] mtim This is the structure which contains the last modification time of the file
 * @param[in] _before This structure contains the upper-bound of the specified time-interval
 * @param[in] _after This structure contains the lowe-bound of the specified time-interval
 * 
 * @return true if mtim lies within _after and _before and false if mtim does not lie ithin _after and _before
 */
bool checkIfWithin(struct timespec mtim,struct timespec _before,struct timespec _after) {
    if((_after.tv_sec < mtim.tv_sec) && (mtim.tv_sec < _before.tv_sec)) {
        return true;
    }
    else if((_after.tv_sec == mtim.tv_sec) && (mtim.tv_sec < _before.tv_sec)) {
        if(_after.tv_nsec < mtim.tv_nsec) {
            return true;
        }
        else return false;
    }
    else if((_after.tv_sec < mtim.tv_sec) && (mtim.tv_sec == _before.tv_sec)) {
        if(mtim.tv_nsec < _before.tv_nsec) {
            return true;
        }
        else return false;
    }
    
    return false;
}

/**
 * @brief This is a lower-level function called by search() function.
 * It helps to break the given search format into separate tokens.
 * 
 * @param[in,out] buffer This is the structure
 * @param[in] _targetFormat 
 * @param[in] delim 
 */
void stringFormatDisassembler(struct formatInfo *buffer,char *_targetFormat,char *delim){
    char *token, *saveptr, *temp = NULL;
    
    temp = (char *)malloc(strlen(_targetFormat)+1);
    strcpy(temp,_targetFormat);

    memset(buffer->toMatch,'\0',sizeof(buffer->toMatch));
    
    int i=0, j=0;
    while(1) {
        if(j==0) {
            token = strtok_r(_targetFormat,delim,&saveptr);
        }
        else {
            token = strtok_r(NULL,delim,&saveptr);
        }

        if(token == NULL) break;
        buffer->toMatch[i] = (char *)malloc(strlen(token));
        sprintf(buffer->toMatch[i++],"%s",token);

        j++;
    }

    buffer->subStringCount = i;

    if((temp[strlen(temp)-1]) == '*') {
        buffer->starAtEnd = true;
    }
}

void scourDirectory(char *dirName,char *pathArray[],bool recurFlg) {
    DIR* dir;
    struct dirent *dirEntry;
    struct stat statbuf;
    char name[1000], defaultParent[1000], defaultSame[1000];
    static int i = -1;

    dir = opendir(dirName);
    if(dir==0) {
        perror("opendir() failed");
        exit(EXIT_FAILURE);
    }

    sprintf(defaultParent,"%s/..",dirName);
    sprintf(defaultSame,"%s/.",dirName);

    while((dirEntry=readdir(dir)) != 0) {
        sprintf(name,"%s/%s",dirName,dirEntry->d_name);  

        if((strcmp(name,defaultParent) != 0) && (strcmp(name,defaultSame) != 0)) {
            pathArray[++i] = (char *)malloc(strlen(name)+1);
            strcpy(pathArray[i],name);

            lstat(pathArray[i],&statbuf);

            //Recursively call scourDirectory() if it is a directory
            if(S_ISDIR(statbuf.st_mode)) {
                if(recurFlg == true) {
                    scourDirectory(pathArray[i],pathArray,true);
                }
            }
        }
    }

    closedir(dir);
}

void search(char *pathArray[],char *targetFormat) {
    if((targetFormat[0] == '*') && (targetFormat[1] != '.')) {
        printf("'*' is not accepted at the begining.\n");
        exit(2);
    }

    char *temp[MAX_CONTENT];
    int j=0;

    memset(temp,'\0',sizeof(temp));
    
    for(int i=0;pathArray[i] != 0;i++) {
        temp[i] = pathArray[i];
        pathArray[i] = NULL;
    }
    
    if(strstr(targetFormat,"*") == NULL) {                                     //If there is no star in the target
        char *toMatch = NULL;
        toMatch = (char *)malloc(strlen(targetFormat)+2);       //'size' parameter passed to malloc is strlen(targetFormat)+2 because we are passing 1 character more than what targetFormat contains
        sprintf(toMatch,"/%s",targetFormat);

        for(int i=0;temp[i] != 0;i++) {
            if(strstr(temp[i],toMatch) != NULL) {
                if(strcmp(strstr(temp[i],toMatch),toMatch) == 0) {
                    pathArray[j++] = temp[i];
                }
            }
        }
    }
    else {
        if((targetFormat[0] == '*') && (targetFormat[1] == '.')) {             //If "*.ext" is the target
            char *toMatch = NULL;
            toMatch = (char *)malloc(strlen(targetFormat));     //'size' parameter passed to malloc is strlen(targetFormat) because we are passing 1 character less than what targetFormat contains
            strcpy(toMatch,&targetFormat[1]);

            for(int i=0;temp[i] != 0;i++) {
                if(strstr(temp[i],toMatch) != NULL) {
                    if(strcmp(strstr(temp[i],toMatch),toMatch) == 0) {
                        pathArray[j++] = temp[i];
                    }
                }
            }
        }
        else {                                                                 //If random format is the target
            struct formatInfo f1;
            
            f1.subStringCount = 0;
            memset(f1.toMatch,'\0',sizeof(f1.toMatch));
            f1.starAtEnd = false;

            stringFormatDisassembler(&f1,targetFormat,"*");

            char *remaining[f1.subStringCount];
            memset(remaining,'\0',sizeof(remaining));
            
            for(int i = 0;temp[i] != 0;i++) {                             //For every pathname in the temp array
                int k=0;
                while(k<f1.subStringCount) {                         //As long as there are tokens to search for
                    if(strstr(temp[i],f1.toMatch[k]) == NULL) { 
                        break;              //Break as sonon as there is a mismatched token
                    }
                    
                    if(k != 0) {            //If it's not the first token, check for it in the remaining string
                        if(strstr(remaining[k-1],f1.toMatch[k]) == NULL) {
                            break;
                        }
                        else {
                            remaining[k] = strstr(remaining[k-1],f1.toMatch[k]);
                        }
                    }
                    else {                  //Check for the first token and put the rest in remaining
                        remaining[k] = strstr(temp[i],f1.toMatch[k]);
                    }

                    if(k == f1.subStringCount - 1) {       //When all tokens have been serched for and are found to be present sequentially
                        if(f1.starAtEnd) {       //If there is a star at end, simply update pathArray
                            pathArray[j++] = temp[i];
                        }
                        else {                   //If star is not there at end, update pathArray only when the last remaining string matches the last token
                            if(strstr(temp[i],f1.toMatch[k]) != NULL) {
                                if(strcmp(strstr(temp[i],f1.toMatch[k]),f1.toMatch[k]) == 0) {
                                    pathArray[j++] = temp[i];
                                }
                            }
                        }
                    }

                    k++;
                }
            }
        }
    }
}

void checkPermission(char *pathArray[],int perm) {
    char *temp[MAX_CONTENT];
    struct stat statbuf;
    int j=0;

    memset(temp,'\0',sizeof(temp));
    
    for(int i=0;pathArray[i] != 0;i++) {
        temp[i] = pathArray[i];
        pathArray[i] = NULL;
    }

    for(int i=0;temp[i] != 0;i++) {
        lstat(temp[i],&statbuf);

        //Check the type of resource and update array if permission matches
        if(S_ISDIR(statbuf.st_mode)) {
            continue;
        }
        else {
            if((statbuf.st_mode & 0777) == perm) {
                pathArray[j++] = temp[i];
            }  
        }
    }
}

void checkModTime(char *pathArray[],struct timespec before,struct timespec after) {
    char *temp[MAX_CONTENT];
    struct stat statbuf;
    int j=0;

    memset(temp,'\0',sizeof(temp));
    
    for(int i=0;pathArray[i] != 0;i++) {
        temp[i] = pathArray[i];
        pathArray[i] = NULL;
    }

    for(int i=0;temp[i] != 0;i++) {
        lstat(temp[i],&statbuf);

        //Put it in array if modified within interval
        if(checkIfWithin(statbuf.st_mtim,before,after)) {
            pathArray[j++] = temp[i];
        }
    }
}

void parseCMDline(struct options *_opt,int argumentCount,char *arguments[]) {
    if(arguments[1][0] == '-') {            //If user doesn't provide a starting directory
        _opt->startingDir = (char *)malloc(128*sizeof(char));
        getcwd(_opt->startingDir,128*sizeof(char));
    }
    else if(arguments[1][0] == '/') {       //If user provides full path of starting directory
        _opt->startingDir = (char *)malloc(strlen(arguments[1])+1);
        strcpy(_opt->startingDir,arguments[1]);
    }
    else {                                  //If user provides the relative path of starting directory
        char *currentDirectory = NULL;

        currentDirectory = (char *)malloc(128*sizeof(char));
        getcwd(currentDirectory,128*sizeof(char));

        _opt->startingDir = (char *)malloc((strlen(currentDirectory) + 1 + strlen(arguments[1]))+1);    //We are appending two strings and also a '/', that justifies the size argument in malloc()
        sprintf(_opt->startingDir,"%s/%s",currentDirectory,arguments[1]);
    }

    for(int i=1;i<minimumOf(3,argumentCount);i++) {                            //Checking for the global-option i.e. to search the directories recursively or not
        char *lookingFor = NULL;
        lookingFor = (char *)malloc(strlen(arguments[i]));    
        strcpy(lookingFor,&arguments[i][1]);

        if(strcmp(lookingFor,"no-recurse") == 0) {
            _opt->recursionEnabled = false;

            break;
        }
    }

    for(int i=1;i<argumentCount;i++) {
        if(arguments[i][0] == '-') {
            char *lookingFor = NULL;
            lookingFor = (char *)malloc(strlen(arguments[i]));    
            strcpy(lookingFor,&arguments[i][1]);

            if(strcmp(lookingFor,"name") == 0) {      //Checking for '-name' that implements searching for specific names
                _opt->if_search = true;

                _opt->target = (char *)malloc(strlen(arguments[i+1])+1);
                strcpy(_opt->target,arguments[i+1]);
            }

            if(strcmp(lookingFor,"perm") == 0) {      //Checking for '-perm'
                _opt->if_perm = true;

                int a = atoi(arguments[i+1]), count=0, result=0;

                while(a) {
                    int x = a%10;
                    a /= 10;
                    
                    if(count == 0) result = x + result;
                    else if(count == 1) result = x*8 + result;
                    else if(count == 2) result = x*64 + result;

                    count++;
                }

                _opt->perm = result;
            }
            
            //All checks below are for '-mtime' type of arguments
            if(strcmp(lookingFor,"msec") == 0) {
                _opt->if_mtime = true;

                if(arguments[i+1][0] == '+') {
                    char *t = NULL;
                    t = (char *)malloc(strlen(arguments[i+1]));    
                    strcpy(t,&arguments[i+1][1]);

                    _opt->duration[0] = atoi(t);
                }
                else if(arguments[i+1][0] == '-') {
                    char *t = NULL;
                    t = (char *)malloc(strlen(arguments[i+1]));    
                    strcpy(t,&arguments[i+1][1]);

                    _opt->duration[1] = atoi(t);
                }
                else {
                    _opt->duration[0] = atoi(arguments[i+1]);
                    _opt->duration[1] = atoi(arguments[i+1]);
                }
            }

            if(strcmp(lookingFor,"mmin") == 0) {
                _opt->if_mtime = true;

                if(arguments[i+1][0] == '+') {
                    char *t = NULL;
                    t = (char *)malloc(strlen(arguments[i+1]));    
                    strcpy(t,&arguments[i+1][1]);

                    _opt->duration[0] = atoi(t)*MIN_TO_SEC;
                }
                else if(arguments[i+1][0] == '-') {
                    char *t = NULL;
                    t = (char *)malloc(strlen(arguments[i+1]));    
                    strcpy(t,&arguments[i+1][1]);

                    _opt->duration[1] = atoi(t)*MIN_TO_SEC;
                }
                else {
                    _opt->duration[0] = atoi(arguments[i+1])*MIN_TO_SEC;
                    _opt->duration[1] = atoi(arguments[i+1])*MIN_TO_SEC;
                }
            }

            if(strcmp(lookingFor,"mhour") == 0) {
                _opt->if_mtime = true;

                if(arguments[i+1][0] == '+') {
                    char *t = NULL;
                    t = (char *)malloc(strlen(arguments[i+1]));    
                    strcpy(t,&arguments[i+1][1]);

                    _opt->duration[0] = atoi(t)*HOUR_TO_SEC;
                }
                else if(arguments[i+1][0] == '-') {
                    char *t = NULL;
                    t = (char *)malloc(strlen(arguments[i+1]));    
                    strcpy(t,&arguments[i+1][1]);

                    _opt->duration[1] = atoi(t)*HOUR_TO_SEC;
                }
                else {
                    _opt->duration[0] = atoi(arguments[i+1])*HOUR_TO_SEC;
                    _opt->duration[1] = atoi(arguments[i+1])*HOUR_TO_SEC;
                }
            }

            if(strcmp(lookingFor,"mday") == 0) {
                _opt->if_mtime = true;

                if(arguments[i+1][0] == '+') {
                    char *t = NULL;
                    t = (char *)malloc(strlen(arguments[i+1]));    
                    strcpy(t,&arguments[i+1][1]);

                    _opt->duration[0] = atoi(t)*DAY_TO_SEC;
                }
                else if(arguments[i+1][0] == '-') {
                    char *t = NULL;
                    t = (char *)malloc(strlen(arguments[i+1]));    
                    strcpy(t,&arguments[i+1][1]);

                    _opt->duration[1] = atoi(t)*DAY_TO_SEC;
                }
                else {
                    _opt->duration[0] = atoi(arguments[i+1])*DAY_TO_SEC;
                    _opt->duration[1] = atoi(arguments[i+1])*DAY_TO_SEC;
                }
            }
        }
    }
}

int main(int argc,char *argv[]) {
    if(argc<2) {
        printf("Give at least 1 command-line argument.");
        exit(1);
    }

    struct options *opt = (struct options *)malloc(sizeof(struct options));
    struct stat statbuf;
    char *dirContent[MAX_CONTENT];

    opt->startingDir = NULL;
    opt->duration[0] = 0;
    opt->duration[1] = DAY_TO_SEC*OLDEST_MODIFICATION;
    opt->perm = 0000;
    opt->target = NULL;
    opt->if_perm = false;
    opt->if_mtime = false;
    opt->if_search = false;
    opt->recursionEnabled = true;
    parseCMDline(opt,argc,argv);

    memset(dirContent,'\0',sizeof(dirContent));
    if(opt->recursionEnabled) {
        scourDirectory(opt->startingDir,dirContent,true);
    }
    else {
        scourDirectory(opt->startingDir,dirContent,false);
    }

    if(opt->if_search) {
        search(dirContent,opt->target);
    }

    if(opt->if_perm) {
        checkPermission(dirContent,opt->perm);
    }

    if(opt->if_mtime) {
        struct timespec cur_time = {0,0}, earliestModTime = {0,0}, mostRecentModTime = {0,0};
        if(clock_gettime(CLOCK_REALTIME,&cur_time) == -1) {
            perror("clock_gettime() failed");
            exit(EXIT_FAILURE);
        }

        mostRecentModTime.tv_nsec = cur_time.tv_nsec;
        mostRecentModTime.tv_sec = cur_time.tv_sec - (time_t)opt->duration[0];
        earliestModTime.tv_nsec = cur_time.tv_nsec;
        earliestModTime.tv_sec = cur_time.tv_sec - (time_t)opt->duration[1];

        checkModTime(dirContent,mostRecentModTime,earliestModTime);
    }

    for(int i=0;dirContent[i] != 0;i++) {
        lstat(dirContent[i],&statbuf);

        //Check the type of resource and print accordingly
        if(S_ISDIR(statbuf.st_mode)) {
            printf("\033[1;32m");
            printf("dir \t");
            printf("%s\n",dirContent[i]);
            printf("\033[0m");
        }
        else {
            if(S_ISREG(statbuf.st_mode)) {
                printf("file\t");
            }  
            else if(S_ISLNK(statbuf.st_mode)) {
                printf("lnk \t");
            }
            else if(S_ISCHR(statbuf.st_mode)) {
                printf("chrD\t");
            }
            else if(S_ISBLK(statbuf.st_mode)) {
                printf("blkD\t");
            }
            else if(S_ISFIFO(statbuf.st_mode)) {
                printf("FIFO\t");
            }
            else if(S_ISSOCK(statbuf.st_mode)) {
                printf("sock\t");
            }
            printf("%s\n",dirContent[i]);
        }
    }

    return 0;
}