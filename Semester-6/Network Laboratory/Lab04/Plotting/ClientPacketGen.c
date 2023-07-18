/**
 * @file ClientPacketGen.c
 * @author Kuldip Kundu (2020CSB022)
 * @brief Assignment 4 Extension
 * @date 2023-03-19
 */
#include <stdio.h>           //for sprintf() and dprintf()
#include <stdlib.h>          //for exit()
#include <string.h>          //for strlen(), memset() and memcpy()
#include <stdbool.h>

#include <inttypes.h>

#include <sys/time.h>        //for struct timeval, gettimeofday() and timersub()

#include <sys/types.h>       //for open(), lseek(), socket(), inet_ntoa(), sendto() and recvfrom()
#include <sys/stat.h>        //for open()
#include <unistd.h>          //for lseek(), usleep() and close()
#include <fcntl.h>           //for open()
#include <sys/socket.h>      //for socket(), sendto() and recvfrom()
#include <netinet/in.h>      //for inet_ntoa()
#include <arpa/inet.h>       //for inet_ntoa() and inet_pton()

#include <errno.h>           //for perror()

#define MIN_PAYLOAD_SIZE 100      //Minimum size of payload
#define MAX_PAYLOAD_SIZE 1000     //Maximum size of payload
#define MIN_TTL 2                 //Minumum Time-To-Live value
#define MAX_TTL 20                //Maximum Time-To-Live value
#define MIN_ISSUE 1               //Minimum number of packets to be sent
#define MAX_ISSUE 50              //Maximum number of packets to be sent
#define MILLION (int)1E6

void __attribute__((constructor)) setReference();     //Program execution starts with the calling of setReference() function

struct timeval Absolute;          //The reference time-point for this program.

/**
 * @brief This function is called even before the main method.
 * It sets up an absolute time-point which will be used as steady reference in rest of the program.
 * Nothe taht this function does not take any arguments, neither does it return.
 * It only calculate the time(with micro-second level precision) elapsed since the epoch when the program starts executing and stores it in a structure of type struct timeval.
 * Then it creates a delay of about 3 seconds before handing over to main().
 */
void setReference() {
    gettimeofday(&Absolute,NULL);

    printf("Please wait, setting up a reference time-point");
    for(int i=0;i<10;i++) {
        usleep(300000);
        printf(".");
    }
    printf("\nYou are ready to go.\n");
}

/**
 * @brief This is an inline function which checks if a certain value lies in an interval.
 * 
 * @param min The minimum allowed value.
 * @param max The maximum allowed value.
 * @param val The value which is being checked.
 * 
 * @return true if val is between min and max, false otherwise.
 */
static inline bool ifWithin(int min,int max,int val) {
    if((val < min) || (val > max)) return false;
    else return true;
} 

/**
 * @struct datagram
 * 
 * @brief This is the format of packet being sent over the socket.
 */
typedef struct {
    uint16_t sequenceNumber;           //A 2-byte field which identifies the unique sequence number of a packet
    uint32_t timeStamp;                //A 4-byte filed which contains time-stamp of when the packet was first generated (Relative to a pre set time-point)
    uint8_t TTL;                       //An 1-byte filed which contains the Time-To-Live value
    char payload[MAX_PAYLOAD_SIZE];    //An array of bytes containing the actual payload
} datagram;

/*
struct addrinfo {
    int             ai_flags;          // AI_PASSIVE, AI_CANONNAME, etc.
    int             ai_family;         // AF_INET, AF_INET6, AF_UNSPEC
    int             ai_socktype;       // SOCK_STREAM, SOCK_DGRAM
    int             ai_protocol;       // use 0 for "any"
    size_t          ai_addrlen;        //size of ai_addr in bytes
    struct sockaddr *ai_addr;          //struct sockaddr_in or _in6
    char            *ai_canonname;     //full canonical hostname
    struct addrinfo *ai_next;          //linked list, next node
};

struct sockaddr {
    unsigned short sa_family;          //address family, AF_xxx
    char           sa_data[14];        //14 bytes of protocol address
};

struct sockaddr_in {
    short int      sin_family;         //Address family, AF_INET
    unsigned short int sin_port;       //Port number
    struct in_addr sin_addr;           //Internet address
    unsigned char  sin_zero[8];        //Same size as struct sockaddr
};
*/

/*
struct timeval {
    time_t      tv_sec;           //seconds
    suseconds_t tv_usec;          //microseconds
};
*/

/**
 * @brief A custom implementation of the htons() function provided by the kernel.
 * 
 * @param val A 2-byte data
 * 
 * @return Network-order representation of val
 */
uint16_t hostToNetworkShortCustom(uint16_t val) {
    uint8_t *p = (uint8_t *)&val;

    return (uint16_t)((*p << 8) | *(p+1));
}

