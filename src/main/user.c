#include <stdio.h>
#include <windows.h>
#include "../include/user.h"
#include "../include/tree.h"
#include "../include/katalog.h"
#include "../include/printTemplate.h"
#include "../include/keranjang.h"
#include "../include/transaksi.h"

int main()
{
    // Variable Declaration
    List P;
    User user;
    TreeManager tm;
    CartList C;
    TQueue T;
    char choice;
    
    // Initialization Module ADT
    initUserFile();
    InitTree(&tm);
    loadKatalogFromFile(&P);
    GenerateCartList(&C);
    GenerateTransactionList(&T);

    // PROGRAM
    system("cls");
    print_center("Welcome to Alpenlishop!", WIDTH, HEIGHT);
    Sleep(3000);
    system("cls");
    print_title("1.LOGIN / 2.REGISTRASI", WIDTH);
    printf("\nPilihan: ");
    scanf(" %c", &choice);
    system("cls");
    if (choice == '1')
    {
        system("cls");
        loginUser(&tm, &P, &user, &C, &T);
    }
    else if (choice == '2')
    {
        system("cls");
        registration();
    }
    else
    {
        printf("Pilihan tidak valid. Silakan jalankan ulang program.\n");
    }

    return 0;
}