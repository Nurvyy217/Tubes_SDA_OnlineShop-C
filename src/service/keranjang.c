#include "../include/keranjang.h"
#include "../include/printTemplate.h"

// MAIN PROGRAM
void CreateEmptyCart(CartList *List){
    List->First = NULL;
}

boolean IsEmpty(CartList List) {
    if (List.First == NULL)
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

void InsertLast(CartList *list, cartAddress newCart) {
    if (list->First == NULL) {
        list->First = newCart;
    } else {
        cartAddress p = list->First;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newCart;
    }
}

void AddCart(CartList *List, int user_id, int item_id, int quantity){
    Cart *newCart, *existing;
    int id;

    existing = GetCartById(*List, item_id);

    if (existing != NULL) {
        existing->quantity += quantity;
        printf("Berhasil mengupdate keranjang!\n");

        RewriteCartFile(*List);
        return;
    }

    AllocateCart(&newCart);
    if(!newCart) {
        printf("Gagal mengalokasi keranjang...\n");
        return;
    }

    id = GetLastCartID(*List);

    newCart->id = id + 1; 
    newCart->user_id = user_id;
    newCart->item_id = item_id;
    newCart->quantity = quantity;
    newCart->next = NULL;

    AddToFile(newCart->id, newCart->user_id ,newCart->item_id, newCart->quantity);
    InsertLast(List, newCart);
    printf("Berhasil menambahkan keranjang!\n");
}

void PrintCart(CartList List, int user_id){
    cartAddress TempNode;
    char line[100];
    int id, price, stock;
    char name[50], type[20];
    boolean found;

    TempNode = List.First;

    printf("============================================================\n");
    printf("| No  | Item Name      | Type           | Price      | Qty |\n");
    printf("============================================================\n");

    int no = 1;
    while (TempNode != NULL) {
        if (TempNode->user_id == user_id) {
            FILE *katalog = fopen("data/katalog.txt", "r");
            if (katalog == NULL) {
                perror("Failed to open katalog.txt");
                return;
            }

            found = false;

            while (fgets(line, sizeof(line), katalog)) {
                if (sscanf(line, "%d,%[^,],%[^,],%d,%d", &id, name, type, &price, &stock) == 5) {
                    if (id == TempNode->item_id) {
                        found = true;
                        printf("| %-3d | %-14s | %-14s | %-10d | %-4d|\n",
                            no, name, type, price, TempNode->quantity);
                        break;
                    }
                }
            }
            if (!found) {
                printf("| %-3d | %-14s | %-9s | %-11s | %-4d|\n",
                    no, "[UNKNOWN]", "-", "-", TempNode->quantity);
            }

            fclose(katalog);
            no++;
        }
        TempNode = TempNode->next;
    }

    printf("============================================================\n");
}

void CheckOut(CartList *List, TQueue *TList){
    Transaction *newTrs;
    cartAddress trsNode;
    int user_id, cart_id, total_price;

    print_title("CHECKOUT KERANJANG", WIDTH);
    PrintCart(*List, 1);
    printf("\nMasukan no keranjang: ");
    scanf("%d", &cart_id);
    
    total_price = 0;
    user_id = 1; // Change to user_id from login
    trsNode = GetCartById(*List, cart_id);

    if (trsNode == NULL) {
        printf("Keranjang dengan ID %d tidak ditemukan.\n", cart_id);
        return;
    }

    total_price = trsNode->quantity * GetPrice(trsNode->item_id);

    Enqueue(TList, user_id, cart_id, trsNode->quantity, total_price);
    DeleteCartById(List, cart_id);
}

cartAddress GetCartById(CartList List, int item_id) {
    cartAddress temp = List.First;
    while (temp != NULL) {
        if (temp->item_id == item_id) {
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

void RewriteCartFile(CartList List) {
    FILE *cartFile = fopen("data/cart.txt", "w");
    cartAddress temp; 
    if (!cartFile) {
        perror("Error rewriting cart.txt");
        return;
    }

    temp = List.First;
    while (temp != NULL) {
    fprintf(cartFile, "%d,%d,%d,%d\n", temp->id, temp->user_id, temp->item_id, temp->quantity);
    temp = temp->next;
    }
    fclose(cartFile);
}

// HELPER 
void GenerateCartList(CartList *List) {
    cartAddress newCart;
    char line[100];
    int id, user_id, item_id, quantity;

    // clear existing list before loading
    CreateEmptyCart(List);

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
                InsertLast(List, newCart);
            }
        }
    }
    fclose(file);
}

int GetLastCartID(CartList List) {
    cartAddress temp = List.First;
    int lastID = 0;
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
        if (sscanf(line, "%d,%[^,],%[^,],%d,%d", &id, name, type, &price, &stock) == 5) {
            if (id == item_id) {
                fclose(katalog);
                return price;
            }
        }
    }
    fclose(katalog);
    return 0;
}

void DeleteCartById(CartList *List, int cart_id) {
    cartAddress current = List->First;
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
                List->First = current->next;
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
