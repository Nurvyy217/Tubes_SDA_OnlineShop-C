#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include "environment.h"
#include "user.h"
#include "katalog.h"
#include "printTemplate.h"

#define MAX_TRANSACTION 3
typedef struct Transaction *trsAddress;
typedef struct Transaction
{
    int id;
    int user_id;
    int cart_id;
    int item_id;
    int quantity;
    int total_price;
    char status[10];
    trsAddress next;
} Transaction;

typedef struct TQueue
{
    trsAddress Front;
    trsAddress Rear;
}TQueue;

void AllocateTransaction(Transaction **Trs);
void CreateEmptyTransaction(TQueue *TQueue);
void SaveTransactionToFile(int user_id, int cart_id, int item_id, int quantity, int total_price);
void Dequeue(TQueue *TList);
boolean IsTrsEmpty(TQueue *TQueue);
int CountTransactionByUser(TQueue Q, int user_id);
void PayTransaction(User *userLogin);
void PrintTransaction(TQueue TList);

void UpdateUserFile(User *userLogin);
void GenerateTransactionList(TQueue *TList);
int GetLastTransactionID(TQueue TQueue);

#endif