#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "irc_server.h"

#define BACKLOG 5

int main(int argc, char** argv) {

    if(argc != 3) {
        fprintf(stderr, "Usage: ./server <IP> <port>\n");
        return 1;
    }

    int status, s_fd, bind_res, listen_res, n_fd;
    socklen_t addr_size;
    struct sockaddr_storage their_addr;
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; //IPv4 mode
    hints.ai_socktype = SOCK_STREAM; //TCP

    if((status = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 2;
    }

    s_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if(s_fd == -1) {
        perror("socket error");
    }

    bind_res = bind(s_fd, res->ai_addr, res->ai_addrlen);

    if(bind_res == -1) {
        perror("bind error");
    }

    listen_res = listen(s_fd, BACKLOG);

    if(listen_res == -1) {
        perror("listen error");
    }

    addr_size = sizeof(their_addr);
    n_fd = accept(s_fd, (struct sockaddr *)&their_addr, &addr_size);

    if(n_fd == -1) {
        perror("accept error");
    }

    char msg[25];
    int len, bytes_sent;

    printf("Enter a message to send from server: ");
    scanf("%s", msg);

    len = strlen(msg);
    bytes_sent = send(n_fd, msg, len, 0);

    printf("Sent %d bytes!\n", bytes_sent);

    if(bytes_sent == -1) {
        perror("send error");
    }

    close(s_fd);
    close(n_fd);
    freeaddrinfo(res);

    return 0;
}

