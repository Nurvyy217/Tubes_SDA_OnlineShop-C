#include "login.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "styleText.h"
#include <windows.h>

void viewProduct()
{
    system("cls");
    printf("Implement me");
}

void topUp(User *user)
{
    int jumlahIsiSaldo;
    system("cls");
    printTopCenter("TOP UP SALDO\n");
    printf("\t\t\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan jumlah saldo yang ingin diisi: ");
    scanf(" %d", &jumlahIsiSaldo);

    if (jumlahIsiSaldo > 0)
    {
        // Perbarui saldo user
        user->saldo += jumlahIsiSaldo;

        // Baca semua data user dari file
        FILE *file = fopen("dataUser.txt", "r");
        if (file == NULL)
        {
            printf("Gagal membuka file untuk membaca data user.\n");
            return;
        }

        // Simpan data ke buffer
        User bufferUser[100];
        int count = 0;
        while (bacaUser(file, &bufferUser[count]))
        {
            count++;
        }
        fclose(file);

        // Perbarui data user yang sesuai
        int i;
        for (i = 0; i < count; i++)
        {
            if (strcmp(user->username, bufferUser[i].username) == 0)
            {
                bufferUser[i].saldo = user->saldo;
                break;
            }
        }

        // Tulis kembali semua data user ke file
        file = fopen("dataUser.txt", "w");
        if (file == NULL)
        {
            printf("Gagal membuka file untuk menyimpan data user.\n");
            return;
        }
        for (i = 0; i < count; i++)
        {
            simpanUser(file, &bufferUser[i]);
        }
        fclose(file);
        printf("Saldo berhasil diisi. Saldo Anda: %d\n", user->saldo);
    }
    else
    {
        printf("Jumlah saldo yang diisi harus lebih dari 0.\n");
    }
}

void menuAdmin()
{
    system("cls");
    printf("implement me");
}
void menuUser(User *user)
{
    int choice;
    do
    {
        system("cls");
        printf("\t\t\t\t\t\t\tMENU USER\n");
        printf("\t\t\t\t\t<=====================================>\n\n\n");
        printf("1.Top Up Saldo\n");
        printf("2. Tampilkan Produk\n");
        printf("3. Keluar\n");
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
            printf("Keluar dari program!\n");
            break;
        default:
            printf("pilihan tidak valid");
            break;
        }
    } while (choice != 3);
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

// Fungsi untuk menyimpan data user ke file
void simpanUser(FILE *file, User *n)
{
    fprintf(file, "Username: %s\n", n->username);
    fprintf(file, "PIN: %d\n", n->pin);
    fprintf(file, "Saldo: %d\n", n->saldo);
}

// Fungsi untuk membaca data User dari file
int bacaUser(FILE *file, User *n)
{
    return fscanf(file, "Username: %s\n", n->username) != EOF &&
           fscanf(file, "PIN: %d\n", &n->pin) &&
           fscanf(file, "Saldo: %d\n\n", &n->saldo);
}

void registrasi()
{
    User userBaru;
    char username[50];
    int pin, konfirmasiPin;
    long noRek;

retry:
    printf("\t\t\t\t\t\t\tBUAT AKUN\n");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan username: ");
    scanf("%s", username);
    if (cekUsernameSudahAda(username))
    {
        printf("Username sudah digunakan. Silakan pilih username lain.\n");
        Sleep(2000);
        system("cls");
        goto retry;
        return;
    }
    inputPin(&pin);
    printf("Konfirmasi PIN: ");
    inputPin(&konfirmasiPin);

    if (pin == konfirmasiPin)
    {

        // Set data user
        setUsername(&userBaru, username);
        setPin(&userBaru, pin);
        setSaldo(&userBaru, 0);

        // Simpan data ke file
        FILE *file = fopen("dataUser.txt", "a");
        if (file == NULL)
        {
            printf("Gagal membuka file untuk menyimpan data.\n");
            return;
        }
        simpanUser(file, &userBaru);
        fclose(file);

        printf("Selamat! Anda berhasil membuat akun.\n");
    }
    else
    {
        printf("PIN tidak cocok! Silakan coba lagi.\n");
    }
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

int cekUsernameSudahAda(const char *username)
{
    FILE *file = fopen("dataUser.txt", "r");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk memeriksa username.\n");
        return 0; // Jika file tidak ada, dianggap username belum ada
    }

    User user;
    while (bacaUser(file, &user))
    {
        if (strcmp(username, user.username) == 0)
        {
            fclose(file);
            return 1; // Username sudah ada
        }
    }

    fclose(file);
    return 0; // Username belum ada
}

// Fungsi untuk login user
void loginUser()
{
    char inputUsername[50];
    int pinlogin;
    User user;
    int found = 0;

    printf("\t\t\t\t\t\t\tLOGIN USER\n");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan username: ");
    scanf("%s", inputUsername);

    // Buka file untuk membaca data user
    FILE *file = fopen("dataUser.txt", "r+"); // Gunakan mode "r+" untuk dapat menulis kembali
    if (file == NULL)
    {
        printf("Gagal membuka file! Pastikan file dataUser.txt ada.\n");
        return;
    }

    // Cek data user di file
    while (bacaUser(file, &user))
    {
        if (strcmp(inputUsername, getUsername(&user)) == 0)
        {
            // Memulai proses verifikasi PIN
            while (pinlogin != getPin(&user))
            {
                inputPin(&pinlogin);
                if (pinlogin == getPin(&user))
                {
                    printf("Login berhasil! Selamat datang, %s.\n", getUsername(&user));
                    menuUser(&user);
                    found = 1;
                    break;
                }
                else
                {
                    printf("PIN salah! Coba lagi");
                }
            }

            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Login gagal! Username tidak ditemukan atau PIN salah.\n");
    }
}
