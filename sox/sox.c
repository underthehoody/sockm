#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(){

    struct addrinfo example_addrinfo;
    struct sockaddr servaddr;
    struct sockaddr_in servaddr_in;
    struct sockaddr_in *sockaddr_in_ptr;
    struct sockaddr_in6 ip6_sockaddr;

    //struct addrinfo serv_addrinfo;

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    printf("%lu", sizeof(servaddr));
    printf("%lu", sizeof(servaddr_in));

    //connect(sock_fd, const struct sockaddr *addr,  len)


    return 0;
}
