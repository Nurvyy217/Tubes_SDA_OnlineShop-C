#include <stdio.h>
#include <windows.h>
#include "styleText.h"
#include "login.h"
#include "transitKota.h"

int main() {
    sqlite3 *userDb;
    TreeManager tm;
    
    // Initialize both databases
    initDatabase(&userDb);
    InitTree(&transitDb, &tm);
    
    char choice1, choice2;
    printf("\n\n\n\n\t\t\t\t\t\tWelcome to online shop\n");
    Sleep(3000);
    system("cls");
    printTopCenter("LOGIN / REGISTRASI\n");
    printf("\t\t\t\t\t\t\t<=====================================>\n");
    printf("\n\n\n\nPilihan: ");scanf(" %c", &choice1);
    system("cls");
    if (choice1 == '1') {
        printf("\t\t\t\t\t\t   1.ADMIN / 2. USER\n");
        printf("\t\t\t\t\t<=====================================>\n");
        printf("\n\n\n\nPilihan: ");scanf(" %c",&choice2);
        system("cls");
        if(choice2 == '1'){
            loginAdmin();
        }
        else if(choice2 == '2'){
            loginUser(&tm, userDb);
        }
    } else if (choice1 == '2') {
        system("cls");
        registrasi(userDb);
    } else {
        printf("Pilihan tidak valid. Silakan jalankan ulang program.\n");
    }
    
    // Close both database connections before exiting
    closeDatabase(userDb);
    return 0;
}