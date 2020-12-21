/**
 * Obtain SHA of a content file
 *
 * Compilation: gcc calculate_sha.c -o calculate_sha -lssl -lcrypto
 */

#include <stdbool.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <openssl/sha.h>


/* Buffer size for the filepath to monitor */
#define FILENAME_SIZE 256
/* Buffers size used to read the file content */
#define BUFFER_SIZE 2028
/* SHA size */
#define SHA_SIZE    130


/* Info and error messages */
#define INFO_SHA            "SHA: %s\n"
#define ERROR_OPEN_FILE     "Failure to open file. Errno: %d (%s)\n"
#define ERROR_MEM           "Unable to allocate memory\n"
#define ERROR_SHA_VAL       "Invalid sha algorithm\n"


/* Functions to calculate SHA */
static void generate_sha1(FILE *fp, unsigned char md[]);
static void generate_sha224(FILE *fp, unsigned char md[]);
static void generate_sha256(FILE *fp, unsigned char md[]);
static void generate_sha384(FILE *fp, unsigned char md[]);
static void generate_sha512(FILE *fp, unsigned char md[]);


/* Help binary message */
void help() {
    printf("Proof of concept: Obtain SHA of a content file\n");
    printf("Options allowed:\n");
    printf("   -f <file_path>       File to calculate SHA\n");
    printf("   -a <sha_algorithm>   SHA to calculate\n");
}

int main (int argc, char **argv) {

    int option;
    const char *file = NULL;
    const char *sha_alg = NULL;

    while (option = getopt(argc, argv, "f:a:"), option != -1) {
        switch (option) {
            case 'f':
                file = optarg;
                break;
            case 'a':
                sha_alg = optarg;
                break;
            default:
                help();
                return -1;
        }
    }

    if (file == NULL || sha_alg == NULL) {
        help();
        return -1;
    }

    void (*generate_sha)(FILE *fp, unsigned char md[]);
    int md_size;

    if (strcasecmp(sha_alg, "sha1") == 0) {
        generate_sha = generate_sha1;
        md_size = SHA_DIGEST_LENGTH;
    } else if (strcasecmp(sha_alg, "sha224") == 0) {
        generate_sha = generate_sha224;
        md_size = SHA256_DIGEST_LENGTH;
    } else if (strcasecmp(sha_alg, "sha256") == 0) {
        generate_sha = generate_sha256;
        md_size = SHA256_DIGEST_LENGTH;
    } else if (strcasecmp(sha_alg, "sha384") == 0) {
        generate_sha = generate_sha384;
        md_size = SHA512_DIGEST_LENGTH;
    } else if (strcasecmp(sha_alg, "sha512") == 0) {
        generate_sha = generate_sha512;
        md_size = SHA512_DIGEST_LENGTH;
    } else {
        printf(ERROR_SHA_VAL);
        return -1;
    }

    FILE *fp;
    if (fp = fopen(file, "rb"), !fp) {
        printf(ERROR_OPEN_FILE, errno, strerror(errno));
        return -1;
    }

    unsigned char md[md_size];
    generate_sha(fp, md);

    fclose(fp);

    char *sha;
    if(sha = calloc(sizeof(char), 130), sha == NULL) {
        printf(ERROR_MEM);
        return -1;
    }

    char *aux = sha;
    for (int i = 0; i < md_size; i++) {
        snprintf(aux, 3, "%02x", md[i]);
        aux += 2;
    }

    if (strcmp(sha, "")) {
        printf(INFO_SHA, sha);
    }

    free(sha);
    sha = NULL;

    return 0;
}


static void generate_sha1(FILE *fp, unsigned char md[]) {
    SHA_CTX context;
    char buffer[BUFFER_SIZE];
    size_t size_read;

    SHA1_Init(&context);

    while(size_read = fread(buffer, 1, BUFFER_SIZE-1, fp), size_read > 0) {
        buffer[size_read] = '\0';
        SHA1_Update(&context, buffer, size_read);
    }

    SHA1_Final(&(md[0]), &context);
}

static void generate_sha224(FILE *fp, unsigned char md[]) {
    SHA256_CTX context;
    char buffer[BUFFER_SIZE];
    size_t size_read;

    SHA224_Init(&context);

    while(size_read = fread(buffer, 1, BUFFER_SIZE-1, fp), size_read > 0) {
        buffer[size_read] = '\0';
        SHA224_Update(&context, buffer, size_read);
    }

    SHA224_Final(&(md[0]), &context);
}

static void generate_sha256(FILE *fp, unsigned char md[]) {
    SHA256_CTX context;
    char buffer[BUFFER_SIZE];
    size_t size_read;

    SHA256_Init(&context);

    while(size_read = fread(buffer, 1, BUFFER_SIZE-1, fp), size_read > 0) {
        buffer[size_read] = '\0';
        SHA256_Update(&context, buffer, size_read);
    }

    SHA256_Final(&(md[0]), &context);
}

static void generate_sha384(FILE *fp, unsigned char md[]) {
    SHA512_CTX context;
    char buffer[BUFFER_SIZE];
    size_t size_read;

    SHA384_Init(&context);

    while(size_read = fread(buffer, 1, BUFFER_SIZE-1, fp), size_read > 0) {
        buffer[size_read] = '\0';
        SHA384_Update(&context, buffer, size_read);
    }

    SHA384_Final(&(md[0]), &context);
}

static void generate_sha512(FILE *fp, unsigned char md[]) {
    SHA512_CTX context;
    char buffer[BUFFER_SIZE];
    size_t size_read;

    SHA512_Init(&context);

    while(size_read = fread(buffer, 1, BUFFER_SIZE-1, fp), size_read > 0) {
        buffer[size_read] = '\0';
        SHA512_Update(&context, buffer, size_read);
    }

    SHA512_Final(&(md[0]), &context);
}
