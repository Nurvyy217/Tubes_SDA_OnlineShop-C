#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../include/styleText.h"
#include "../include/user.h"
#include "../include/stack.h"


void initUserFile()
{
    FILE *file = fopen(USER_FILE, "a");
    if (file)
    {
        fclose(file);
    }
}

void saveUser(User *u)
{
    FILE *file = fopen(USER_FILE, "a");
    if (!file)
    {
        printf("Error: Cannot open user file\n");
        return;
    }
    fprintf(file, "%d,%s,%d,%d,%s\n", u->id, u->username, u->pin, u->saldo, u->domisili);
    fclose(file);
}

int getUserByUsername(const char *username, User *u)
{
    FILE *file = fopen(USER_FILE, "r");
    if (!file)
        return 0;

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int tempId, tempPin, tempSaldo;
        char tempUsername[50], tempDomisili[100];
        if (sscanf(line, "%d,%49[^,],%d,%d,%99[^\n]", &tempId, tempUsername, &tempPin, &tempSaldo, tempDomisili) == 5)
        {
            if (strcmp(tempUsername, username) == 0)
            {
                u->id = tempId;
                strcpy(u->username, tempUsername);
                u->pin = tempPin;
                u->saldo = tempSaldo;
                strcpy(u->domisili, tempDomisili);
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

void updateUserInFile(User *user)
{
    FILE *file = fopen(USER_FILE, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile)
        return;

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int tempId, tempPin, tempSaldo;
        char tempUsername[50], tempDomisili[100];
        if (sscanf(line, "%d,%49[^,],%d,%d,%99[^\n]", &tempId, tempUsername, &tempPin, &tempSaldo, tempDomisili) == 5)
        {
            if (strcmp(tempUsername, user->username) == 0)
            {
                fprintf(tempFile, "%d,%s,%d,%d,%s\n", user->id, user->username, user->pin, user->saldo, user->domisili);
            }
            else
            {
                fprintf(tempFile, "%s", line);
            }
        }
        else
        {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(USER_FILE);
    rename("temp.txt", USER_FILE);
}

int getLastUserId()
{
    FILE *file = fopen(USER_FILE, "r");
    if (!file) return 0;
    int lastId = 0, tempId, tempPin, tempSaldo;
    char tempUsername[50], tempDomisili[100];
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d,%49[^,],%d,%d,%99[^\n]", &tempId, tempUsername, &tempPin, &tempSaldo, tempDomisili) == 5)
        {
            lastId = tempId;
        }
    }
    fclose(file);
    return lastId;
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
        user->saldo += jumlahIsiSaldo;
        updateUserInFile(user);
        printf("Saldo berhasil diisi. Saldo Anda: %d\n", user->saldo);
    }
    else
    {
        printf("Jumlah saldo yang diisi harus lebih dari 0.\n");
    }
}

void registration()
{
    User userBaru;
    char username[50];
    int pin, konfirmasiPin;
    char domisili[100];
    TreeManager tm;
    InitTree(&tm);

retry:
    system("cls");
    printf("\t\t\t\t\t\t\tBUAT AKUN\n");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan username: ");
    scanf("%s", username);
    if (isUsernameExists(username))
    {
        printf("Username sudah digunakan.\n");
        Sleep(2000);
        goto retry;
    }

    inputPin(&pin);
    printf("Konfirmasi PIN: ");
    inputPin(&konfirmasiPin);

    // Input domisili, harus ada di tree
    while (1) {
        printf("Masukkan domisili (kota asal, harus berada di Jawa Barat atau Jabodetabek): ");
        scanf("%s", domisili);
        if (find_node_by_name(&tm, domisili)) {
            break;
        } else {
            printf("Kota yang diinputkan tidak ditemukan.\n");
            printf("Kota harus berada di daerah Jawa Barat dan Jabodetabek.\n");
            showCityList(&tm);
        }
    }

    if (pin == konfirmasiPin)
    {
         userBaru.id = getLastUserId() + 1;
        strcpy(userBaru.username, username); 
        userBaru.pin = pin;                  
        userBaru.saldo = 0;                  
        strcpy(userBaru.domisili, domisili); 
        saveUser(&userBaru);
        printf("Akun berhasil dibuat.\n");
    }
    else
    {
        printf("PIN tidak cocok.\n");
    }
}

void loginUser(TreeManager *tm, List P)
{
    char inputUsername[50];
    int pinlogin;
    User user;

    printf("\t\t\t\t\t\t\tLOGIN USER\n");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\nMasukkan username: ");
    scanf("%s", inputUsername);

    if (!getUserByUsername(inputUsername, &user))
    {
        printf("Username tidak ditemukan.\n");
        return;
    }

    while (1)
    {
        inputPin(&pinlogin);
        if (pinlogin == user.pin)
        {
            printf("Login berhasil! Selamat datang, %s.\n", user.username);
            userMenu(&user, tm, P);
            break;
        }
        else
        {
            printf("PIN salah! Coba lagi.\n");
        }
    }
}


int isUsernameExists(const char *username)
{
    User temp;
    return getUserByUsername(username, &temp);
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

void viewProduct(TreeManager *tm, User *user, List P){
    int choice;
    userPrintKatalogByKategori(P);
    printf("\n1. Beli produk\n");
    printf("2. Masukkan ke keranjang\n");
        printf("3. Kembali\n");
        printf("Masukkan pilihan anda : ");
        scanf(" %c", &choice);
        if(choice == '1'){
            buyProduct(tm, user);
            system("cls");    
        }else if(choice == '2'){
            printf("modul pembelian...");
        }
}


void buyProduct(TreeManager *tm, User *user)
{
    char tujuan[100];
    int useDomisili = 0;
    while (1) {
        printf("Kota tujuan: %s\n", user->domisili);
        printf("Kirim ke alamat ini? (y/n): ");
        char yn[10];
        scanf("%s", yn);
        if (yn[0] == 'y' || yn[0] == 'Y') {
            strcpy(tujuan, user->domisili);
            break;
        } else {
            while (1) {
                printf("Masukkan nama kota tujuan (harus berada di Jawa Barat atau Jabodetabek): ");
                scanf("%s", tujuan);
                if (find_node_by_name(tm, tujuan)) {
                    break;
                } else {
                    printf("Kota yang diinputkan tidak ditemukan.\n");
                    printf("Kota tujuan harus berada di daerah Jawa Barat dan Jabodetabek.\n");
                    showCityList(tm);
                }
            }
            break;
        }
    }

    //Modul mengurangi stok barang

    TreeNode *target = find_node_by_name(tm, tujuan);
    printf("Rute pengiriman:\n");
    print_route(target);
}

void userMenu(User *user, TreeManager *tm, List P)
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
        printf("4. Lihat/Beli Produk\n");
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
            viewProduct(tm, user, P);
            break;
        case 3:
            infoPemesanan(user);
            break;
        case 4:
            viewProduct(tm, user, P);
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




