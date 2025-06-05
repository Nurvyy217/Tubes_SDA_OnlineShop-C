#include <stdio.h>
#include <windows.h>
#include "../include/styleText.h"
#include "../include/user.h"
#include "../include/tree.h"
#include "../include/katalog.h"

int main()
{
    List P;
    TreeManager tm;
    initUserFile();
    InitTree(&tm);
    loadKatalogFromFile(&P);

    char choice;
    system("cls");
    printf("\n\n\n\n\t\t\t\t\t\tWelcome to online shop\n");
    Sleep(3000);
    system("cls");
    printf("\t\t\t\t\t\t\t1.LOGIN / 2.REGISTRASI\n");
    printf("\t\t\t\t\t\t<==================================>\n");
    printf("\n\n\n\nPilihan: ");
    scanf(" %c", &choice);
    system("cls");
    if (choice == '1')
    {
        system("cls");
        loginUser(&tm, P);
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