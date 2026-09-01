//
// Created by emirhan on 8/19/2026.
//
#include <stdio.h>

#ifndef ACCOUNT_HEADERS_H
#define ACCOUNT_HEADERS_H

#define DB_FILE "accounts.txt"
#define TEMP_FILE "temp.txt"

#define ADMIN_ID "Admin123"
#define ADMIN_PASSWORD "11223344"
typedef struct {
    int id;
    char name[20];
    int password;
    float balance;
}account;

void sign_up();
int log_in(int id,int passwd,account *user);
void deposit(account* user,float money);
int withdraw(account * user,float money);
void balance(account* user);
void update_balance(account *user);
void transfer_money(account *sen,int receiver, float money);


account* add_account();
void add_accounts(account *db[],int nm);
void add_accounts_from_file(FILE *src);
void log_in_admin(char id[20],char key[20]);
void list_accounts();

void bank_screen();
void handle_bank_menu();

void account_screen();
void handle_account_menu(account *acc);

void admin_screen();
void handle_admin_menu();

int find_addres(int id,account *acc);

#endif


