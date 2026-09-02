#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void sign_up() {
    account *acc=malloc(sizeof(account));

    printf("Enter an account id: \n");
    if (scanf("%d",&(acc->id))!=1) {
        perror("Scanf error");
        exit(1);
    }

    printf("Enter account password: \n");
    if (scanf("%s",(acc->password))!=1) {
        perror("Scanf error");
        exit(1);}

    printf("Enter a name : \n");
    if (scanf("%s",acc->name)!=1) {
        perror("Scanf error");
        exit(1);}

    acc->balance=0;


    FILE *fp=fopen(DB_FILE,"a");
    if (fp==NULL) {
        perror("fopen error");
        exit(1);}

    char hashed_psw[HASH_LEN];
    hash_sha256(acc->password,hashed_psw);

    strcpy(acc->password,hashed_psw);

    fprintf(fp,"%d:%s:%s:%.2f\n",acc->id,acc->name,hashed_psw,acc->balance);

    log_transaction(acc->id,"SIGN_UP",0);

    if (fclose(fp)==EOF) {
        perror("Fclose error");
    }
    free(acc);

};

int log_in(int id,char passwd[64],account *user) {
    FILE *fp=fopen(DB_FILE,"r");
    if (fp==NULL) {
        perror("fopen error \n");
        return 0;
    }

    account tmp;

    char hashed_psw[HASH_LEN];
    hash_sha256(passwd,hashed_psw);

    while (fscanf(fp,"%d:%19[^:]:%64[^:]:%f",&tmp.id,tmp.name,tmp.password,&tmp.balance)==4) {
        if ((strcmp(hashed_psw,tmp.password)==0)&&(id==tmp.id)) {
            printf("Login successful! Welcome, %s.\n",tmp.name);
            *user=tmp;
            fclose(fp);
            log_transaction(user->id,"LOGIN_SUCCESS",0);
            return 1;
        }

    }
    log_transaction(user->id,"LOGIN_FAILED",0);
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
        printf("insufficient funds");
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
        fclose(src);
        return;
    }
    account current;
    while (fscanf(src,"%d:%19[^:]:%s:%f\n",&current.id,current.name,current.password,&current.balance)==4) {
        if (current.id==user->id) {
            fprintf(tmp,"%d:%s:%s:%.2f\n",current.id,current.name,current.password,user->balance);
        }
        else {
            fprintf(tmp,"%d:%s:%s:%.2f\n",current.id,current.name,current.password,current.balance);


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


    if (find_address(rec,&receiver)==0) {
        printf("Cannot found receiver account!! \n");
        return;
    }


    if(withdraw(sen,money)) {
        deposit(&receiver,money);
        printf("Transfer completed succesfully, your current balance is %.2f",sen->balance);
        log_transaction(sen->id,"TRANSFER_SEND",money);
        log_transaction(receiver.id,"TRANSFER_RECEIVED",money);

    }
}

void log_transaction(int acc_id,char *type,float money){
    FILE *fp=fopen(LOG_FILE,"a");
    if (fp==NULL) {
        perror("fopen error ");
        return;
    }

    time_t raw_time;
    time(&raw_time);

    struct tm *time_info;
    time_info = localtime(&raw_time);

    char time[30];

    strftime(time,sizeof(time),"%Y-%m-%d %H:%M:%S",time_info);

    if (money<=0) {
        fprintf(fp,"[%s] ID: %d -- Action: %s \n",time,acc_id,type);
    }
    else {
        fprintf(fp,"[%s] ID: %d -- Action: %s -- Amount: %.2f \n",time,acc_id,type,money);
    }

    fclose(fp);
}

