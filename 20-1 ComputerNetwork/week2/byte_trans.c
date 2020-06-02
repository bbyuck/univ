#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char* argv[]) {
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr;
    unsigned long net_addr = 0x78563412;

    net_port = htons(host_port);
    host_addr = ntohl(net_addr);

    printf("Host orderd port: %#x \n", host_port);
    printf("Network ordered prt: %#x \n", net_port);
    printf("Host ordered address: %#lx \n", host_addr);
    printf("Network ordered address: %#lx \n", net_addr);

    return 0;
}