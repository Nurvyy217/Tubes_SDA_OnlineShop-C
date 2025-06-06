#include "transaksi.h"

void AllocateTransaction(Transaction **Trs) {
    *Trs = (Transaction*) malloc(sizeof(Transaction));
    if (*Trs == NULL) {
        printf("Gagal mengalokasi keranjang!\n");
    }
}

void CreateEmptyTransaction(TQueue *TQueue){
    TQueue->Front = NULL;
    TQueue->Rear = NULL;
}

void Enqueue(TQueue *TQueue, int user_id, int cart_id, int quantity, int total_price) {
    Transaction *newTrs;
    int id;

    AllocateTransaction(&newTrs);

    id = GetLastTransactionID(*TQueue);

    newTrs->id = id + 1;
    newTrs->user_id = user_id;
    newTrs->cart_id = cart_id;
    newTrs->quantity = quantity;
    newTrs->total_price = total_price;
    newTrs->next = NULL;

    if (IsTrsEmpty(TQueue))
    {
        TQueue->Front = newTrs;
        TQueue->Rear = newTrs;
    } else {
        TQueue->Rear->next = newTrs;
        TQueue->Rear = newTrs;
    }

    AddTrsToFile(newTrs->id, user_id, cart_id, quantity, total_price);
    printf("Berhasil melakukan checkout!\n");
}

boolean IsTrsEmpty(TQueue *TQueue){
    return (TQueue->Front == NULL && TQueue->Rear == NULL);
}



// void Dequeue(TQueue *TQueue);
// boolean IsFull(TQueue *TQueue);

// FILES
void AddTrsToFile(int id, int user_id, int cart_id, int quantity, int total_price){
    FILE *trsFile;
    trsFile = fopen("data/transaction.txt", "a");
    if(!trsFile){
        perror("Gagal membuka transaction.txt");
    } else {
        fprintf(trsFile, "%d,%d,%d,%d,%d,PENDING\n", id, user_id, cart_id, quantity, total_price);
        fclose(trsFile);
    }
}

trsAddress GetTransactionById(TQueue TQueue, int trs_id) {
    trsAddress temp = TQueue.Front;
    while (temp != NULL) {
        if (temp->id == trs_id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;  // not found
}


// HELPER

void GenerateTransactionList(TQueue *TList) {
    Transaction *newTrs;
    char line[200];
    int id, user_id, cart_id, quantity, total_price;
    char status[20];  // Assuming status is a string like "PENDING"

    // clear existing list before loading
    CreateEmptyTransaction(TList);

    FILE *file = fopen("data/transaction.txt", "r");
    if (!file) {
        perror("Error opening transaction.txt");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        // Parse a line with format: id,user_id,cart_id,quantity,total_price,status
        if (sscanf(line, "%d,%d,%d,%d,%d,%19s", &id, &user_id, &cart_id, &quantity, &total_price, status) >= 5) {
            AllocateTransaction(&newTrs);
            if (newTrs != NULL) {
                newTrs->id = id;
                newTrs->user_id = user_id;
                newTrs->cart_id = cart_id;
                newTrs->quantity = quantity;
                newTrs->total_price = total_price;
                // If you want, you can store status as well if you add it to struct Transaction
                newTrs->next = NULL;

                // Insert at the end of the queue
                if (IsTrsEmpty(TList)) {
                    TList->Front = newTrs;
                    TList->Rear = newTrs;
                } else {
                    TList->Rear->next = newTrs;
                    TList->Rear = newTrs;
                }
            }
        }
    }
    fclose(file);
}


int GetLastTransactionID(TQueue TQueue) {
    Transaction *temp = TQueue.Front;
    int lastID = 0;
    while (temp != NULL) {
        if (temp->id > lastID) {
            lastID = temp->id;
        }
        temp = temp->next;
    }
    return lastID;
}
