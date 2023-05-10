#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILENAME_LEN 256
#define MAX_BUFFER_SIZE 4096

void print_usage() {
    printf("Usage: WordCount [-c | -w] [input_file_name]\n");
}

int count_characters(FILE* fp) {
    int count = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        count++;
    }

    return count;
}

int count_words(FILE* fp) {
    int count = 0;
    int ch;
    int is_word = 0; // Boolean flag indicating whether we are currently inside a word

    while ((ch = fgetc(fp)) != EOF) {
        if (isalnum(ch)) { // Check if the character is alphanumeric
            if (!is_word) { // If we were not previously inside a word, increment the word count
                count++;
            }
            is_word = 1;
        } else {
            is_word = 0;
        }
    }

    return count;
}

int main(int argc, char* argv[]) {
    char filename[MAX_FILENAME_LEN];
    char mode[3];
    FILE* fp;
    int count;

    // Parse command-line arguments
    if (argc != 3) {
        print_usage();
        return 1;
    }
    strcpy(mode, argv[1]);
    strcpy(filename, argv[2]);

    // Open input file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return 1;
    }

    // Perform counting based on mode
    if (strcmp(mode, "-c") == 0) {
        count = count_characters(fp);
        printf("Character count: %d\n", count);
    } else if (strcmp(mode, "-w") == 0) {
        count = count_words(fp);
        printf("Word count: %d\n", count);
    } else {
        print_usage();
        return 1;
    }

    // Close input file
    fclose(fp);

    return 0;
}