/**
 * @brief A custom implementation of the ntohs() function provided by the kernel.
 * 
 * @param val A 2-byte data
 * 
 * @return Host-order i.e. little-endian representation of val
 */
uint16_t networkToHostShortCustom(uint16_t val) {
    return ((val << 8) | (val >> 8));
}

/**
 * @brief A custom implementation of the htonl() function provided by the kernel.
 * 
 * @param val A 4-byte data
 * 
 * @return Network-order representation of val
 */
uint32_t hostToNetworkLongCustom(uint32_t val) {
    uint8_t *p = (uint8_t *)&val;

    return (uint32_t)((*p << 24) | (*(p+1) << 16) | (*(p+2) << 8) | *(p+3));
}

/**
 * @brief A custom implementation of the ntohs() function provided by the kernel.
 * 
 * @param val A 4-byte data
 * 
 * @return Host-order i.e. little-endian representation of val
 */
uint32_t networkToHostLongCustom(uint32_t val) {
    return ((val << 24) | ((val & 0xFF00) << 8) | ((val >> 8) & 0xFF00) | (val >> 24));
}

/**
 * @brief This function packs the datagram into a buffer before writing it into the socket.
 * 
 * @param d This is the pointer of type struct datagram which points to the packet to be sent in network
 * @param _buffer This is the buffer where the datagram is put in network-order.
 */
void pack(datagram *d,char *_buffer) {
    uint16_t seq_no = hostToNetworkShortCustom(d->sequenceNumber);
    uint32_t timeStamp = hostToNetworkLongCustom(d->timeStamp);
    uint8_t TTL = d->TTL;

    memcpy(_buffer,&seq_no,sizeof(seq_no));
    memcpy(_buffer + sizeof(seq_no),&timeStamp,sizeof(timeStamp));
    memcpy(_buffer + sizeof(seq_no) + sizeof(timeStamp),&TTL,sizeof(TTL));
    memcpy(_buffer + sizeof(seq_no) + sizeof(timeStamp) + sizeof(TTL),d->payload,sizeof(d->payload));
}

/**
 * @brief This function unpacks the buffer received from the socket and formats(in host-order) it into a structure of type struct datagram.
 * 
 * @param _buffer This is the buffer where the datagram is put in network-order.
 * @param d This is the pointer of type struct datagram which points to the formatted packet.
 */
void unpack(char *_buffer,datagram *d) {
    uint16_t seq_no;
    uint32_t timeStamp;
    uint8_t TTL;

    memcpy(&seq_no,_buffer,sizeof(seq_no));
    memcpy(&timeStamp,_buffer + sizeof(seq_no),sizeof(timeStamp));
    memcpy(&TTL,_buffer + sizeof(seq_no) + sizeof(timeStamp),sizeof(TTL));
    memcpy(d->payload,_buffer + sizeof(seq_no) + sizeof(timeStamp) + sizeof(TTL),sizeof(d->payload));

    d->sequenceNumber = networkToHostShortCustom(seq_no);
    d->timeStamp = networkToHostLongCustom(timeStamp);
    d->TTL = TTL;
}

