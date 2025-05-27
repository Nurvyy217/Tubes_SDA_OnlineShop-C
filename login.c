#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "styleText.h"
#include "login.h"

#define USER_FILE "user.txt"

void initUserFile() {
    FILE *file = fopen(USER_FILE, "a");
    if (file) {
        fclose(file);
    }
}

void simpanUser(User *u) {
    FILE *file = fopen(USER_FILE, "a");
    if (!file) {
        printf("Error: Cannot open user file\n");
        return;
    }
    fprintf(file, "%s,%d,%d\n", u->username, u->pin, u->saldo);
    fclose(file);
}

int getUserByUsername(const char *username, User *u) {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char tempUsername[50];
        int tempPin, tempSaldo;
        sscanf(line, "%[^,],%d,%d", tempUsername, &tempPin, &tempSaldo);
        
        if (strcmp(tempUsername, username) == 0) {
            strcpy(u->username, tempUsername);
            u->pin = tempPin;
            u->saldo = tempSaldo;
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void updateUserInFile(User *user) {
    FILE *file = fopen(USER_FILE, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) return;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char tempUsername[50];
        int tempPin, tempSaldo;
        sscanf(line, "%[^,],%d,%d", tempUsername, &tempPin, &tempSaldo);
        
        if (strcmp(tempUsername, user->username) == 0) {
            fprintf(tempFile, "%s,%d,%d\n", user->username, user->pin, user->saldo);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(USER_FILE);
    rename("temp.txt", USER_FILE);
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
        updateUserInFile(user);
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

void viewProduct() {
    system("cls");
    printf("Implement me");
}

void menuAdmin() {
    system("cls");
    printf("1. ");
}

void infoPemesanan(User *user) {
    system("cls");
    printf("\t\t\t\t\t\t\tINFO PEMESANAN\n");
    printf("\t\t\t\t\t<=====================================>\n\n");
    printf("Pengiriman barang Anda sedang dalam proses.\n");
    printf("Status Transit: .\n");
    printf("Estimasi sampai: 2 hari.\n");
}

void beliProduk(TreeManager *tm) {
    char tujuan[100];
    printf("Masukkan kota tujuan: ");
    scanf("%s", tujuan);

    Node *target = find_node_by_name(tm, tujuan);
    printf("Rute pengiriman ke %s:\n", tujuan);
    print_route(target);
}

void menuUser(User *user, TreeManager *tm) {
    int choice;
    do {
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
        switch (choice) {
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

void setUsername(User *n, const char *username) {
    strcpy(n->username, username);
}

void setPin(User *n, int pin) {
    n->pin = pin;
}

void setSaldo(User *n, int saldo) {
    n->saldo = saldo;
}

char *getUsername(User *n) {
    return n->username;
}

int getPin(User *n) {
    return n->pin;
}

int getSaldo(User *n) {
    return n->saldo;
}

void loginAdmin() {
    char adminUsername[50];
    char inputUsername[50];
    int adminPassword;
    int inputPassword;
    int isAdminValid = 0;

    strcpy(adminUsername, "admin");
    adminPassword = 1234;
    system("cls");
    printf("\t\t\t\t\t\t\tLOGIN ADMIN\n");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan Username Admin: ");
    scanf("%s", inputUsername);
    inputPin(&inputPassword);

    if (strcmp(inputUsername, adminUsername) == 0 && inputPassword == adminPassword) {
        isAdminValid = 1;
    }

    if (isAdminValid) {
        printf("\n\n\nLogin Admin berhasil. Selamat datang, Admin.\n");
        Sleep(2000);
        menuAdmin();
    } else {
        printf("\nLogin Admin gagal! Username atau Password salah.\n");
    }
}

