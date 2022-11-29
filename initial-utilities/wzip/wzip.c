#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void compress_string(char* target) {
    int cnt = 0;
    char ch = EOF;
    int size = strlen(target);

    for (int i = 0; i < size; i++){
        if (EOF == ch || target[i] == ch) {
            ch = target[i];
            cnt++;
        } else{
            fwrite(&cnt, sizeof(int), 1, stdout);
            fwrite(&ch, sizeof(char), 1, stdout);
            ch = target[i];
            cnt = 1;
        }
    }
    // 以二进制形式写入int和char
    // 便于在shell中进行管道处理
    fwrite(&cnt, sizeof(int), 1, stdout);
    fwrite(&ch, sizeof(char), 1, stdout);
}

char* read_file(FILE* fd) {
    if (NULL == fd) {
        printf("meaningless stream\n");
        exit(1);
    }
    // 是一个超大的文件，需要开的buffer很大， 在这里尝试了挺多次
    char* buf = (char*)malloc(sizeof(char) * BUFSIZ * BUFSIZ);

    // fread 读取整个文件
    // fwrite 以二进制格式写入字符
    fread(buf,sizeof(char),BUFSIZ * BUFSIZ,fd);
    return buf;
}


int main(int argc, char* argv[]) {
    FILE* fd = NULL;
    if (argc < 2){
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    } else {
        char* buf = (char*)malloc(sizeof(char) * BUFSIZ * BUFSIZ);
        for (int i = 1; i < argc; i++) {
            fd = fopen(argv[i], "r");
            char* data = read_file(fd);
            strcat(buf, data);
            fclose(fd);
            free(data);
        }
        compress_string(buf);
    }
    return 0;
}