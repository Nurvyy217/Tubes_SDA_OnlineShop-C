#include "../include/keranjang.h"
#include "../include/printTemplate.h"
#include "../include/transaksi.h"
#include "../include/tree.h"
#include "../include/stack.h"

// MAIN PROGRAM
void CreateEmptyCart(CartList *CList){
    CList->First = NULL;
}

void AllocateCart(Cart **newCart){
    *newCart = (Cart*) malloc(sizeof(Cart));
    if (*newCart == NULL) {
        printf("Gagal mengalokasi keranjang!\n");
    } else {
        (*newCart)->next = NULL;
    }
}

void InsertLast(CartList *CList, cartAddress newCart) {
    if (CList->First == NULL) {
        CList->First = newCart;
    } else {
        cartAddress p = CList->First;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newCart;
    }
}

void AddCart(CartList *CList, int user_id) {
    List P;
    Cart *newCart, *cartExist;
    int id, item_id, quantity;
    CartList tempCartList;

    LoadTempCartList(&tempCartList);
    loadKatalogFromFile(&P);

    clear_screen();
    print_title("TAMBAH KERANJANG", WIDTH);
    printKatalog(P);
    printf("\nMasukkan ID Barang: ");
    scanf("%d", &item_id);

    // Cek apakah item_id ada di dalam katalog
    addressJenis jenisPtr = P.First;
    bool found = false;

    while (jenisPtr != NULL && !found) {
        addressProduk produkPtr = jenisPtr->produkJenis;
        while (produkPtr != NULL) {
            if (produkPtr->id == item_id) {
                found = true;
                break;
            }
            produkPtr = produkPtr->next;
        }
        jenisPtr = jenisPtr->next_jenis;
    }

    if (!found) {
        printf("Item tidak ada di dalam list.\n");
        return;
    }

    printf("Masukkan Jumlah Barang: ");
    scanf("%d", &quantity);

    cartExist = GetCartById(*CList, item_id);

    if (cartExist != NULL) {
        cartExist->quantity += quantity;
        printf("Berhasil mengupdate keranjang!\n\n");
        RewriteCartFile(*CList);
        return;
    }

    AllocateCart(&newCart);
    if (newCart == NULL) {
        printf("Gagal mengalokasi memori untuk cart baru\n");
        return;
    }

    id = GetLastCartID(*CList, tempCartList);

    newCart->id = id + 1;
    newCart->user_id = user_id;
    newCart->item_id = item_id;
    newCart->quantity = quantity;
    newCart->next = NULL;

    AddToFile(newCart->id, newCart->user_id, newCart->item_id, newCart->quantity);
    InsertLast(CList, newCart);

    printf("Berhasil menambahkan ke keranjang!\n");
}

void PrintCart(CartList CList, int user_id, boolean *item)
{
    cartAddress TempNode = CList.First;
    char line[100];
    int id, price, stock;
    char name[50], type[20];
    boolean found;

    printf("============================================================\n");
    printf("| ID  | Item Name      | Type           | Price      | Qty |\n");
    printf("============================================================\n");

    *item = false;
    while (TempNode != NULL) {
        if (TempNode->user_id == user_id) {
            *item = true;
            FILE *katalog = fopen("data/katalog.txt", "r");
            if (!katalog) {
                perror("Failed to open katalog.txt");
                return;
            }

            found = false;
            while (fgets(line, sizeof(line), katalog)) {
                if (strncmp(line, "Jenis:", 6) == 0) continue;
                if (sscanf(line, "%d; %[^;]; %[^;]; %d; %d",
                           &id, name, type, &price, &stock) == 5)
                {
                    if (id == TempNode->item_id) {
                        found = true;
                        printf("| %-3d | %-14s | %-14s | %-10d | %-4d|\n",
                               TempNode->id, name, type, price, TempNode->quantity);
                        break;
                    }
                }
            }
            if (!found) {
                printf("| %-3d | %-14s | %-14s | %-10s | %-4d|\n",
                       TempNode->id, "[UNKNOWN]", "-", "-", TempNode->quantity);
            }
            fclose(katalog);
        }
        TempNode = TempNode->next;
    }

        if (!(*item)) {
        printf("|                    Keranjang kosong                      |\n");
    }

    printf("============================================================\n");
    return;
}

