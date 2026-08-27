//
// Created by emirhan on 8/19/2026.
//
#include <stdio.h>

#ifndef ACCOUNT_HEADERS_H
#define ACCOUNT_HEADERS_H

typedef struct {
    int id;
    char name[20];
    int password;
    float balance;
}account;

void deposit(account* acc,float money);
void withdraw(account * acc,float money);
void balance(account* acc);
account* add_account();
void add_accounts(account *db[],int nm);
void bank_screen();
void handle_bank_menu();
int log_in(int id,int passwd,account *user);
void add_accounts_from_file(FILE *src);
void account_screen();
void handle_account_menu(account *acc);

#endif


