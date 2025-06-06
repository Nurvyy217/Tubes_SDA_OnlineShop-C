#include <stdio.h>
#include <windows.h>
#include "../include/user.h"
#include "../include/tree.h"
#include "../include/katalog.h"
#include "../include/printTemplate.h"

int main()
{
    List P;
    User user;
    TreeManager tm;
    initUserFile();
    InitTree(&tm);
    loadKatalogFromFile(&P);

    char choice;
    system("cls");
    print_center("Welcome to Alpenlishop!", WIDTH, HEIGHT);
    Sleep(3000);
    system("cls");
    print_title("1.LOGIN / 2.REGISTRASI", WIDTH);
    printf("\n\nPilihan: ");
    scanf(" %c", &choice);
    system("cls");
    if (choice == '1')
    {
        system("cls");
        loginUser(&tm, P, &user);
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