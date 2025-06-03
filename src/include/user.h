#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include "tree.h"

// Path file user
#define USER_FILE "data/user.txt"

// Struktur data user
typedef struct
{
    char username[50];
    int pin;
    int saldo;
} User;

// Inisialisasi file user (buat jika belum ada)
void initUserFile();

// Registrasi user baru
void registrasi();

// Login user
void loginUser(TreeManager *tm);

// Simpan user baru ke file
void simpanUser(User *u);

// Cek apakah username sudah ada
int cekUsernameSudahAda(const char *username);

// Ambil data user berdasarkan username
int getUserByUsername(const char *username, User *u);

// Menu utama user
void menuUser(User *user, TreeManager *tm);

// Top up saldo user
void topUp(User *user);

// Fungsi bantu set/get user
void setUsername(User *n, const char *username);
void setPin(User *n, int pin);
void setSaldo(User *n, int saldo);
int getPin(User *n);
char *getUsername(User *n);
int getSaldo(User *n);

// Fitur beli produk (sementara)
void beliProduk(TreeManager *tm);

#endif