int main(int argc,char *argv[]) {
    if(argc != 6) {
        fprintf(stderr,"Usage: %s <ServerIP> <ServerPortAddress> <P> <TTL> <NumOfPackets>\n",argv[0]);
        exit(0);
    }
    if(!ifWithin(MIN_PAYLOAD_SIZE,MAX_PAYLOAD_SIZE,atoi(argv[3]))) {
        fprintf(stderr,"Payload size should be within %d and %d bytes.\n",MIN_PAYLOAD_SIZE,MAX_PAYLOAD_SIZE);
        exit(0);
    }
    if((!ifWithin(MIN_TTL,MAX_TTL,atoi(argv[4]))) || (atoi(argv[4])%2 != 0)) {
        fprintf(stderr,"Time-to-Live value should bean even integer within %d and %d bytes.\n",MIN_TTL,MAX_TTL);
        exit(0);
    }
    if(!ifWithin(MIN_ISSUE,MAX_ISSUE,atoi(argv[5]))) {
        fprintf(stderr,"A minimum of %d and a maximum of %d packet(s) have to be sent.\n",MIN_ISSUE,MAX_ISSUE);
        exit(0);
    }

    int client_sockfd, output_fd;
    long total_RTT = 0, avg_RTT = 0;
    char *filename;
    struct sockaddr_in server_addr;
    socklen_t server_addrLength = sizeof(server_addr);

    filename = (char *)malloc(4 + strlen(argv[4]) + 1 + strlen(argv[3]) + 4 + 1);
    sprintf(filename,"TTL-%s_%s.txt",argv[4],argv[3]);

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET,argv[1],&server_addr.sin_addr);

    client_sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(client_sockfd < 0) {
        perror("Error creating socket:");
        exit(1);
    }

    if((output_fd = open(filename,O_RDWR | O_CREAT | O_EXCL,S_IRWXU | S_IRWXG | S_IROTH)) == -1) {      //Opening or creating a file for a particular TTL value and particular payload size
        output_fd = open(filename,O_RDWR);
    }
    free(filename);
    
    for(int i=0;i < atoi(argv[5]);i++) {
        struct timeval actual, relativeSend_time, relativeReceive_time, cumulative_RTT;
        datagram *originalPacket, *recvnFwdPacket;
        char toSendOriginal[MAX_PAYLOAD_SIZE + 7], recvnFwdBuffer[MAX_PAYLOAD_SIZE + 7];
        int bytes_received;

        originalPacket = (datagram *)malloc(sizeof(datagram));
        recvnFwdPacket = (datagram *)malloc(sizeof(datagram));

        //printf("----------------------------------------------------------------------\n");
        //printf("Sending packet with sequence number %d to %s:%d having payload size of %d bytes and Time-To-Live = %d.\n",i,inet_ntoa(server_addr.sin_addr),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));

        originalPacket->sequenceNumber = i;
        originalPacket->TTL = atoi(argv[4]);
        memset(originalPacket->payload,'A',atoi(argv[3]));      //Filled the payload with all 'A'
        gettimeofday(&actual,NULL);
        timersub(&actual,&Absolute,&relativeSend_time);
        originalPacket->timeStamp = (relativeSend_time.tv_sec * MILLION) + relativeSend_time.tv_usec;
        
        pack(originalPacket,toSendOriginal);

        sendto(client_sockfd,toSendOriginal,sizeof(toSendOriginal),0,(const struct sockaddr *)&server_addr,server_addrLength);

        free(originalPacket);

        while(1) {
            if((bytes_received = recvfrom(client_sockfd,recvnFwdBuffer,sizeof(recvnFwdBuffer),0,(struct sockaddr *)&server_addr,&server_addrLength)) == 0) {
                perror("Error receiving packet:");
                exit(1);
            }
            
            unpack(recvnFwdBuffer,recvnFwdPacket);

            if(recvnFwdPacket->TTL != 0) {       //If TTL value is not zero, decrement it by 1 and send the packet again
                recvnFwdPacket->TTL--;

                pack(recvnFwdPacket,recvnFwdBuffer);

                sendto(client_sockfd,recvnFwdBuffer,sizeof(recvnFwdBuffer),0,(const struct sockaddr *)&server_addr,server_addrLength);
            }
            else {                               //If TTL value is zero, calculate the cumulative round-trip delay
                gettimeofday(&actual,NULL);
                timersub(&actual,&Absolute,&relativeReceive_time);

                struct timeval packet_sendTime;
                packet_sendTime.tv_sec = recvnFwdPacket->timeStamp/MILLION;
                packet_sendTime.tv_usec = recvnFwdPacket->timeStamp%MILLION;

                timersub(&relativeReceive_time,&packet_sendTime,&cumulative_RTT);

                //printf("Received final delivery of return-packet with sequence number %hu from %s:%d with Time-To-Live = %u.\n",recvnFwdPacket->sequenceNumber,inet_ntoa(server_addr.sin_addr),atoi(argv[2]),recvnFwdPacket->TTL);
                //printf("\033[0;33mThe 'cumulative' round-trip delay of this packet is %ld seconds and %ld micro-seconds.\033[0m\n",cumulative_RTT.tv_sec,cumulative_RTT.tv_usec);
                //printf("----------------------------------------------------------------------\n");

                total_RTT += (cumulative_RTT.tv_sec * MILLION) + cumulative_RTT.tv_usec;

                break;
            } 
        }

        //lseek(output_fd,0,SEEK_END);                                                                       //Bringing the offset to the end of the file

        dprintf(output_fd,"%s %ld\n",argv[3],((cumulative_RTT.tv_sec * MILLION) + cumulative_RTT.tv_usec));  //Printing the average cumulative-RTT for given payload-size in relevant file

        free(recvnFwdPacket);
    }

    close(output_fd);

    avg_RTT = total_RTT/atoi(argv[5]);
    printf("\033[1;45mAverage of 'cumulative' round-trip delays for %s packets, each with payload-size of %s-bytes, is %ld seconds and %ld micro-seconds.\033[0m\n",argv[5],argv[3],avg_RTT/MILLION,avg_RTT%MILLION);
    
    if(close(client_sockfd) == -1) {
        perror("Close() failed");
        exit(1);
    }
    printf("The client socket has been closed.\n");
}