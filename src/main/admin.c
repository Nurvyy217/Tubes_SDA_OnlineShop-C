#include "../include/printTemplate.h"
#include "../include/admin.h"
#include <windows.h>
#include "../include/printTemplate.h"
#include "../include/user.h"
#include "../include/tree.h"
#include "../include/environment.h"

int main()
{
    TreeManager tm;
    int choice;
    print_center("SELAMAT DATANG ADMIN", WIDTH, HEIGHT);
    sleep(2);
    clear_screen();
    InitTree(&tm);

    loginAdmin(); 
    for(;;){
        system("cls");
        print_title("MENU ADMIN", WIDTH);
        printf("\n1. Proses Transaksi\n");
        printf("2. Kelola Katalog\n3. keluar\n");
        printf("Masukkan pilihan: ");
        scanf(" %d", &choice);
        switch (choice) {
        case 1:
            ProsesTransaksi(&tm);
            system("pause");
            break;
        case 2:
            adminKatalog();
            break;
        case 3:
            printf("\n\nData telah di update....\n");
            sleep(2);
            printf("Sampai jumpa admin :)");
            sleep(2);
            return 0;
        default:
            printf("Pilihan tidak valid.\n");
            break;
        }
    }
    
}