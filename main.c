#include <stdio.h>
#include "headers.h"
#include <stdlib.h>

int main(void) {
    int chs;

    do{
    system("cls");
    bank_screen();
    scanf("%d",&chs);

    switch (chs) {
        case 1:
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
            add_accounts_from_file(stc);
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


    return 0;
}
