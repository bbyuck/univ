#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";
    unsigned long host_addr;

    unsigned long conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE){
        printf("Error occured!\n");
    }
    else {
        printf("Network ordered integer addr: %#lx\n", conv_addr);
        host_addr = ntohl(conv_addr);
        printf("Host ordered integer addr: %#lx\n", host_addr);    
    }

    conv_addr = inet_addr(addr2);

    if (conv_addr == INADDR_NONE) {
        printf("Error occured!\n");
    }
    else
    {
        printf("Network ordered integer addr: %#lx\n", conv_addr);
    }

    return 0;
}