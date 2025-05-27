#ifndef LOGIN_H
#define LOGIN_H
#include <stdio.h>
#include "transitKota.h"

typedef struct {
    char username[50];
    int pin;
    int saldo;
} User;

void initUserFile();
void topUp(User *user);
void menuAdmin();
void menuUser(User *user, TreeManager *tm);
void setUsername(User *n, const char *username);
void setPin(User *n, int pin);
void setSaldo(User *n, int saldo);
int getPin(User *n);
char *getUsername(User *n);
int getSaldo(User *n);
void simpanUser(User *u);
void registrasi();
void loginAdmin();
int cekUsernameSudahAda(const char *username);
void loginUser(TreeManager *tm);
int getUserByUsername(const char *username, User *u);
void beliProduk(TreeManager *tm);
void inputPin(int *pin);

#endif