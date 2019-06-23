#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <zconf.h>
#include <cstring>
#include <arpa/inet.h>

#include "Ping.h"

// Define the Packet Constants
// ping packet size
#define PING_PKT_S 64

// Automatic port number
#define PORT_NO 0

// ping packet structure
struct ping_pkt {
    struct icmphdr hdr;
    char msg[PING_PKT_S - sizeof(struct icmphdr)];
};

// Calculating the Check Sum
unsigned short checksum(void *b, int len) {
    unsigned short *buf = (unsigned short *) b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *) buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

/**
 * Sends ICMP package to a given IP address and checks whether there is a response.
 *
 * @param addr (IP address of target)
 * @param timeout (in milliseconds)
 * @return true if target response to the ICMP package else false
 */
bool sendPing(const char *addr, int timeout) {
    int ttl_val = 64, i, addr_len;

    struct ping_pkt pckt;
    struct sockaddr_in serv_addr;
    struct sockaddr_in r_addr;
    struct timeval tv_out;
    tv_out.tv_sec = 0;
    tv_out.tv_usec = timeout * 1000;

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    // set socket options at ip to TTL and value to 64,
    // change to what you want by setting ttl_val
    if (setsockopt(sockfd, SOL_IP, IP_TTL,
                   &ttl_val, sizeof(ttl_val)) != 0) {
        printf("\nSetting socket options to TTL failed!\n");
        return false;
    }

    // setting timeout of recv setting
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,
               (const char *) &tv_out, sizeof tv_out);

    // filling packet
    bzero(&pckt, sizeof(pckt));

    pckt.hdr.type = ICMP_ECHO;
    pckt.hdr.un.echo.id = getpid();

    for (i = 0; i < sizeof(pckt.msg) - 1; i++)
        pckt.msg[i] = i + '0';

    pckt.msg[i] = 0;
    pckt.hdr.un.echo.sequence = 0;
    pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_NO);

    if (inet_pton(AF_INET, addr, &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported \n");
        return false;
    }

    // send packet
    if (sendto(sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <= 0) {
        printf("Packet Sending Failed!\n");
        return false;
    }

    //receive packet
    addr_len = sizeof(r_addr);
    if (recvfrom(sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr *) &r_addr, (socklen_t *) &addr_len) <= 0) {
        // if no package was received the host isn't up
        return false;
    } else {
        if (pckt.hdr.type == 69 && pckt.hdr.code == 0) {
            // ping was successful
            return true;
        } else {
            return false;
        }
    }
}
