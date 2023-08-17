/*
    Направете програма, в която се подават като аргументи от 
    командния ред списък от имената на бинарни файлове, в които 
    са записани цели неотрицателни 64 битови числа. Целта на 
    програмата е да изведе сумата на цифрите на числата от 
    всеки файл. Сумирането трябва да стане с цифрите от 
    десетичния запис на числата от всеки файл. Сумирането да
     се извърши като за всеки файл се създаде отделен процес. 
     Накрая родителския процес да изведе общата сума в stdout. 

*/

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>

int total_sum = 0;

// int dig_sum(uint64_t num){
//     int sum = 0;
//     while(num>0){
//         sum += num % 10;
//         num /= 10;
//     }
//     return sum;

// }

void* thread_fun(void* args) {
    //printf("%p\n", args);
    //printf("%p\n", (thread_args_t*)args);
    int *sum = malloc(sizeof(int));
    *sum = ((int*)args) + ((int*)args);
    return sum;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Invalid arguments");
        exit (-1);
    }   

    pthread_t th1;

     if(pthread_create(&th1, NULL, dig_sum, argc) == -1) {
        perror("Could not create thread");
        exit(1);
    }


    for(int i = 1 ; i< argc ; i++){
        FILE *f = fopen(argv[i], "r");

       //for(int j = argc + i; j < argc -1 ; j++){
            pid_t pid = fork();
            if(pid == -1){
                perror("fork failed");
                exit(-1);

            } else if(pid == 0){
                FILE * f = fopen(argv[i], "r");
                if(!f){
                    perror("file failed");
                    exit(-1);
                }

                uint64_t number;
                while(fread(&number, sizeof(uint64_t), 1, f)){
                    total_sum += dig_sum(number);
                }

                fclose(f);
               printf("%d\n", total_sum);

            } else {
                int wstatus;
                pid_t child_pid = wait(&wstatus);
                total_sum += dig_sum(wstatus);
                return 0;
            } 


        //}

    }

    write(STDERR_FILENO, &total_sum, sizeof((total_sum)));

    //printf("Sum: %d\n", total_sum);
}