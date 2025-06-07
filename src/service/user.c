#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../include/user.h"
#include "../include/stack.h"
#include "../include/printTemplate.h"

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
        if (sscanf(line, "%d,%49[^,],%d,%d,%99[^\n]", &tempId, tempUsername, &tempPin, &tempSaldo, tempDomisili) == 5) // parsing data dari baris
        //kenapa pakai &? karena sscanf membutuhkan alamat dari variabel untuk menyimpan data yang dibaca
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

// update user di file jika ada perubahan
void updateUserInFile(User *user)
{
    FILE *file = fopen(USER_FILE, "r");
    FILE *tempFile = fopen("temp.txt", "w"); // buat file sementara untuk menyimpan data yang sudah diupdate. Jika file sudah ada, isinya akan dihapus total.
    if (!file || !tempFile)
        return; // jika file tidak ditemukan, keluar dari fungsi

    char line[256];
    while (fgets(line, sizeof(line), file)) // membaca setiap baris dari file dan menyimpannya ke dalam array of char line
    {
        int tempId, tempPin, tempSaldo;
        char tempUsername[50], tempDomisili[100];
        if (sscanf(line, "%d,%49[^,],%d,%d,%99[^\n]", &tempId, tempUsername, &tempPin, &tempSaldo, tempDomisili) == 5)
        {
            if (strcmp(tempUsername, user->username) == 0) // jika username cocok dengan user yang ingin diupdate
            {
                fprintf(tempFile, "%d,%s,%d,%d,%s\n", user->id, user->username, user->pin, user->saldo, user->domisili);
                // update data user di file sementara
            }
            else
            {
                fprintf(tempFile, "%s", line);
                // jika tidak cocok, tulis baris tersebut (di user.txt) ke file sementara
            }
        }
        else
        {
            fprintf(tempFile, "%s", line);
            // jika format baris tidak sesuai, tetap tulis baris tersebut ke file sementara
            // ini untuk menghindari error jika ada baris yang tidak sesuai format
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(USER_FILE); // hapus file asli (user.txt)
    rename("temp.txt", USER_FILE); // ganti nama file sementara (temp.txt) menjadi user.txt
}

// Mendapatkan ID user terakhir dari file
int getLastUserId()
{
    FILE *file = fopen(USER_FILE, "r"); // mode read untuk membaca file
    if (!file) return 0;
    int lastId = 0, tempId, tempPin, tempSaldo;
    char tempUsername[50], tempDomisili[100];
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d,%49[^,],%d,%d,%99[^\n]", &tempId, tempUsername, &tempPin, &tempSaldo, tempDomisili) == 5)
        {
            lastId = tempId;
            // ambil ID terakhir dari file
        }
    }
    fclose(file);
    return lastId;
}

// isi Saldo user
void topUp(User *user)
{
    int jumlahIsiSaldo;
    system("cls");
    print_title("TOP UP SALDO", WIDTH);
    printf("\nMasukkan jumlah saldo yang ingin diisi: ");
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

// registrasi user baru (daftarkan di file user.txt)
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
    print_title("BUAT AKUN", WIDTH);
    printf("\nMasukkan username: ");
    scanf("%s", username);
    // Cek apakah username sudah ada
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
            break; // Jika kota ditemukan di tree, keluar dari loop
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

void loginUser(User *user)
{
    char inputUsername[50];
    int pinlogin;

    print_title("LOGIN USER", WIDTH);
    while(1){
    printf("\nMasukkan username: ");
    scanf("%s", inputUsername);
    if (!getUserByUsername(inputUsername, user))
    {
        printf("Username tidak ditemukan.\n");
    }else{
        break;
        }
    }
    
    while (1)
    {
        inputPin(&pinlogin);
        if (pinlogin == user->pin)
        {
            printf("\n\nLogin berhasil! Selamat datang, %s.\n", user->username);
            sleep(2);
            break;
            // Keluar dari loop jika login berhasil dan masuk ke menu user
        }
        else
        {
            printf("PIN salah! Coba lagi.\n");
        }
    }
    return;
}

// Cek apakah username sudah ada, jika ada, return 1, jika tidak ada, return 0
int isUsernameExists(const char *username)
{
    User temp;
    return getUserByUsername(username, &temp);
}

// Tabel informasi/riwayat pesanan
void orderInformation(User *user)
{
    TQueue TList;
    system("cls");
    print_title("INFO PESANAN", WIDTH);
    GenerateTransactionListByUser(&TList, user->id, NULL);
    PrintTransaction(TList);
}

// Lihat produk berdasarkan kategori
void viewProduct(TreeManager *tm, User *user, List *P, CartList *C, TQueue *T){
    int choice;
    start:
    userPrintKatalogByKategori(*P);
    printf("\n1. Beli produk\n");
    printf("2. Masukkan ke keranjang\n");
    printf("3. Kembali\n");
    printf("Masukkan pilihan anda : ");
    scanf(" %c", &choice);
    if(choice == '1'){
        buyProduct(tm, user, P, C, T);
        system("cls");    
    }else if(choice == '2'){
        AddCart(C, user->id);
    }
    else{
        goto start;
    }
}

void buyProduct(TreeManager *tm, User *user, List *P, CartList *C, TQueue *T)
{
    char tujuan[100];
    int useDomisili = 0;
    while (1) {
        clear_screen();
        print_title("PILIH ALAMAT", WIDTH);
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

    AddCart(C, user->id);
    CheckOut(C, T, P, user->id);

    TreeNode *target = find_node_by_name(tm, tujuan);
    clear_screen();
    print_title("RUTE PENGIRIMAN", WIDTH);
    print_route(target);
    system("pause");
}
