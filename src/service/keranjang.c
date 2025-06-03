#include "../include/keranjang.h"

// MAIN PROGRAM
void CreateEmpty(CartList *List){
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

void AddCart(CartList *List, int item_id, int quantity){
    Cart *newCart, *existing;
    int id;
    
    existing = CheckItemExisted(*List, item_id);

    if (existing != NULL) {
        existing->quantity += quantity;
        printf("Quantity updated for item_id %d: now %d\n", item_id, existing->quantity);

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
}

void AddToFile(int id, int item_id, int quantity){
    FILE *cartFile;
    cartFile = fopen("data/cart.txt", "a");
    if(!cartFile){
        perror("Error opening cart.txt");
    } else {
        fprintf(cartFile, "%d,%d,%d\n", id, item_id, quantity);
        printf("Keranjang ditambahkan!\n");
        fclose(cartFile);
    }
}

void RewriteCartFile(CartList List) {
    FILE *cartFile = fopen("data/cart.txt", "w");
    if (!cartFile) {
        perror("Error rewriting cart.txt");
        return;
    }

    address p = List.First;
    while (p != NULL) {
        fprintf(cartFile, "%d,%d,%d\n", p->id, p->item_id, p->quantity);
        p = p->next;
    }

    fclose(cartFile);
}

// HELPER 
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
