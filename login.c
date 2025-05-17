#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "sqlite3.h"
#include "styleText.h"
#include "login.h"


sqlite3 *db;

void initDatabase() {
    char *errMsg = 0;
    if (sqlite3_open("userDB.db", &db)) {
        fprintf(stderr, "Tidak bisa membuka database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char *createTable =
        "CREATE TABLE IF NOT EXISTS user ("
        "username TEXT PRIMARY KEY,"
        "pin INTEGER,"
        "saldo INTEGER);";

    if (sqlite3_exec(db, createTable, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        exit(1);
    }
}

void simpanUser(User *u) {
    char sql[256];
    snprintf(sql, sizeof(sql),
             "INSERT INTO user (username, pin, saldo) VALUES ('%s', %d, %d);",
             u->username, u->pin, u->saldo);

    char *errMsg;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Gagal simpan user: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

int getUserByUsername(const char *username, User *u) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT username, pin, saldo FROM user WHERE username = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    int found = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(u->username, (const char *)sqlite3_column_text(stmt, 0));
        u->pin = sqlite3_column_int(stmt, 1);
        u->saldo = sqlite3_column_int(stmt, 2);
        found = 1;
    }
    sqlite3_finalize(stmt);
    return found;
}

void topUp(User *user) {
    int jumlahIsiSaldo;
    system("cls");
    printTopCenter("TOP UP SALDO\n");
    printf("\t\t\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan jumlah saldo yang ingin diisi: ");
    scanf(" %d", &jumlahIsiSaldo);

    if (jumlahIsiSaldo > 0) {
        user->saldo += jumlahIsiSaldo;
        char sql[256];
        snprintf(sql, sizeof(sql),
                 "UPDATE user SET saldo = %d WHERE username = '%s';",
                 user->saldo, user->username);

        char *errMsg;
        if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
            return;
        }

        printf("Saldo berhasil diisi. Saldo Anda: %d\n", user->saldo);
    } else {
        printf("Jumlah saldo yang diisi harus lebih dari 0.\n");
    }
}

void registrasi() {
    User userBaru;
    char username[50];
    int pin, konfirmasiPin;

retry:
    system("cls");
    printf("\t\t\t\t\t\t\tBUAT AKUN\n");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan username: ");
    scanf("%s", username);
    if (cekUsernameSudahAda(username)) {
        printf("Username sudah digunakan.\n");
        Sleep(2000);
        goto retry;
    }

    inputPin(&pin);
    printf("Konfirmasi PIN: ");
    inputPin(&konfirmasiPin);

    if (pin == konfirmasiPin) {
        setUsername(&userBaru, username);
        setPin(&userBaru, pin);
        setSaldo(&userBaru, 0);
        simpanUser(&userBaru);
        printf("Akun berhasil dibuat.\n");
    } else {
        printf("PIN tidak cocok.\n");
    }
}

void loginUser(TreeManager *tm) {
    char inputUsername[50];
    int pinlogin;
    User user;

    printf("\t\t\t\t\t\t\tLOGIN USER\n");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan username: ");
    scanf("%s", inputUsername);

    if (!getUserByUsername(inputUsername, &user)) {
        printf("Username tidak ditemukan.\n");
        return;
    }

    while (1) {
        inputPin(&pinlogin);
        if (pinlogin == user.pin) {
            printf("Login berhasil! Selamat datang, %s.\n", user.username);
            menuUser(&user, tm);
            break;
        } else {
            printf("PIN salah! Coba lagi.\n");
        }
    }
}

int cekUsernameSudahAda(const char *username) {
    User temp;
    return getUserByUsername(username, &temp);
}

void viewProduct()
{
    system("cls");
    printf("Implement me");
}



void menuAdmin()
{
    system("cls");
    printf("1. ");
}

void infoPemesanan(User *user)
{
    system("cls");
    printf("\t\t\t\t\t\t\tINFO PEMESANAN\n");
    printf("\t\t\t\t\t<=====================================>\n\n");
    printf("Pengiriman barang Anda sedang dalam proses.\n");
    printf("Status Transit: .\n");
    printf("Estimasi sampai: 2 hari.\n");
}

void beliProduk(TreeManager *tm) {
    char tujuan[100];
    // Input data pembelian (nama, produk, dll)
    // ...
    printf("Masukkan kota tujuan: ");
    scanf("%s", tujuan);

    // Proses pembelian produk
    // ...

    // Setelah pembelian berhasil, tampilkan info rute pengiriman
    Node *target = find_node_by_name(tm, tujuan);
    printf("Rute pengiriman ke %s:\n", tujuan);
    print_route(target);
}

void menuUser(User *user, TreeManager *tm)
{
    int choice;
    do
    {
        system("cls");
        printf("\t\t\t\t\t\t\tMENU USER\n");
        printf("\t\t\t\t\t<=====================================>\n\n\n");
        printf("1. Top Up Saldo\n");
        printf("2. Tampilkan Produk\n");
        printf("3. Info Pemesanan\n");
        printf("4. Beli Produk\n");
        printf("5. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            topUp(user);
            system("pause");
            break;
        case 2:
            viewProduct();
            break;
        case 3:
            infoPemesanan(user);
            break;
        case 4:
            beliProduk(tm);
            printf("Fitur beli produk belum diimplementasikan.\n");
            system("pause");
            break;
        case 5:
            printf("Keluar dari program!\n");
            break;
        default:
            printf("Pilihan tidak valid\n");
            break;
        }
    } while (choice != 5);
}

void setUsername(User *n, const char *username)
{
    strcpy(n->username, username);
}
void setPin(User *n, int pin)
{
    n->pin = pin;
}

void setSaldo(User *n, int saldo)
{
    n->saldo = saldo;
}

char *getUsername(User *n)
{
    return n->username;
}
int getPin(User *n)
{
    return n->pin;
}

int getSaldo(User *n)
{
    return n->saldo;
}


void loginAdmin()
{
    char adminUsername[50];
    char inputUsername[50];
    int adminPassword;
    int inputPassword;
    int isAdminValid = 0;

    // Data admin (hardcoded atau gunakan file admin.txt)
    strcpy(adminUsername, "admin");
    adminPassword = 1234;
    system("cls");
    printf("\t\t\t\t\t\t\tLOGIN ADMIN\n");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan Username Admin: ");
    scanf("%s", inputUsername);
    inputPin(&inputPassword);

    if (strcmp(inputUsername, adminUsername) == 0 && inputPassword == adminPassword)
    {
        isAdminValid = 1;
    }

    if (isAdminValid)
    {
        printf("\n\n\nLogin Admin berhasil. Selamat datang, Admin.\n");
        Sleep(2000);
        menuAdmin();
    }
    else
    {
        printf("\nLogin Admin gagal! Username atau Password salah.\n");
    }
}


