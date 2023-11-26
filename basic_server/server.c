#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(void){

    struct addrinfo hints, *res;
    int addrinfo_status, bind_status;
    struct sockaddr_storage rem_addr;
    unsigned rem_size = sizeof(rem_addr);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((addrinfo_status = getaddrinfo(NULL, "30321", &hints, &res)) != 0){
        printf("addrinfo failed");
        return 1;
    };

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if ((bind_status = bind(sockfd, res->ai_addr, res->ai_addrlen)) != 0){
        printf("bind failed");
        return 1;
    };

    listen(sockfd, 20);

    int remfd = accept(sockfd, (struct sockaddr *)&rem_addr, &rem_size);

    char *msg = "Hello_Friend\n";

    send(remfd, msg, 14, 0);
    for (;;){
        int recv_len = 13;
        char recv_msg[recv_len];
        bzero(recv_msg, recv_len);
        recv(remfd, recv_msg, recv_len, 0);

        printf("%s", recv_msg);
    }
    close(sockfd);

    return 0;
}

