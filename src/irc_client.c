#include <stdio.h>
#include <stdlib.h>

#include "irc_client.h"

int main(int argc, char** argv) {
    char username[11];

    if (argc != 1 || !argv) {
        printf("Invalid command line arguments.\n");
        return 1;
    }

    printf("Enter a username (10 characters or less)\n");
    printf("Username: ");
    scanf("%10s", username);
    printf("Welcome, %s!\n", username);

    return 0;
}
