#include <stdlib.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
int main(void){

    struct addrinfo hints, *res;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(NULL, "30321", &hints, &res) < 0)){
            printf("getaddrinfo failed\n");
            return 1;
            }
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if ((status = bind(sockfd, res->ai_addr, res->ai_addrlen)) < 0){
        printf("bind failed\n");
        return 1;
    }

    struct sockaddr rem_addr;
    unsigned rem_size = sizeof(rem_addr);
    listen(sockfd, 20);
    int remfd = accept(sockfd, &rem_addr, &rem_size);

    int c;
    char *web_page;
    unsigned web_page_offset = 0;
    unsigned buffer_size = 4;
    web_page = malloc(buffer_size);
    FILE *index_html;
    index_html = fopen("../../../web/wow/index.html", "r");

    while(c = fgetc(index_html), c != EOF){
        if (web_page_offset == buffer_size -1){
            buffer_size *= 2;
            char *new_buffer = realloc(web_page, buffer_size);
            if (new_buffer == NULL){
                printf("realloc failed");
                free(web_page);
                return 1;
            }
            web_page = new_buffer;

        }
        web_page[web_page_offset++] = c;
    }

    send(remfd, web_page, web_page_offset, 0);

    free(web_page);





    return 0;
}
