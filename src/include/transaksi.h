#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include "environment.h"

typedef struct Transaction *trsAddress;
typedef struct Transaction
{
    int id;
    int user_id;
    int cart_id;
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
void Enqueue(TQueue *TQueue, int user_id, int cart_id, int quantity, int total_price);
// void Dequeue(TQueue *TQueue);
boolean IsTrsEmpty(TQueue *TQueue);
// boolean IsFull(TQueue *TQueue);


void GenerateTransactionList(TQueue *TList);
int GetLastTransactionID(TQueue TQueue);
void AddTrsToFile(int id, int user_id, int cart_id, int quantity, int total_price);

#endif