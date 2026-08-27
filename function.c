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

void balance(account *acc) {
    printf("Current balance is %.2f \n",acc->balance);
}

account* add_account() {
    account *acc=malloc(sizeof(account));

    printf("Enter an account id: \n");
    if (scanf("%d",&(acc->id))!=1) {
           perror("Scanf error ");
           exit(1);
    }

    printf("Enter account password: \n");
    if (scanf("%d",&(acc->password))!=1) {
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

    fprintf(fp,"%d:%s:%d:%f\n",acc->id,acc->name,acc->password,acc->balance);

    if (fclose(fp)==EOF) {
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

void handle_bank_menu() {
    int chs;
    do{
        system("cls");
        bank_screen();
        scanf("%d",&chs);

        switch (chs) {
            case 1: {
                int id,passwd,success;
                account user;

                printf("Please enter your id: \n");
                scanf("%d",&id);
                printf("Please enter your password: \n");
                scanf("%d",&passwd);

                success=log_in(id,passwd,&user);
                if (success==1) {
                    handle_account_menu(&user);
                }
                getchar();
                getchar();

            }
            break;
            case 2:
                add_account();
                break;
            case 3:{
                int nm;
                printf("Enter number of accounts: \n");
                scanf("%d",&nm);
                account *accs[nm];
                add_accounts(accs,nm);
                break;
            }
            case 4: {
                char fname[20];
                printf("Enter the file name...\n");
                scanf("%s",fname);
                FILE *src=fopen(fname ,"r");
                if (src==NULL) {
                    perror("fopen error");
                    continue;
                }
                add_accounts_from_file(src);
                if (fclose(src)==EOF) {
                    perror("fclose error \n");
                    continue;
                };
            }
            break;
            case 0:
                printf("Existing system...\n");
                break;
            default:
                printf("Invalid chocie!! Try again or exit. \n");
                break;
        }
        if (chs!=0) {
            printf("Please enter to return main menu...\n");
            getchar();
            getchar();
        }}
    while(chs!=0);
}


int log_in(int id,int passwd,account *user) {
    FILE *fp=fopen(DB_FILE,"r");
    if (fp==NULL) {
        perror("fopen error \n");
        return 0;
    }

    account tmp;

    while (fscanf(fp,"%d:%19[^:]:%d:%f",&tmp.id,tmp.name,&tmp.password,&tmp.balance)==4) {
        if ((passwd==tmp.password)&&(id==tmp.id)) {
            printf("Login successful! Welcome, %s.",tmp.name);
            *user=tmp;
            fclose(fp);
            return 1;
        }

    }
    printf("Invalid ID or password!\n");

    return 1;
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

void account_screen() {
    printf("-----------------------------------------------\n");
    printf("-----------------Account Menu------------------\n");
    printf("---------------Please choose...----------------\n");
    printf("-----------------------------------------------\n");
    printf("Press 1 to check balance...\n");
    printf("Press 2 to deposit money...\n");
    printf("Press 3 to withdraw money...\n");
    printf("Press 0 to log out...\n");
    printf("-----------------------------------------------\n");
    printf("-----------------------------------------------\n");
}

void handle_account_menu(account *acc) {
    int chs;
    do{
        system("cls");
        account_screen();
        scanf("%d",&chs);

       switch (chs) {
           case 1:
               break;
           case 2:
               break;
           case 3:
               break;
           case 0:
               break;
               deafult:
                   printf("Incvalid chocie!! Try again or exit...");
               break;

       }

   }while (chs!=0);
}

