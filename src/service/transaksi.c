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

void PrintTransaction(TQueue TList) {
    Transaction *current = TList.Front;

    if (current == NULL) {
        printf("Tidak ada transaksi yang sudah dibayar.\n");
        return;
    }

    printf("==================================================================\n");
    printf("| ID  | User ID | Cart ID | Item ID | Qty | Total Price | Status |\n");
    printf("==================================================================\n");

    while (current != NULL) {
        printf("| %-3d | %-7d | %-7d | %-7d | %-3d | %-11d | %-6s |\n",
               current->id,
               current->user_id,
               current->cart_id,
               current->item_id,
               current->quantity,
               current->total_price,
               current->status);
        current = current->next;
    }

    printf("==================================================================\n");
}

void PayTransaction(User *userLogin) {
    boolean trsFound;
    FILE *file = fopen("data/transaction.txt", "r");
    if (!file) {
        perror("Gagal membuka file transaksi");
        return;
    }

    Transaction transaksi[100];
    int count = 0;

    print_title("BAYAR TRANSAKSI", WIDTH);

    // Baca semua transaksi
    printf("=====================================================\n");
    printf("| ID  | Item ID | Qty | Total (Rp)     | Status     |\n");
    printf("=====================================================\n");

    while (fscanf(file, "%d,%d,%d,%d,%d,%d,%s\n",
        &transaksi[count].id, &transaksi[count].user_id,
        &transaksi[count].cart_id, &transaksi[count].item_id,
        &transaksi[count].quantity, &transaksi[count].total_price,
        transaksi[count].status) == 7)
    {
        if (transaksi[count].user_id == userLogin->id &&
            strcmp(transaksi[count].status, "PENDING") == 0) {

            printf("| %-3d | %-7d | %-3d | %-14d | %-9s  |\n",
                transaksi[count].id,
                transaksi[count].item_id,
                transaksi[count].quantity,
                transaksi[count].total_price,
                transaksi[count].status);

            trsFound = true;
        }
        count++;
    }
    printf("=====================================================\n");

    fclose(file);

    if (!trsFound) {
        printf("\nTidak ada transaksi yang bisa dibayar.\n");
        return;
    }

    if (count == 0) {
        printf("Tidak ada transaksi.\n");
        return;
    }

    int selectedId;
    printf("\nMasukkan ID Transaksi yang ingin dibayar: ");
    scanf("%d", &selectedId);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (transaksi[i].id == selectedId &&
            transaksi[i].user_id == userLogin->id &&
            strcmp(transaksi[i].status, "PENDING") == 0) {

            if (userLogin->saldo < transaksi[i].total_price) {
                printf("Saldo tidak cukup.\n");
                return;
            }

            userLogin->saldo -= transaksi[i].total_price;
            strcpy(transaksi[i].status, "PAID");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Transaksi tidak ditemukan atau sudah dibayar.\n");
        return;
    }

    // Tulis ulang semua transaksi
    file = fopen("data/transaction.txt", "w");
    if (!file) {
        perror("Gagal menulis ulang file transaksi");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%d,%d,%d,%d,%d,%s\n",
                transaksi[i].id, transaksi[i].user_id,
                transaksi[i].cart_id, transaksi[i].item_id,
                transaksi[i].quantity, transaksi[i].total_price,
                transaksi[i].status);
    }
    fclose(file);

    // Perbarui user
    UpdateUserFile(userLogin);
    printf("Pembayaran berhasil! Saldo Anda sekarang: %d\n", userLogin->saldo);
}


boolean IsTrsEmpty(TQueue *TQueue){
    return (TQueue->Front == NULL && TQueue->Rear == NULL);
}

