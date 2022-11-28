#include<stdio.h>
#include<stdlib.h>
#define BUFFER 1024
void _read_file(FILE* file){
    char buffer[BUFFER];
    while (fgets(buffer, BUFFER, file) != NULL) {
        printf("%s",buffer);
    }
}

void read_file(char* filename) {
    FILE* fd = fopen(filename,"rwx");
    if (fd == NULL) {
        printf("wcat: cannot open file\n");
        exit(1);
    } else {
        _read_file(fd);
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        read_file(argv[i]);
    }
    return 0;
}