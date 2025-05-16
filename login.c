#include "login.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "styleText.h"
#include <windows.h>

void menuAdmin(){
    system("cls");
    printf("implement me");
}
void menuUser(){
    system("cls");
    printf("implement me");
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

char* getUsername(User *n) {
    return n->username;
}
int getPin(User *n) {
    return n->pin;
}

int getSaldo(User *n) {
    return n->saldo;
}

// Fungsi untuk menyimpan data nasabah ke file
void simpanUser(FILE *file, User *n) {
    fprintf(file, "Username: %s\n", n->username);
    fprintf(file, "PIN: %d\n", n->pin);
    fprintf(file, "Saldo: %d\n", n->saldo);
}

// Fungsi untuk membaca data User dari file
int bacaUser(FILE *file, User *n) {
    return fscanf(file, "Username: %s\n", n->username) != EOF &&
           fscanf(file, "PIN: %d\n", &n->pin) &&
           fscanf(file, "Saldo: %d\n\n", &n->saldo);
}







void registrasi(){
    User userBaru;
    char username[50];
    int pin, konfirmasiPin;
    long noRek;

	retry:
    printf("BUAT AKUN");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan username: ");
    scanf("%s", username);
    if (cekUsernameSudahAda(username)) {
        printf("Username sudah digunakan. Silakan pilih username lain.\n");
        Sleep(2000);
        system("cls");
        goto retry;
        return;
    }
    inputPin(&pin);
    printf("Konfirmasi PIN: ");
    inputPin(&konfirmasiPin);

    if (pin == konfirmasiPin) {

        // Set data user
        setUsername(&userBaru, username);
        setPin(&userBaru, pin);
        setSaldo(&userBaru, 0);

        // Simpan data ke file
        FILE *file = fopen("dataUser.txt", "a");
        if (file == NULL) {
            printf("Gagal membuka file untuk menyimpan data.\n");
            return;
        }
        simpanUser(file, &userBaru);
        fclose(file);

        printf("Selamat! Anda berhasil membuat akun.\n");
    } else {
        printf("PIN tidak cocok! Silakan coba lagi.\n");
    }
}

void loginAdmin(){
    char adminUsername[50];
    char inputUsername[50];
    int adminPassword;
    int inputPassword;
    int isAdminValid = 0;

    // Data admin (hardcoded atau gunakan file admin.txt)
    strcpy(adminUsername, "admin");
    adminPassword=1234;
	system("cls");
    printf("LOGIN ADMIN");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan Username Admin: ");
    scanf("%s", inputUsername);
    inputPin(&inputPassword);

    if (strcmp(inputUsername, adminUsername) == 0 && inputPassword==adminPassword) {
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


int cekUsernameSudahAda(const char *username) {
    FILE *file = fopen("dataUser.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk memeriksa username.\n");
        return 0; // Jika file tidak ada, dianggap username belum ada
    }

    User user;
    while (bacaUser(file, &user)) {
        if (strcmp(username, user.username) == 0) {
            fclose(file);
            return 1; // Username sudah ada
        }
    }

    fclose(file);
    return 0; // Username belum ada
}

// Fungsi untuk login user
void loginUser() {
    char inputUsername[50];
    int pinlogin;
    User user;
    int found = 0;

    printf("LOGIN USER");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan username: ");
    scanf("%s", inputUsername);

    // Buka file untuk membaca data user
    FILE *file = fopen("dataUser.txt", "r+"); // Gunakan mode "r+" untuk dapat menulis kembali
    if (file == NULL) {
        printf("Gagal membuka file! Pastikan file dataUser.txt ada.\n");
        return;
    }

    // Cek data user di file
    while (bacaUser(file, &user)) {
        if (strcmp(inputUsername, getUsername(&user)) == 0) {
            // Memulai proses verifikasi PIN
            while (pinlogin != getPin(&user)) {
                inputPin(&pinlogin);
                if (pinlogin == getPin(&user)) {
                    printf("Login berhasil! Selamat datang, %s.\n", getUsername(&user));
                    menuUser();
                    found = 1;
                    break;
                } else {
                    printf("PIN salah! Coba lagi");
                }
            }

            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Login gagal! Username tidak ditemukan atau PIN salah.\n");
    }
}
