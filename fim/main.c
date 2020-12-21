/**
 * Proof of concept: Monitoring file using SHA
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fim_scheduled.h"

void help() {
    printf("Proof of concept: Obtain SHA of a content file\n");
    printf("Options allowed:\n");
    printf("   -f <file_path>       File to calculate SHA\n");
    printf("   -i <scan_interval>   Time to sleep between scans\n");
}

int main (int argc, char **argv) {

    int option;
    const char *file = NULL;
    long interval = 30;
    char *end;

    while (option = getopt(argc, argv, "f:i:"), option != -1) {
        switch (option) {

            case 'f':
                file = optarg;
                break;

            case 'i':
                interval = strtol(optarg, &end, 10);
                if(*end != '\0') {
                    printf("Invalid interval value\n");
                    return -1;
                }
                break;

            default:
                help();
                break;
        }
    }

    if (file == NULL) {
        help();
        return -1;
    }

    if (fim_set_file_watched(file) == false) {
        printf("Unable to set file to watch\n");
        return -1;
    }

    if (fim_set_configuration(interval) == false) {
        printf("Unable to set scan interval\n");
        return -1;
    }

    fim_monitoring();

    return 0;
}
