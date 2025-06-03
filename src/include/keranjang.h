#ifndef KERANJANG_H
#define KERANJANG_H
#include "environment.h"

typedef struct Cart *address;
typedef struct Cart {
    int id;
    int item_id;
    int quantity;
    address next;
} Cart;

typedef struct { 
    address First;
} CartList;

void CreateEmpty(CartList *List);
boolean IsEmpty(CartList List);
void InsertLast(CartList *list, address newCart);
void AllocateCart(Cart **newCart);
void GenerateCartList(CartList *List);


void AddCart(CartList *List, int item_id, int quantity);
void AddToFile(int id, int item_id, int quantity);


int GetLastCartID();
address CheckItemExisted(CartList List, int item_id);

#endif