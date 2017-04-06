#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "irc_client.h"

void get_username(char* username) {
    printf("Enter a username (10 characters or less)\n");
    printf("Username: ");
    scanf("%10s", username);
    printf("Welcome, %s!\n", username);
}

int main(int argc, char** argv) {
    char username[11];
    int status, s_fd;
    struct addrinfo hints, *res;

    if (argc != 3 || !argv) {
        printf("Invalid command line arguments.\n");
        return 1;
    }

    get_username(username);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if((status = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    s_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if(s_fd == -1) {
        perror("socket error");
        return 3;
    }

    char buf[25];
    int bytes, con_res;

    con_res = connect(s_fd, res->ai_addr, res->ai_addrlen);

    if(con_res == -1) {
        perror("connect error");
        return 4;
    }

    bytes = recv(s_fd, buf, 25, 0);

    close(s_fd);

    printf("%d bytes from server: %s\n", bytes, buf);

    if(bytes == -1) {
        perror("recv error");
    }

    freeaddrinfo(res);

    return 0;
}
