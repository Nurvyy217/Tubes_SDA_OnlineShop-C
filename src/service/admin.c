#include "../include/admin.h"
#include "../include/printTemplate.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
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
    while(1){
        printf("\nMasukkan Username Admin: ");
        scanf("%s", inputUsername);
        if (strcmp(inputUsername, adminUsername) == 0) {
            break;
        }
        else{
            printf("login gagal! Username salah");
        }
    }
    while(1){
        inputPin(&inputPassword);
        if (inputPassword == adminPassword) {
            break;
        }
        else{
            printf("login gagal! pin salah");
        }
    }
    printf("\n\n\nLogin berhasil, selamat datang admin...");
    sleep(2);
    return;
}

void ProsesTransaksi(TreeManager *tm){
    print_title("PROSES TRANSAKSI", WIDTH);
    printf("\n\nTree:\n");
    print_tree_horizontal_centered(tm);
}