void Dequeue(TQueue *TList) {
    GenerateTransactionList(TList);
    if (IsTrsEmpty(TList)) {
        printf("Tidak ada transaksi dalam antrean.\n");
        return;
    }

    PrintTransaction(*TList);

    char pilihan;
    printf("\nIngin proses transaksi? [y/n]: ");
    scanf(" %c", &pilihan);

    if (pilihan == 'y' || pilihan == 'Y') {
        Transaction *deleted = TList->Front;

        FILE *file = fopen("data/transaction.txt", "r");
        if (!file) {
            perror("Gagal membuka transaction.txt");
            return;
        }

        Transaction allTrans[200];
        int count = 0;
        while (fscanf(file, "%d,%d,%d,%d,%d,%d,%s\n",
                      &allTrans[count].id, &allTrans[count].user_id,
                      &allTrans[count].cart_id, &allTrans[count].item_id,
                      &allTrans[count].quantity, &allTrans[count].total_price,
                      allTrans[count].status) == 7) {
            if (allTrans[count].id == deleted->id &&
                strcmp(allTrans[count].status, "PAID") == 0) {
                strcpy(allTrans[count].status, "SHIPPING");
            }
            count++;
        }
        fclose(file);

        file = fopen("data/transaction.txt", "w");
        if (!file) {
            perror("Gagal menulis ulang transaction.txt");
            return;
        }
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d,%d,%d,%d,%d,%d,%s\n",
                    allTrans[i].id, allTrans[i].user_id,
                    allTrans[i].cart_id, allTrans[i].item_id,
                    allTrans[i].quantity, allTrans[i].total_price,
                    allTrans[i].status);
        }
        fclose(file);

        printf("Memproses transaksi ID: %d, User ID: %d, Total: %d\n",
               deleted->id, deleted->user_id, deleted->total_price);

        TList->Front = TList->Front->next;
        if (TList->Front == NULL) {
            TList->Rear = NULL;
        }
        free(deleted);
        printf("Transaksi berhasil diproses dan diubah ke status SHIPPING.\n\n");

        Dequeue(TList);
    } else {
        printf("Pengolahan transaksi dihentikan.\n");
        return;
    }
}

int CountTransactionByUser(TQueue Q, int user_id) {
    trsAddress temp = Q.Front;
    int count = 0;
    while (temp != NULL) {
        if (temp->user_id == user_id) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

// FILES
trsAddress GetTransactionById(TQueue TQueue, int trs_id) {
    trsAddress temp = TQueue.Front;
    while (temp != NULL) {
        if (temp->id == trs_id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void UpdateUserFile(User *userLogin) {
    FILE *userFile = fopen("data/user.txt", "r");
    if (!userFile) {
        perror("Gagal membuka file user");
        return;
    }

    User users[100];
    int count = 0;

    while (fscanf(userFile, "%d,%[^,],%d,%d,%[^\n]\n",
                  &users[count].id, users[count].username,
                  &users[count].pin, &users[count].saldo,
                  users[count].domisili) == 5)
    {
        if (users[count].id == userLogin->id) {
            users[count].saldo = userLogin->saldo;
        }
        count++;
    }
    fclose(userFile);

    userFile = fopen("data/user.txt", "w");
    if (!userFile) {
        perror("Gagal menulis file user");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(userFile, "%d,%s,%d,%d,%s\n",
                users[i].id, users[i].username,
                users[i].pin, users[i].saldo,
                users[i].domisili);
    }

    fclose(userFile);
}

void SaveTransactionToFile(int user_id, int cart_id, int item_id, int quantity, int total_price) {
    FILE *trsFile;
    int new_id = 1;

    FILE *readFile = fopen("data/transaction.txt", "r");
    char line[200];
    while (readFile && fgets(line, sizeof(line), readFile)) {
        int temp_id;
        if (sscanf(line, "%d,", &temp_id) == 1 && temp_id >= new_id) {
            new_id = temp_id + 1;
        }
    }
    if (readFile) fclose(readFile);

    trsFile = fopen("data/transaction.txt", "a");
    if (!trsFile) {
        perror("Gagal membuka transaction.txt");
        return;
    }

    fprintf(trsFile, "%d,%d,%d,%d,%d,%d,PENDING\n",
            new_id, user_id, cart_id, item_id, quantity, total_price);
    fclose(trsFile);

    printf("Berhasil menyimpan transaksi dengan ID %d!\n", new_id);
}

// HELPER
void GenerateTransactionList(TQueue *TList) {
    Transaction *newTrs;
    char line[200];
    int id, user_id, cart_id, item_id, quantity, total_price;
    char status[20];

    CreateEmptyTransaction(TList);

    FILE *file = fopen("data/transaction.txt", "r");
    if (!file) {
        perror("Error opening transaction.txt");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%d,%d,%d,%d,%d,%19s", &id, &user_id, &cart_id, &item_id, &quantity, &total_price, status) == 7) {
            if (strcmp(status, "PAID") == 0) {
                AllocateTransaction(&newTrs);
                if (newTrs != NULL) {
                    newTrs->id = id;
                    newTrs->user_id = user_id;
                    newTrs->cart_id = cart_id;
                    newTrs->item_id = item_id;
                    newTrs->quantity = quantity;
                    newTrs->total_price = total_price;
                    strcpy(newTrs->status, status);
                    newTrs->next = NULL;

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
