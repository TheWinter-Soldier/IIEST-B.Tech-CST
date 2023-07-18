/**
 * @file ServerPacketFwd.c
 * @author Kuldip Kundu (2020CSB022)
 * @brief Assignment 4 Extension
 * @date 2023-03-19
*/
#include <stdio.h>
#include <stdlib.h>          //for exit()
#include <string.h>          //for memset() and memcpy()

#include <inttypes.h>        

#include <sys/types.h>       //for socket(), bind(), sendto() and recvfrom()
#include <unistd.h>          //for close()
#include <sys/socket.h>      //for socket(), bind(), sendto() and recvfrom()    
#include <netinet/in.h>      //for the relevant structures

#include <signal.h>          //for signal()

#include <errno.h>           //for perror()

#define MAX_PAYLOAD_SIZE 1000

int server_sockfd;                //The file-descriptor of the socket used by server

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

struct in_addr {
    uint32_t s_addr;                   //that's a 32-bit int (4 bytes)
};
*/

typedef void (*sighandler_t)(int);
/**
 * @brief A custom signal-handler designed to close the socket and terminate the program when ctrl-C[^C] is pressed.
 * 
 * @param signum SIGINT will be passed when it is installed
*/
void socketCloser(int signum) {
    close(server_sockfd);

    printf("The socket has been closed gracefully.\n");
    exit(0);
}

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
    if(argc != 2) {
        printf("Usage: %s <ServerPortAddress>\n",argv[0]);
        exit(1);
    }
    if((atoi(argv[1]) < 1024) || (atoi(argv[1]) > 65535)) {
        printf("Port number should be between 1024 and 65535.");
        exit(0);
    }

    signal(SIGINT,socketCloser);       //Installation of the custom signal-handler

    struct sockaddr_in server_addr;

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    server_sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(server_sockfd < 0) {
        perror("Error creating socket:");
        exit(1);
    }

    if(bind(server_sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        perror("Error binding socket:");
        exit(1);
    }

    printf("Server listening at port %d .....\n",atoi(argv[1]));

    while(1) {
        struct sockaddr_in client_addr;
        socklen_t client_addrLength = sizeof(client_addr);
        char buffer[MAX_PAYLOAD_SIZE + 7];
        int bytes_received;
        datagram *packet = (datagram *)malloc(sizeof(datagram));

        if((bytes_received = recvfrom(server_sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client_addr,&client_addrLength)) == -1) {
            perror("Error recieving packet:");
            exit(1);
        }
        
        unpack(buffer,packet);

        if(packet->TTL >= 0) {
            char toSendBack[MAX_PAYLOAD_SIZE + 7];

            if(packet->TTL != 0) packet->TTL--;  //Decrease TTL only if it is greater than 0

            pack(packet,toSendBack);           

            sendto(server_sockfd,toSendBack,sizeof(toSendBack),0,(const struct sockaddr *)&client_addr,client_addrLength);
        }
    }

    return 0;
}