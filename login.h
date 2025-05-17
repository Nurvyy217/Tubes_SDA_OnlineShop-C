#ifndef LOGIN_H
#define LOGIN_H
#include <stdio.h>
#include "sqlite3.h"
#include "transitKota.h"

typedef struct {
    char username[50];
    int pin;
    int saldo;
} User;

// Updated function declarations to accept db parameter
void initDatabase(sqlite3 **db);
void closeDatabase(sqlite3 *db);
void topUp(User *user, sqlite3 *db);
void menuAdmin();
void menuUser(User *user, TreeManager *tm, sqlite3 *db);
void setUsername(User *n, const char *username);
void setPin(User *n, int pin);
void setSaldo(User *n, int saldo);
int getPin(User *n);
char *getUsername(User *n);
int getSaldo(User *n);
void simpanUser(User *u, sqlite3 *db);
void registrasi(sqlite3 *db);
void loginAdmin();
int cekUsernameSudahAda(const char *username, sqlite3 *db);
void loginUser(TreeManager *tm, sqlite3 *db);
int getUserByUsername(const char *username, User *u, sqlite3 *db);
void beliProduk(TreeManager *tm);
void inputPin(int *pin);

#endif