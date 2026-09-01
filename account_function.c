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

int log_in(int id,int passwd,account *user) {
    FILE *fp=fopen(DB_FILE,"r");
    if (fp==NULL) {
        perror("fopen error \n");
        return 0;
    }

    account tmp;

    while (fscanf(fp,"%d:%19[^:]:%d:%f",&tmp.id,tmp.name,&tmp.password,&tmp.balance)==4) {
        if ((passwd==tmp.password)&&(id==tmp.id)) {
            printf("Login successful! Welcome, %s.\n",tmp.name);
            *user=tmp;
            fclose(fp);
            return 1;
        }

    }
    fclose(fp);
    printf("Invalid ID or password!\n");

    return 0;
}

void deposit(account* user,float money) {
    user->balance+=money;
    update_balance(user);

}

int withdraw(account * user,float money) {
    if (user->balance<money){
        perror("insufficient funds");
        return 0;
    }
    user->balance-=money;
    update_balance(user);
    return 1;
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
        if (current.id==user->id) {
            fprintf(tmp,"%d:%s:%d:%.2f\n",current.id,current.name,current.password,user->balance);
        }
        else {
            fprintf(tmp,"%d:%s:%d:%.2f\n",current.id,current.name,current.password,current.balance);


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

void transfer_money(account *sen,int rec,float money) {
    if (sen->id==rec) {
        printf("You cannot transfer your money to your own account!!! \n");
        return;
    }

    account receiver;


    if (find_addres(rec,&receiver)==0) {
        perror("Cannot found receiver account!! \n");
        return;
    }

    if(withdraw(sen,money)) {
        deposit(&receiver,money);
        printf("Transfer completed succesfully, your current balance is %.2f",sen->balance);

    }
}