int CheckOut(CartList *CList, TQueue *TList, List *P, int id_user)
{
    cartAddress cartNode;
    int cart_id, total_price;
    char line[100], productName[100], name[50], type[50], payVar;
    int id, price, stock;
    bool found = false;
    boolean item;

    GenerateTransactionList(TList);

    if (CountTransactionByUser(*TList, id_user) >= 5) {
        printf("Transaksi penuh! Mohon menunggu proses transaksi.\n");
        system("pause");
        return -1;
    }

    clear_screen();
    print_title("CHECKOUT KERANJANG", WIDTH);
    PrintCart(*CList, id_user, &item);
    printf("\nMasukkan ID Keranjang: ");
    scanf("%d", &cart_id);

    total_price = 0;
    cartNode = GetCartById(*CList, cart_id);

    if (cartNode == NULL) {
        printf("Keranjang dengan ID %d tidak ditemukan.\n", cart_id);
        return -1;
    }

    FILE *katalog = fopen(FILE_KATALOG, "r");
    if (katalog == NULL) {
        perror("Gagal membuka file katalog");
        return -1;
    }

    while (fgets(line, sizeof(line), katalog)) {
        if (strncmp(line, "Jenis:", 6) == 0) continue;
        if (sscanf(line, "%d; %[^;]; %[^;]; %d; %d", &id, name, type, &price, &stock) == 5) {
            if (id == cartNode->item_id) {
                strcpy(productName, name);
                found = true;
                break;
            }
        }
    }
    fclose(katalog);

    if (!found) {
        printf("Produk tidak ditemukan di katalog.\n");
        return -1;
    }

    total_price = cartNode->quantity * GetPrice(cartNode->item_id);

    minusStokProduk(P, cartNode->quantity, productName);
    saveKatalogToFile(*P);

    int trans_id = SaveOrUpdateTransaction("baru", 0, id_user, cart_id, cartNode->item_id, cartNode->quantity, total_price, "PENDING", "RUTE KOSONG");

    DeleteCartById(CList, cart_id);
    printf("Checkout berhasil!\n\n");

    printf("Ingin melakukan pembayaran? [y/n] ");
    scanf(" %c", &payVar);
    if (payVar == 'y') {
        TreeManager tm;
        InitTree(&tm);
        char tujuan[100];

        // Pilih alamat tujuan
        while (1) {
            clear_screen();
            print_title("PILIH ALAMAT", WIDTH);
            // Ambil domisili user dari file user.txt
            FILE *fuser = fopen("data/user.txt", "r");
            char uname[50], domisili[100];
            int uid, upin, usaldo;
            while (fgets(line, sizeof(line), fuser)) {
                if (sscanf(line, "%d,%49[^,],%d,%d,%99[^\n]", &uid, uname, &upin, &usaldo, domisili) == 5) {
                    if (uid == id_user) {
                        break;
                    }
                }
            }
            fclose(fuser);

            printf("Kota tujuan: %s\n", domisili);
            printf("Kirim ke alamat ini? (y/n): ");
            char yn[10];
            scanf("%s", yn);
            if (yn[0] == 'y' || yn[0] == 'Y') {
                strcpy(tujuan, domisili);
                break;
            } else {
                while (1) {
                    printf("Masukkan nama kota tujuan (harus berada di Jawa Barat atau Jabodetabek): ");
                    scanf("%s", tujuan);
                    if (find_node_by_name(&tm, tujuan)) {
                        break;
                    } else {
                        printf("Kota yang diinputkan tidak ditemukan.\n");
                        printf("Kota tujuan harus berada di daerah Jawa Barat dan Jabodetabek.\n");
                        showCityList(&tm);
                    }
                }
                break;
            }
        }

        // Proses pembayaran
        PayTransaction(id_user);

        // Update rute transaksi
        addressTree target = find_node_by_name(&tm, tujuan);
        if (target) {
            printf("Rute pengiriman: ");
            print_route(target);

            char routeStr[1000];
            get_route_string(target, routeStr);

            SaveOrUpdateTransaction("update", trans_id, id_user, cart_id, cartNode->item_id, cartNode->quantity, total_price, "PAID", routeStr);
        } else {
            printf("Kota tujuan tidak ditemukan di tree. Rute tetap KOSONG.\n");
            SaveOrUpdateTransaction("update", trans_id, id_user, cart_id, cartNode->item_id, cartNode->quantity, total_price, "PAID", "RUTE KOSONG");
        }
    } else {
        printf("Kembali..\n");
        sleep(2);
    }

    return trans_id;
}


