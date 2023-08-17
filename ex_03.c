#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

int N , M;
typedef struct arg {
    int n;
    int m;
    int *arr;
} arg;


void *average(void *args)
{
    int *numbers = (int *)args;
    double *sum = malloc(sizeof(double));
    *sum = 0;
    for (int i = 0; i < M; i++)
    {
        *sum += numbers[i];
    }
    *sum /= (double)M;
    return sum;
}

int main(){
    
    scanf("%d %d", &N, &M);

    int arr[N][M]; // n > col m -> row

    pthread_t *thread = malloc(sizeof(pthread_t ) * N);
    int *num;
   
    char filename[100];
    scanf("%s", filename);

    for(int i = 0; i < N; i++)
    {
        num = malloc(sizeof(int)* N);
        for(int j = 0; j < M; j++){
            scanf("%d", &arr[i][j]);
        }
        
        if(pthread_create(thread, NULL, average, &num[i])){
            return 1;
        }
    }

    for (int i = 0 ; i < N; i++) {

        if(phread_join(thread[i], (void*)num)){
            perror("ERROR: join");
            exit(-1);
        }
    }
    // for (int i = 0; i < N; i++){
    //     //ROW[i][j] = rand() % 10;
    //     for (int j = 0; j < M; j++){
    //        scanf("%d", &arr[i][j]);
    //     }
    // }

    // char filename[100];
    // scanf("%s", filename);

    // pthread_t pht[N];
    // arg *args = malloc(sizeof(arg));
    // for


     for (int i = 0; i < N; i++){
        //ROW[i][j] = rand() % 10;
        for (int j = 0; j < M; j++){
           printf("%d ", arr[i][j]);
        }
    }

    sum(arr);
}