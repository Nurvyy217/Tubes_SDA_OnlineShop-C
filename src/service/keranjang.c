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

void InsertLast(CartList *list, address newCart) {
    if (list->First == NULL) {
        list->First = newCart;
    } else {
        address p = list->First;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newCart;
    }
}

void AddCart(CartList *List, int item_id, int quantity){
    Cart *newCart, *existing;
    int id;
    
    existing = CheckItemExisted(*List, item_id);

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

    id = GetLastCartID();

    newCart->id = id + 1; 
    newCart->item_id = item_id;
    newCart->quantity = quantity;
    newCart->next = NULL;

    AddToFile(newCart->id, newCart->item_id, newCart->quantity);
    InsertLast(List, newCart);
    printf("Berhasil menambahkan keranjang!\n");
}

void PrintCart(CartList List){
    CartList TempList;
    address TempNode;
    char line[100];
    int id, price, stock;
    char name[50], type[20];
    boolean found;

    CreateEmptyCart(&TempList);
    GenerateCartList(&TempList);

    TempNode = TempList.First;
    found = false;

    printf("============================================================\n");
    printf("| No  | Item Name      | Type           | Price      | Qty |\n");
    printf("============================================================\n");

    int no = 1;
    while (TempNode != NULL) {
        FILE *katalog = fopen("data/katalog.txt", "r");
        if (katalog == NULL) {
            perror("Failed to open katalog.txt");
            return;
        }

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
        TempNode = TempNode->next;
        no++;
    }

    printf("============================================================\n");
}

void CheckOut(CartList *List){
    int id;

    print_title("CHECKOUT KERANJANG", WIDTH);
    PrintCart(*List);
    printf("\nMasukan no keranjang: ");
    scanf("%d", &id);
    
}

// FILES
void AddToFile(int id, int item_id, int quantity){
    FILE *cartFile;
    cartFile = fopen("data/cart.txt", "a");
    if(!cartFile){
        perror("Error opening cart.txt");
    } else {
        fprintf(cartFile, "%d,%d,%d\n", id, item_id, quantity);
        fclose(cartFile);
    }
}

void RewriteCartFile(CartList List) {
    FILE *cartFile = fopen("data/cart.txt", "w");
    address temp; 
    if (!cartFile) {
        perror("Error rewriting cart.txt");
        return;
    }

    temp = List.First;
    while (temp != NULL) {
        fprintf(cartFile, "%d,%d,%d\n", temp->id, temp->item_id, temp->quantity);
        temp = temp->next;
    }
    fclose(cartFile);
}

// HELPER 
void GenerateCartList(CartList *List) {
    address newCart;
    char line[100];
    int id, item_id, quantity;
    
    FILE *file = fopen("data/cart.txt", "r");
    if (!file) {
        perror("Error opening cart.txt");
        return;
    }
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%d,%d", &id, &item_id, &quantity) == 3) {
            AllocateCart(&newCart);
            if (newCart != NULL) {
                newCart->id = id;
                newCart->item_id = item_id;
                newCart->quantity = quantity;
                newCart->next = NULL;
                InsertLast(List, newCart);
            }
        }
    }
    fclose(file);
}

int GetLastCartID() {
    int id, item_id, qty;
    int lastID = 0;
    char line[100];

    FILE *cartFile = fopen("data/cart.txt", "r");
    if (!cartFile) return 0;

    while (fgets(line, sizeof(line), cartFile)) {
        if (sscanf(line, "%d,%d,%d", &id, &item_id, &qty) == 3) {
            lastID = id;
        }
    }

    fclose(cartFile);
    return lastID;
}

address CheckItemExisted(CartList List, int item_id) {
    address temp = List.First;
    while (temp != NULL) {
        if (temp->item_id == item_id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
