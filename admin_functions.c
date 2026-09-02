#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

account* add_account() {
    account *acc=malloc(sizeof(account));

    printf("Enter an account id: \n");
    if (scanf("%d",&(acc->id))!=1) {
        perror("Scanf error ");
        exit(1);
    }

    printf("Enter account password: \n");
    if (scanf("%s",(acc->password))!=1) {
        perror("Scanf error ");
        exit(1);}

    printf("Enter a name : \n");
    if (scanf("%s",acc->name)!=1) {
        perror("Scanf error ");
        exit(1);}

    printf("Enter balance: \n");
    if (scanf("%f",&(acc->balance))!=1) {
        perror("Scanf error ");
        exit(1);}


    FILE *fp=fopen(DB_FILE,"a");
    if (fp==NULL) {
        perror("fopen error");
        exit(1);}

    char hashed_psw[HASH_LEN];
    hash_sha256(acc->password,hashed_psw);

    strcpy(acc->password,hashed_psw);

    fprintf(fp,"%d:%s:%s:%.2f\n",acc->id,acc->name,hashed_psw,acc->balance);

    log_transaction(acc->id,"ADMIN_ADD_ACC_SUCCESS",0);

    if (fclose(fp)==EOF) {
        log_transaction(acc->id,"ADMIN_ADD_ACC_FAILED_FILE_ERROR",0);
        perror("Fclose error");
    }
    return acc;
}

void add_accounts(account *db[],int nm) {

    int i;
    for (i=0;i<nm;i++) {
        db[i]=add_account();
    }
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

void log_in_admin(char id[20],char key[20]) {
    if ((strcmp(id,ADMIN_ID)==0 && strcmp(key,ADMIN_PASSWORD)==0)){
        log_transaction(000, "ADMIN_LOGIN_SUCCESS", 0);
        admin_screen();
        handle_admin_menu();
    }
    else {
        log_transaction(0, "ADMIN_LOGIN_FAILED", 0);
        printf("You entered wrong id or password, try again... \n");
    }


}

void list_accounts() {
    FILE *fp=fopen(DB_FILE,"r");
    if (fp==NULL) {
        perror("fopen error");
        return;
    }




    account user;

    printf("|------|--------------------|-------------|\n");
    printf("|--ID--|--------NAME--------|---BALANCE---|\n");
    printf("|------|--------------------|-------------|\n");

    while((fscanf(fp,"%d:%19[^:]:%65[^:]:%f",&user.id,user.name,user.password,&user.balance))==4) {

        printf("|%6d|%20s|%13f|\n",user.id,user.name,user.balance);

    }
    printf("|------|--------------------|-------------|\n");

    printf("");
}

void list_logs() {
    FILE *logs=fopen(LOG_FILE,"r");
    if (logs==NULL) {
        perror("fopen error");
        return;
    }

    printf("|------|----LOG-RECORDS-----|-------------|\n");

    char buff[256];

    while (fgets(buff,sizeof(buff),logs)) {
        fputs(buff,stdout);
    }

    fclose(logs);
}