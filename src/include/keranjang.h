#ifndef KERANJANG_H
#define KERANJANG_H
#include "environment.h"
#include "transaksi.h"

typedef struct Cart *cartAddress;
typedef struct Cart {
    int id;
    int user_id;
    int item_id;
    int quantity;
    cartAddress next;
} Cart;

typedef struct { 
    cartAddress First;
} CartList;

void CreateEmptyCart(CartList *List);
boolean IsEmpty(CartList List);
void InsertLast(CartList *list, cartAddress newCart);
void AllocateCart(Cart **newCart);
void AddCart(CartList *List, int user_id, int item_id, int quantity);
void PrintCart(CartList List, int user_id);
cartAddress GetCartById(CartList List, int item_id);

void AddToFile(int id, int user_id, int item_id, int quantity);
void RewriteCartFile(CartList List);
void CheckOut(CartList *List, TQueue *TList);

int GetPrice(int item_id);
void GenerateCartList(CartList *List);
int GetLastCartID(CartList List);
void DeleteCartById(CartList *List, int cart_id);

#endif