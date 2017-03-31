
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "enigma.h"
#include "util_debug.h"

char command [BUFFER_LENGTH_COMMAND] = "start";
char *pCommand = command;

char argument [BUFFER_LENGTH_ARGUMENT] = "none";
char *pArgument = argument;

char message [BUFFER_LENGTH_MESSAGE] = ".";
char *pMessage = message;

int main (void) {
    #ifdef DEBUG
        print_debug_indent();
        printf("Program starting...\n");
    #endif

    printf("Welcome to Enigma!\n"); // welcome message

    // apply default settings
    apply_settings_default();

    while (true) {

        printf("Engima $ "); // command prompt

        // get input
        if (fgets(pCommand, BUFFER_LENGTH_COMMAND, stdin) == NULL) {
            printf("Failed check with (fgets(pCommand, %i, stdin) == NULL)\n", BUFFER_LENGTH_COMMAND);
            printf("Exiting...\n");
            exit(1);
        };
        /* Remove trailing newline, if there. */
        if ((strlen(pCommand) > 0) && (pCommand[strlen(pCommand) - 1] == '\n')) {
            pCommand[strlen(pCommand) - 1] = '\0';
        }

        printf("COMMAND ENTERED: \"%s\"\n", pCommand);

        if (strcmp(command, "msg") == STRCMP_EQUAL || strcmp(command, "message") == STRCMP_EQUAL) {
            printf("(max. message size is 1 KiB)\n");
            printf("Enter message: "); // argument prompt

            // get input
            if (fgets(pMessage, BUFFER_LENGTH_MESSAGE, stdin) == NULL) {
                printf("Failed check with (fgets(pArgument, %i, stdin) == NULL)\n", BUFFER_LENGTH_MESSAGE);
                printf("Exiting...\n");
                exit(1);
            };
            /* Remove trailing newline, if there. */
            if ((strlen(pArgument) > 0) && (pArgument[strlen(pArgument) - 1] == '\n')) {
                pArgument[strlen (pArgument) - 1] = '\0';
            }

            printf("MSG: %s\n", pMessage);
            printf("CMSG: %s\n", process_message(pMessage));
        }
        else if (strcmp(command, "config") == STRCMP_EQUAL) {
            printf("View config? (y/n): "); // argument prompt

            // get input
            if (fgets(pArgument, BUFFER_LENGTH_ARGUMENT, stdin) == NULL) {
                printf("Failed check with (fgets(pArgument, %i, stdin) == NULL)\n", BUFFER_LENGTH_ARGUMENT);
                printf("Exiting...\n");
                exit(1);
            };
            /* Remove trailing newline, if there. */
            if ((strlen(pArgument) > 0) && (pArgument[strlen(pArgument) - 1] == '\n')) {
                pArgument[strlen(pArgument) - 1] = '\0';
            }

            if (strcmp(pArgument, "y") == STRCMP_EQUAL || strcmp(pArgument, "Y") == STRCMP_EQUAL) {
                print_config();
            }
        }
        else if (strcmp(command, "help") == STRCMP_EQUAL) {
            printf("Commands: help, msg/message, exit/quit\n");
        }
        else if (strcmp(command, "exit") == STRCMP_EQUAL) {
            break; // exit program loop
        }
        else if (strcmp(command, "quit") == STRCMP_EQUAL) {
            break; // exit program loop
        }
        else {
            printf("Command not recognized.\n");
        }
    }

    #ifdef DEBUG
        print_debug_indent();
        printf("Program finished without errors.\n");
        print_debug_indent();
        printf("Shutting down...\n");
    #endif

    return 0;
}