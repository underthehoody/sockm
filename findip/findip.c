#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>


int main(int argc, char *argv[]){

    struct addrinfo hints, *res;
    char addr[INET_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(argv[1], NULL, &hints, &res) != 0){
        return 2;

    }
    struct sockaddr_in *ip4_address = (struct sockaddr_in *)res->ai_addr;

    inet_ntop(AF_INET, &ip4_address->sin_addr, addr, sizeof addr);

    printf("%s\n", addr);
    return 0;
}
