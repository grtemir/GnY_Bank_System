#include "headers.h"
#include <stdio.h>
#include <stdlib.h>

#define DB_FILE "accounts.txt"

void deposit(account* acc,float money) {
    acc->balance+=money;
}

void withdraw(account * acc,float money) {
    if (acc->balance<money){
    perror("insufficient funds");
    }
    acc->balance-=money;
}

void balance(account* acc) {
    printf("Current balance is %.2f \n",acc->balance);
}

account* add_account() {
    account *acc=malloc(sizeof(account));

    printf("Enter an account id: \n");
    if (scanf("%d",&(acc->id))!=1) {
           perror("Scanf error ");
           exit(1);
    }

    printf("Enter a name : \n");
    if (scanf("%s",acc->name)!=1) {
            perror("Scanf error ");
            exit(1);}

    printf("Enter balance: \n");
    if (scanf("%f",&(acc->balance))!=1) {
            perror("Scanf error ");
            exit(1);}

        return acc;
    }

void add_accounts(account *db[],int nm) {
    FILE *fp=fopen(DB_FILE,"a");
    if (fp==NULL) {
        perror("fopen error");
        return;
    }
    int i;
    for (i=0;i<nm;i++) {
        db[i]=add_account();
        fprintf(fp,"%d:%s:%d:%f\n",db[i]->id,db[i]->name,db[i]->password,db[i]->balance);
    }
    if (fclose(fp)==EOF) {
        perror("Fclose error");
    }

}

void bank_screen() {
    printf("-----------------------------------------------\n");
    printf("-----------Welcome to GnY bank system----------\n");
    printf("---------------Please choose...----------------\n");
    printf("-----------------------------------------------\n");
    printf("Press 1 to sign in...\n");
    printf("Press 2 to sign up...\n");
    printf("Press 3 to add many account ...\n");
    printf("Press 4 to load many account from file...\n");
    printf("Press 0 to exit...\n");
    printf("-----------------------------------------------\n");
    printf("-----------------------------------------------\n");
}

int log_in(int id,int passwd) {
    file *fp=fopen(DB_FILE,"w+");


}

void add_accounts_from_file(FILE *src) {
    FILE *dst=fopen(DB_FILE,"a");
    if (dst==NULL) {
        perror("fopen error \n");
        return;
    }
    char line_s[64];
    while (fgets(line_s,sizeof(line_s),src)) {
        fputs(line_s,dst);
    }
    if (fclose(dst)==EOF) {
        perror("fclose error \n");
        return;
    };


    fclose(src);
}