cartAddress GetCartById(CartList CList, int cart_id) {
    cartAddress temp = CList.First;
    while (temp != NULL) {
        if (temp->id == cart_id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// FILES
void AddToFile(int id, int user_id, int item_id, int quantity){
    FILE *cartFile;
    cartFile = fopen("data/cart.txt", "a");
    if(!cartFile){
        perror("Error opening cart.txt");
    } else {
        fprintf(cartFile, "%d,%d,%d,%d\n", id, user_id, item_id, quantity);
        fclose(cartFile);
    }
}

void RewriteCartFile(CartList CList) {
    FILE *cartFile = fopen("data/cart.txt", "w");
    cartAddress temp; 
    if (!cartFile) {
        perror("Error rewriting cart.txt");
        return;
    }

    temp = CList.First;
    while (temp != NULL) {
    fprintf(cartFile, "%d,%d,%d,%d\n", temp->id, temp->user_id, temp->item_id, temp->quantity);
    temp = temp->next;
    }
    fclose(cartFile);
}

// HELPER 
void GenerateCartList(CartList *CList) {
    cartAddress newCart;
    char line[100];
    int id, user_id, item_id, quantity;

    CreateEmptyCart(CList);

    FILE *file = fopen("data/cart.txt", "r");
    if (!file) {
        perror("Error opening cart.txt");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%d,%d,%d", &id, &user_id, &item_id, &quantity) == 4) {
            AllocateCart(&newCart);
            if (newCart != NULL) {
                newCart->id = id;
                newCart->user_id = user_id;
                newCart->item_id = item_id;
                newCart->quantity = quantity;
                newCart->next = NULL;
                InsertLast(CList, newCart);
            }
        }
    }
    fclose(file);
}

void LoadTempCartList(CartList *CList) {
    cartAddress newCart;
    char line[100];
    int id, user_id, item_id, quantity;

    CreateEmptyCart(CList);

    FILE *file = fopen("data/cart_history.txt", "r");
    if (!file) {
        perror("Gagal membuka cart_temp.txt");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%d,%d,%d", &id, &user_id, &item_id, &quantity) != 4) {
            continue;
        }

        AllocateCart(&newCart);
        if (newCart == NULL) {
            printf("Gagal mengalokasi memori untuk cart sementara\n");
            continue;
        }

        newCart->id = id;
        newCart->user_id = user_id;
        newCart->item_id = item_id;
        newCart->quantity = quantity;
        newCart->next = NULL;

        InsertLast(CList, newCart);
    }

    fclose(file);
}

int GetLastCartID(CartList activeList, CartList tempList) {
    cartAddress temp = activeList.First;
    int lastID = 0;

    while (temp != NULL) {
        if (temp->id > lastID) {
            lastID = temp->id;
        }
        temp = temp->next;
    }

    temp = tempList.First;
    while (temp != NULL) {
        if (temp->id > lastID) {
            lastID = temp->id;
        }
        temp = temp->next;
    }

    return lastID;
}


int GetPrice(int item_id) {
    FILE *katalog = fopen("data/katalog.txt", "r");
    if (!katalog) {
        perror("Failed to open katalog.txt");
        return 0;
    }
    char line[100];
    int id, price, stock;
    char name[50], type[20];
    while (fgets(line, sizeof(line), katalog)) {
        if (strncmp(line, "Jenis:", 6) == 0) continue;
        if (sscanf(line, "%d; %[^;]; %[^;]; %d; %d", &id, name, type, &price, &stock) == 5){
            if (id == item_id) {
                fclose(katalog);
                return price;
            }
        }
    }
    fclose(katalog);
    return 0;
}

void DeleteCartById(CartList *CList, int cart_id) {
    cartAddress current = CList->First;
    cartAddress prev = NULL;

    FILE *src = fopen("data/cart.txt", "r");
    FILE *temp = fopen("data/cart_temp.txt", "a");
    FILE *history = fopen("data/cart_history.txt", "a");

    if (!src || !temp || !history) {
        perror("Gagal membuka file untuk penghapusan cart");
        if (src) fclose(src);
        if (temp) fclose(temp);
        if (history) fclose(history);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), src)) {
        int id, user_id, item_id, quantity;
        if (sscanf(line, "%d,%d,%d,%d", &id, &user_id, &item_id, &quantity) == 4) {
            if (id == cart_id) {
                fprintf(history, "%d,%d,%d,%d\n", id, user_id, item_id, quantity);
            } else {
                fputs(line, temp);
            }
        }
    }

    fclose(src);
    fclose(temp);
    fclose(history);

    remove("data/cart.txt");
    rename("data/cart_temp.txt", "data/cart.txt");

    while (current != NULL) {
        if (current->id == cart_id) {
            if (prev == NULL) {
                CList->First = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
