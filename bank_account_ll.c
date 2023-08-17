#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <threads.h>

#define ITEM_COUNT 5

typedef struct bank_account{
    uint16_t number;
    char name[100];
    double amount;
    char currency[4];
} bank_account;

typedef struct Node{
    bank_account data;
    struct Node *next;
} Node;

int gen_number(uint16_t n){
    return n++;
}

void gen_string(char *str){
    int n = 2 + rand() % (6 - 2);

    for (size_t i = 0 ; i < n; i++) {
        int curIndex = rand() % 52;
        if(curIndex <= 25){
            str[i] = curIndex + 'A';
        } else{
            str[i] = curIndex - 26 + 'a';
        }
    }
}

void init_list(Node **head, bank_account account){
    Node *newNode = malloc(sizeof(Node));
    if(newNode == NULL){
        perror("Cold not malloc\n");
        exit(-1);
    }

    newNode->data = account;
    newNode->next = (*head);
    (*head) = newNode;
}

char *current[] = {"A", "B", "C", "D"};

bank_account* create(){
    bank_account *account = malloc(sizeof(bank_account)*ITEM_COUNT);

    if(account==NULL){
        perror("Cold not malloc\n");
        exit(-1);
    }

    for(int i=0; i < ITEM_COUNT; i++){
        gen_number(account[i].number);

        gen_string(account[i].name);
        //100 000.00лв;
        //100 000
        account[i].amount = (rand() % 10000000)/100.;

        strcpy(account[i].currency, current[rand() % 4]);
    }

    return account;
}

double totalBalance(Node *head){
    int total;
    if (!head) {
        perror("ERROR:");
        exit(-1);
    }
    while (head){
        total += head->data.amount;
        head = head->next;
    }
    return total;

}



Node * maxBalance(Node* head){
    Node *max_node = head;
    int max = head->data.amount;
    head = head->next;
    if(!head){
        perror("ERROR: maxBalance");
        exit(-1);
    }
    
    while(head){
        if(head->data.amount > max){
            max = head->data.amount;
            max_node = head;
        }
    }   

    return head;
}


void print_account(bank_account *account){
    if(account == NULL){
        perror("Empty list");
        exit(-1);
    }

    for (size_t i = 0; i < ITEM_COUNT; i++)
    {
        printf("id_num: %3d \t Name: %10s \t amount: %.2lf \t currency: %3s \n", account[i].number, account[i].name, account[i].amount, account[i].currency);
    }
    printf("\n");


}


int main(){
    Node *head= NULL;
    bank_account *account =  create();

    for(int i=0; i < ITEM_COUNT; i++){
        init_list(&head, account[i]);
    }

    print_account(account);


    printf("Total balance %.2lf \n" , totalBalance(head) );

    Node *max_balance = maxBalance(head);
    //printf("Max Balance : %.2lf\n", max_balance->data.amount);

}