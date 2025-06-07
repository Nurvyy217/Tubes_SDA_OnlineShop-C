#ifndef KERANJANG_H
#define KERANJANG_H

#include "environment.h"
#include "katalog.h"
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

void CreateEmptyCart(CartList *CList);
boolean IsEmpty(CartList CList);
void InsertLast(CartList *list, cartAddress newCart);
void AllocateCart(Cart **newCart);
void AddCart(CartList *CList, int user_id);
void PrintCart(CartList CList, int user_id, boolean *item);
cartAddress GetCartById(CartList CList, int item_id);

void AddToFile(int id, int user_id, int item_id, int quantity);
void RewriteCartFile(CartList CList);
void CheckOut(CartList *CList, TQueue *TList, List *P, int id_user);

int GetPrice(int item_id);
void GenerateCartList(CartList *CList);
int GetLastCartID(CartList activeList, CartList tempList);
void LoadTempCartList(CartList *CList);
void DeleteCartById(CartList *CList, int cart_id);

#endif
