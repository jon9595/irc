#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "irc_client.h"

int user_account_history_add_user(char*);

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

    user_account_history_add_user(username);

    return 0;
}

int user_account_history_add_user(char username[11]) {
    // Get current datetime to store with username
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s, sizeof(s), "%c", tm);

    // Open file and append user
    FILE* fp = fopen("../logs/user_account_history.txt", "a");
    if (!fp) {
        return 1;
    } else {
        fprintf(fp, "%s\n%s\n\n", username, s);
    }

    return 0;
}
