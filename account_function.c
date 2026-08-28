#include "headers.h"
#include <stdio.h>
#include <stdlib.h>

void sign_up() {
    account *acc=malloc(sizeof(account));

    printf("Enter an account id: \n");
    if (scanf("%d",&(acc->id))!=1) {
        perror("Scanf error");
        exit(1);
    }

    printf("Enter account password: \n");
    if (scanf("%d",&(acc->password))!=1) {
        perror("Scanf error");
        exit(1);}

    printf("Enter a name : \n");
    if (scanf("%s",acc->name)!=1) {
        perror("Scanf error");
        exit(1);}

    acc->balance=0.0;


    FILE *fp=fopen(DB_FILE,"a");
    if (fp==NULL) {
        perror("fopen error");
        exit(1);}

    fprintf(fp,"%d:%s:%d:%.2f\n",acc->id,acc->name,acc->password,acc->balance);

    if (fclose(fp)==EOF) {
        perror("Fclose error");
    }
    free(acc);

};


void deposit(account* user,float money) {
    user->balance+=money;
    update_balance(user);

}

void withdraw(account * user,float money) {
    if (user->balance<money){
        perror("insufficient funds");
        return;
    }
    user->balance-=money;
    update_balance(user);
}

void balance(account *user) {
    printf("Current balance is %.2f \n",user->balance);
}

void update_balance(account *user) {
    FILE *src=fopen(DB_FILE,"r");
    if (src==NULL) {
        perror("fopen error ");
        return;
    } FILE *tmp=fopen(TEMP_FILE,"w");
    if (tmp==NULL) {
        perror("fopen error");
        fclose(tmp);
        return;
    }
    account current;
    while (fscanf(src,"%d:%19[^:]:%d:%f\n",&current.id,current.name,&current.password,&current.balance)==4) {
        if (current.id=user->id) {
            fprintf(tmp,"%d:%s:%d:%2f\n",current.id,current.name,current.password,user->balance);
        }
        else {
            fprintf(tmp,"%d:%s:%d:%2f\n",current.id,current.name,current.password,current.balance);


        }
    }
    if (fclose(src)==EOF) {
        perror("Fclose error");
        return;
    }
    if (fclose(tmp)==EOF) {
        perror("Fclose error");
        return;
    }
    remove(DB_FILE);

    rename(TEMP_FILE,DB_FILE);

}
