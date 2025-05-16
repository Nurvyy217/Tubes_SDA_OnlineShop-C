#include "login.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "styleText.h"

void registrasi(){
    User nasabahBaru;
    char username[50];
    int pin, konfirmasiPin;
    long noRek;

	retry:
    printTopCenter("BUAT AKUN");
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
        // Membuat nomor rekening secara random
        srand(time(NULL));
        noRek = 1000000000 + rand() % 9000000000;

        // Set data nasabah
        setUsername(&nasabahBaru, username);
        setPin(&nasabahBaru, pin);
        setSaldo(&nasabahBaru, 0);

        // Simpan data ke file
        FILE *file = fopen("dataUser.txt", "a");
        if (file == NULL) {
            printf("Gagal membuka file untuk menyimpan data.\n");
            return;
        }
        simpanNasabah(file, &nasabahBaru);
        fclose(file);

        printf("Selamat! Anda berhasil membuat akun.\n");
        printf("Nomor rekening Anda adalah: %ld\n", nasabahBaru.noRek);
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
    printTopCenter("LOGIN ADMIN");
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

    User nasabah;
    while (bacaNasabah(file, &nasabah)) {
        if (strcmp(username, nasabah.username) == 0) {
            fclose(file);
            return 1; // Username sudah ada
        }
    }

    fclose(file);
    return 0; // Username belum ada
}

// Fungsi untuk login nasabah
void loginUser() {
    char inputUsername[50];
    int pinlogin, salahPinCount = 0;
    User nasabah;
    int found = 0;

    printTopCenter("LOGIN NASABAH");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan username: ");
    scanf("%s", inputUsername);

    // Buka file untuk membaca data nasabah
    FILE *file = fopen("dataUser.txt", "r+"); // Gunakan mode "r+" untuk dapat menulis kembali
    if (file == NULL) {
        printf("Gagal membuka file! Pastikan file dataUser.txt ada.\n");
        return;
    }

    // Cek data nasabah di file
    while (bacaNasabah(file, &nasabah)) {
        if (strcmp(inputUsername, getUsername(&nasabah)) == 0) {
            if (nasabah.isBlocked==1) {
                printf("Akun Anda diblokir! Silakan hubungi admin.\n");
                found = 1;
                break;
            }

            // Memulai proses verifikasi PIN
            while (salahPinCount < 3) {
                inputPin(&pinlogin);
                if (pinlogin == getPin(&nasabah)) {
                    printf("Login berhasil! Selamat datang, %s.\n", getUsername(&nasabah));
                    tarikSaldo(&nasabah);
                    found = 1;
                    break;
                } else {
                    salahPinCount++;
                    printf("PIN salah! Coba lagi (%d/3)\n", salahPinCount);
                }
            }

            // Jika tiga kali salah PIN, blokir akun
            if (salahPinCount == 3) {
            	found=1;
            	printf("\nAkun Anda Terblokir silahkan hubungi admin!");
                blokir(&nasabah,1);
            }

            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Login gagal! Username tidak ditemukan atau PIN salah.\n");
    }
}
