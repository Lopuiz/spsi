/**
 * Proof of concept: Monitoring file using SHA
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <errno.h>
#include <openssl/sha.h>
#include <string.h>
#include <unistd.h>

#include "fim_scheduled.h"


/* Max time allowed for scan interval */
#define MAX_INTERVAL_VALUE  3600

/* Buffer size for the filepath to monitor*/
#define FILENAME_SIZE 256
/* SHA size: SHA1 = 41, SHA224 = 57, SHA256 = 65, SHA384 = 97, SHA512 = 129 */
#define SHA_SIZE    130
/* Buffers size used to read the file content */
#define BUFFER_SIZE 2028


/* Alerts mode */
#define ALERT_SHA_CHANGED   1
#define ALERT_FILE_DEL      2
#define ALERT_USER_CHANGED  3
#define ALERT_GROUP_CHANGED 4


/* Error and info messages */
#define ERROR_STAT_FILE     "Unable to obtain file information. Errno: %d (%s)\n"
#define ERROR_NOT_REG_FILE  "It isn't regular file\n"
#define ERROR_OPEN_FILE     "Failure to open file. Errno: %d (%s)\n"
#define ERROR_INIT_POC      "Can not initialize FIM POC\n"
#define ERROR_GENERATE_SHA  "Unable to generate SHA\n"
#define INFO_SET_FILE       "File '%s' set to monitor\n"
#define INFO_SET_INIT_SHA   "Initial SHA: %s\n"
#define INFO_START_FIM      "Start monitoring\n"


/* Time to sleep between scans */
short fim_interval;

/* Information about file watched */
char file_name[FILENAME_SIZE];
char file_sha[SHA_SIZE];
struct stat file_stat;

/* Obtain the initial file status */
static bool fim_set_file_status();
/* Caculate SHA1 */
static void fim_generate_sha(char sha[]);
/* Report modifications in the file */
static void fim_generate_alert(int type, char more_info[]);


void fim_monitoring() {

    if(fim_set_file_status() == false) {
        printf(ERROR_INIT_POC);
        return;
    }

    printf(INFO_START_FIM);

    while (true) {

        /* Sleep until next scan */
        sleep(fim_interval);

        /* Check file attributes */
        struct stat statbuf;
        if (stat(file_name, &statbuf) < 0) {
            fim_generate_alert(ALERT_FILE_DEL, file_name);
            return;
        }

        if(statbuf.st_uid != file_stat.st_uid) {
            struct passwd *new_user = getpwuid(statbuf.st_uid);
            if(new_user == NULL) {
                fim_generate_alert(ALERT_USER_CHANGED, "unknown");
            } else {
                fim_generate_alert(ALERT_USER_CHANGED, new_user->pw_name);
            }
            
        }

        if(statbuf.st_gid != file_stat.st_gid) {
            struct group *new_group = getgrgid(statbuf.st_gid);
            if (new_group == NULL) {
                fim_generate_alert(ALERT_USER_CHANGED, "unknown");
            } else {
                fim_generate_alert(ALERT_GROUP_CHANGED, new_group->gr_name);
            }
        }

        file_stat = statbuf;

        /* Check SHA */
        char sha[SHA_SIZE] = "\0";
        fim_generate_sha(sha);

        if(strcmp(sha, file_sha) != 0) {
            strcpy(file_sha, sha);
            fim_generate_alert(ALERT_SHA_CHANGED, file_sha);
        }
    }
}

bool fim_set_configuration(short interval) {

    if (interval < 0 || interval > MAX_INTERVAL_VALUE) {
        return false;
    }

    fim_interval = interval;
    return true;
}

bool fim_set_file_watched(const char *file) {

    size_t size = strlen(file);

    if (file != NULL && size < FILENAME_MAX) {
        strcpy(file_name, file);
        printf(INFO_SET_FILE, file_name);
        return true;
    }

    return false;
}

static bool fim_set_file_status() {

    if (stat(file_name, &file_stat) < 0) {
        printf(ERROR_STAT_FILE, errno, strerror(errno));
        return false;
    }

    if (S_ISREG(file_stat.st_mode) == 0) {
        printf(ERROR_NOT_REG_FILE);
        return false;
    }

    fim_generate_sha(file_sha);
    printf(INFO_SET_INIT_SHA, file_sha);

    return true;
}

static void fim_generate_sha(char sha[]) {

    FILE *fp;
    if (fp = fopen(file_name, "rb"), !fp) {
        printf(ERROR_OPEN_FILE, errno, strerror(errno));
        return;
    }

    SHA_CTX context;
    char buffer[BUFFER_SIZE];
    size_t size_read;

    SHA1_Init(&context);

    while (size_read = fread(buffer, 1, BUFFER_SIZE - 1, fp), size_read > 0) {
        buffer[size_read] = '\0';
        SHA1_Update(&context, buffer, size_read);
    }

    fclose(fp);
    
    unsigned char md[SHA_DIGEST_LENGTH];
    SHA1_Final(&(md[0]), &context);

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        snprintf(sha, 3, "%02x", md[i]);
        sha += 2;
    }
}

static void fim_generate_alert(int type, char more_info[]) {

    switch (type) {
        case ALERT_SHA_CHANGED:
            printf("\n*************************\n");
            printf("File content changed\n");
            printf("New SHA is '%s'\n", more_info);
            break;
    
        case ALERT_FILE_DEL:
            printf("\n*************************\n");
            printf("File '%s' deleted\n", more_info);
            break;
        
        case ALERT_USER_CHANGED:
            printf("\n*************************\n");
            printf("User changed\n");
            printf("New user is '%s'\n", more_info);
            break;
        
        case ALERT_GROUP_CHANGED:
            printf("\n*************************\n");
            printf("Group changed\n");
            printf("New group is '%s'\n", more_info);
            break;
    }
}
