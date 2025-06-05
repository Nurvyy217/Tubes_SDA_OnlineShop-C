#include "../include/admin.h"
#include "../include/printTemplate.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include "../include/styleText.h"
#include "../include/tree.h"
#include "../include/katalog.h"

void loginAdmin(TreeManager *tm) {
    char adminUsername[50];
    char inputUsername[50];
    int adminPassword;
    int inputPassword;
    int isAdminValid = 0;

    strcpy(adminUsername, "admin");
    adminPassword = 1234;
    system("cls");
    print_title("LOGIN ADMIN", WIDTH);
    printf("\nMasukkan Username Admin: ");
    scanf("%s", inputUsername);
    inputPin(&inputPassword);

    if (strcmp(inputUsername, adminUsername) == 0 && inputPassword == adminPassword) {
        isAdminValid = 1;
    }

    if (isAdminValid) {
        printf("\n\n\nLogin Admin berhasil. Selamat datang, Admin.\n");
        Sleep(2000);
        menuAdmin(tm);
    } else {
        printf("\nLogin Admin gagal! Username atau Password salah.\n");
    }
}

void menuAdmin(TreeManager *tm) {
    int choice;
    for(;;){
        system("cls");
        print_title("MENU ADMIN", WIDTH);
        printf("\n1. Proses Transaksi\n");
        printf("2. Kelola Katalog\n3. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf(" %d", &choice);
        switch (choice) {
        case 1:
            ProsesTransaksi(tm);
            system("pause");
            break;
        case 2:
            adminKatalog();
            break;
        case 3:
            return;
        default:
            printf("Pilihan tidak valid.\n");
            break;
        }
    }

}

void ProsesTransaksi(TreeManager *tm){
    print_title("PROSES TRANSAKSI", WIDTH);
    printf("\n\nTree:\n");
    print_tree_horizontal_centered(tm);
}