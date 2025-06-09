#include <stdio.h>
#include <windows.h>
#include "../include/user.h"
#include "../include/tree.h"
#include "../include/katalog.h"
#include "../include/printTemplate.h"
#include "../include/keranjang.h"
#include "../include/transaksi.h"
#include "../include/stack.h"

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
                    int payResult = PayTransaction(user.id);
                    if (payResult == 1) {
                        // Setelah pembayaran sukses, tawarkan update rute
                        char updateRoute;
                        printf("Ingin update rute pengiriman? [y/n]: ");
                        scanf(" %c", &updateRoute);
                        if (updateRoute == 'y' || updateRoute == 'Y') {
                            int trans_id;
                            char tujuan[100], new_route[200];
                            TreeManager tmUpdate;
                            InitTree(&tmUpdate);

                            printf("Masukkan ID transaksi yang ingin diupdate rutenya: ");
                            scanf("%d", &trans_id);
                            printf("Masukkan kota tujuan baru: ");
                            scanf("%s", tujuan);

                            addressTree target = find_node_by_name(&tmUpdate, tujuan);
                            if (target) {
                                get_route_string(target, new_route);

                                // Ambil data transaksi lama
                                FILE *f = fopen("data/transaction.txt", "r");
                                Transaction oldTrx = {0};
                                char line[300];
                                int found = 0;
                                while (f && fgets(line, sizeof(line), f)) {
                                    int n = sscanf(line, "%d,%d,%d,%d,%d,%d,%19[^,],%199[^\n]",
                                        &oldTrx.id, &oldTrx.user_id, &oldTrx.cart_id, &oldTrx.item_id,
                                        &oldTrx.quantity, &oldTrx.total_price, oldTrx.status, oldTrx.route);
                                    if (n == 8 && oldTrx.id == trans_id && oldTrx.user_id == user.id) {
                                        found = 1;
                                        break;
                                    }
                                }
                                if (f) fclose(f);

                                if (found) {
                                    SaveOrUpdateTransaction(
                                        "update",
                                        trans_id,
                                        oldTrx.user_id,
                                        oldTrx.cart_id,
                                        oldTrx.item_id,
                                        oldTrx.quantity,
                                        oldTrx.total_price,
                                        "PAID",
                                        new_route
                                    );
                                    printf("Rute transaksi berhasil diupdate!\n");
                                } else {
                                    printf("Transaksi tidak ditemukan.\n");
                                }
                            } else {
                                printf("Kota tujuan tidak ditemukan di tree. Rute tidak diupdate.\n");
                            }
                        }
                    }
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