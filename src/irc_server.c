#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "irc_server.h"

#define BACKLOG 5

int main(int argc, char** argv) {

    if(argc != 2) {
        fprintf(stderr, "Usage: ./server <port>\n");
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
    hints.ai_flags = AI_PASSIVE;

    if((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
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

    char *test = "Test message!";
    int len, bytes_sent;

    len = strlen(test);
    bytes_sent = send(s_fd, test, len, 0);

    if(bytes_sent == -1) {
        perror("send error");
    }

    close(s_fd);
    freeaddrinfo(res);

    return 0;
}

