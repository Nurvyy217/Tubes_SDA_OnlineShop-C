#ifndef TRANSAKSI_H
#define TRANSAKSI_H

typedef struct Transaction *address;
typedef struct Transaction
{
    int id;
    int user_id;
    int cart_id;
    
} Transaction;

typedef struct TQueue
{
    address Front;
    address Rear;
}TQueue;


#endif