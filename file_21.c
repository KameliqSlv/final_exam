#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc < 3){
        perror("Invalid arguments");
        exit(-1);
    }

    char *file = argv[1];
    int N = atoi(argv[2]);

    FILE *f = fopen(file,"r");
    if(!f){
        perror("Filed to open");
        exit(-1);
    }

    for(int i = 0; i < N; i++){
        uint64_t num = (uint64_t)rand();
        fwrite(&num , sizeof(uint64_t), 1, f);   
    }

    fclose(f);
    return 0;
}
