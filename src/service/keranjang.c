#include "../include/keranjang.h"
#include "../include/printTemplate.h"
#include "../include/transaksi.h"
#include "../include/keranjang.h"

// MAIN PROGRAM
void CreateEmptyCart(CartList *CList){
    CList->First = NULL;
}

boolean IsEmpty(CartList CList) {
    if (CList.First == NULL)
    {
        return true;
    } else {
        return false;
    }
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

void AddCart(CartList *CList, List P, int user_id) {
    Cart *newCart, *cartExist;
    int id, item_id, quantity;
    CartList tempCartList;
    
    GenerateCartList(&tempCartList);

    printKatalog(P);
    printf("Masukkan ID Barang: ");
    scanf("%d", &item_id);
    printf("Masukkan Jumlah Barang: ");
    scanf("%d", &quantity);

    cartExist = GetCartById(*CList, item_id);

    if (cartExist != NULL) {
        cartExist->quantity += quantity;
        printf("Berhasil mengupdate keranjang!\n");
        RewriteCartFile(*CList);
        return;
    }

    AllocateCart(&newCart);
    if (newCart == NULL) {
        printf("Gagal mengalokasi memori untuk cart baru\n");
        return;
    }

    id = GetLastCartID(*CList, tempCartList);  // ✅ Use generated tempCartList

    newCart->id = id + 1;
    newCart->user_id = user_id;
    newCart->item_id = item_id;
    newCart->quantity = quantity;
    newCart->next = NULL;

    AddToFile(newCart->id, newCart->user_id, newCart->item_id, newCart->quantity);
    InsertLast(CList, newCart);

    printf("Berhasil menambahkan ke keranjang!\n");
}

void PrintCart(CartList CList, int user_id){
    cartAddress TempNode;
    char line[100];
    int id, price, stock;
    char name[50], type[20];
    boolean found;

    TempNode = CList.First;

    printf("============================================================\n");
    printf("| ID  | Item Name      | Type           | Price      | Qty |\n");
    printf("============================================================\n");

    while (TempNode != NULL) {
        if (TempNode->user_id == user_id) {
            FILE *katalog = fopen("data/katalog.txt", "r");
            if (katalog == NULL) {
                perror("Failed to open katalog.txt");
                return;
            }

            found = false;

            while (fgets(line, sizeof(line), katalog)) {
                if (strncmp(line, "Jenis:", 6) == 0) continue;  // Skip type headers
                if (sscanf(line, "%d; %[^;]; %[^;]; %d; %d", &id, name, type, &price, &stock) == 5){
                    if (id == TempNode->item_id) {
                        found = true;
                        printf("| %-3d | %-14s | %-14s | %-10d | %-4d|\n",
                            TempNode->id, name, type, price, TempNode->quantity);
                        break;
                    }
                }
            }
            if (!found) {
                printf("| %-3d | %-14s | %-9s | %-11s | %-4d|\n",
                    TempNode->id, "[UNKNOWN]", "-", "-", TempNode->quantity);
            }

            fclose(katalog);
        }
        TempNode = TempNode->next;
    }

    printf("============================================================\n");
}

void CheckOut(CartList *CList, TQueue *TList, List *P, User *user)
{
    cartAddress cartNode;
    int cart_id, total_price;
    char line[100], productName[100], name[50], type[50], payVar;
    int id, price, stock;
    bool found = false;

    if (CountTransactionByUser(*TList, user->id) >= 3) {
        printf("Transaksi penuh! Mohon menunggu proses transaksi.\n");
        return;
    }

    print_title("CHECKOUT KERANJANG", WIDTH);
    PrintCart(*CList, user->id);
    printf("\nMasukkan ID Keranjang: ");
    scanf("%d", &cart_id);

    total_price = 0;
    cartNode = GetCartById(*CList, cart_id);

    if (cartNode == NULL) {
        printf("Keranjang dengan ID %d tidak ditemukan.\n", cart_id);
        return;
    }

    // Cari nama produk dari item_id (cartNode->item_id)
    FILE *katalog = fopen(FILE_KATALOG, "r");
    if (katalog == NULL) {
        perror("Gagal membuka file katalog");
        return;
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
        return;
    }

    total_price = cartNode->quantity * GetPrice(cartNode->item_id);

    minusStokProduk(P, cartNode->quantity, productName);
    saveKatalogToFile(*P);

    SaveTransactionToFile(user->id, cart_id, cartNode->item_id, cartNode->quantity, total_price);
    DeleteCartById(CList, cart_id);

    printf("Checkout berhasil!\n\n");

    printf("Ingin melakukan pembayaran? [y/n] ");
    scanf(" %c", &payVar);
    if (payVar == 'y') {
        PayTransaction(user);  // ✅ Just pass the pointer
    } else {
        printf("Kembali..\n");
        sleep(2);
        return;
    }
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

    // clear existing list before loading
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

    // Clear existing list
    CreateEmptyCart(CList);

    FILE *file = fopen("data/cart_history.txt", "r");
    if (!file) {
        perror("Gagal membuka cart_temp.txt");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        // Skip empty or malformed lines
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

    // Check active carts
    while (temp != NULL) {
        if (temp->id > lastID) {
            lastID = temp->id;
        }
        temp = temp->next;
    }

    // Check temp carts (e.g., checked-out carts)
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
