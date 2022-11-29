#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int search(char* target, char* source) {
    size_t source_length = strlen(source);
    size_t target_length = strlen(target);
    // printf("target: %s %lu; source: %s %lu\n",target, target_length, source, source_length);
    for (int i = 0; i < source_length; i++) {
        char* substr = (char*)malloc(target_length + 1);
        substr = strncpy(substr, source + i, target_length);
        // printf("debug: %s\n",substr);
        if (strcmp(target, substr) == 0) {
            printf("%s", source);
            break;
        }

    }
    return -1;
}

void _search_in_file(char* target, FILE* fd) {
    char* lineptr = NULL;
    size_t size = 0;
    while ( -1 != (getline(&lineptr, &size, fd))) {
        search(target, lineptr);
    }
}

void search_in_file(char* target, char* filename) {
    FILE* fd = fopen(filename, "r");
    if (fd == NULL) {
        printf("wgrep: cannot open file\n");
        exit(1);
    } else {
        _search_in_file(target, fd);
        int result = fclose(fd);
        if (EOF == result) {
            printf("failed to close the file\n");
        }
    }
}




int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    } else if (argc == 2) {
        _search_in_file(argv[1],stdin);
    }
    char* target = argv[1];
    for (int i = 2; i < argc; i++){
        search_in_file(target, argv[i]);
    }
    return 0;
}