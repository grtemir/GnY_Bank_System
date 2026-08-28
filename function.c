#include "headers.h"
#include <stdio.h>
#include <stdlib.h>




void bank_screen() {
    printf("-----------------------------------------------\n");
    printf("-----------Welcome to GnY bank system----------\n");
    printf("---------------Please choose...----------------\n");
    printf("-----------------------------------------------\n");
    printf("Press 1 to sign in...\n");
    printf("Press 2 to sign up...\n");
    printf("Press 3 to sign in as admin...\n");
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
                    printf("Please enter to continue account menu... \n");
                    getchar();
                    getchar();
                    handle_account_menu(&user);
                }
            }
            break;
            case 2:
                sign_up();
                break;
            case 3: {
                char id[20],pass[20];
                printf("Please enter admin account id : \n");
                scanf("%s",id);

                printf("Please enter admin password : \n");
                scanf("%s",pass);

                log_in_admin(id,pass);
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

    return 0;
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

void handle_account_menu(account *user) {
    int chs;
    do{
        system("cls");
        account_screen();
        scanf("%d",&chs);

       switch (chs) {
           case 1:
               printf("Your balance value is %f \n",user->balance);
               break;
           case 2: {
               float money;
               printf("Enter the amount to deposit: \n");
               scanf("%f",&money);
               deposit(user,money);
               break;
           }
           case 3:{
               float money;
               printf("Enter the amount to withdraw: \n");
               scanf("%f",&money);
               withdraw(user,money);
               break;
           }
           case 0:
               break;
           default:
               printf("Incvalid chocie!! Try again or exit...");
               break;

       }
        if (chs!=0) {
            printf("Press enter to continue... \n");
            getchar();
            getchar();
        }

   }while (chs!=0);
}

void admin_screen() {
    printf("Press 1 to add one account ...\n");
    printf("Press 2 to add many account ...\n");
    printf("Press 3 to load many account from file...\n");
    printf("Press 4 to list all accounts ...\n");
    printf("Press 0 to exit admin account...\n");
}

void handle_admin_menu() {
    int chs;
    do{
        system("cls");
        admin_screen();
        scanf("%d",&chs);
    switch (chs) {
        case 1:
            add_account();
            break;
        case 2:{
            int nm;
            printf("Enter number of accounts: \n");
            scanf("%d",&nm);
            account *accs[nm];
            add_accounts(accs,nm);
            break;
        }
        case 3: {
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
        case 4:
            list_accounts();
            break;
        case 0:
            printf("Existing system... \n");
            break;
        default:
            printf("Invalid chocie!! Try again or exit...");
            break;
    }

        printf("Please enter return to the admin menu...\n");
        getchar();
        getchar();

    }
    while (chs!=0);
}
