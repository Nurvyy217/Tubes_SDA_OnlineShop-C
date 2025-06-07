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
    bool valid;
    boolean item;
    char pilihan;
    
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
        loginUser(&user);
                do
                {
                system("cls");
                print_title("MENU USER", WIDTH);
                printf("\n1. Top Up Saldo\n");
                printf("2. Lihat/Beli Produk\n");
                printf("3. Info Pesanan\n");
                printf("4. Keranjang saya\n");
                printf("5. Bayar Transaksi\n");
                printf("6. Keluar\n");
                printf("Masukkan pilihan: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    topUp(&user);
                    system("pause");
                    break;
                case 2:
                    viewProduct(&tm, &user, &P, &C, &T);
                    system("pause");
                    break;
                case 3:
                    orderInformation(&user);
                    system("pause");
                    break;
                case 4:
                    clear_screen();
                    print_title("KERANJANG", WIDTH);
                    PrintCart(C, user.id, &item);
                    if(item){
                        printf("Checkout Keranjang: [y/n]: ");
                        scanf(" %c", &pilihan);
                        if (pilihan == 'y')
                        {
                            CheckOut(&C, &T, &P, user.id);
                        }
                    }
                    system("pause");
                    break;
                case 5:
                    PayTransaction(user.id);
                    system("pause");
                    break;
                case 6:
                    printf("Keluar dari program!\n");
                    break;
                default:
                    printf("Pilihan tidak valid\n");
                    break;
                }
            } while (choice != 6);
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