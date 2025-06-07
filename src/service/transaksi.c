#include "../include/transaksi.h"

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

    printf("======================================================================\n");
    printf("| ID  | User ID | Cart ID | Item ID | Qty | Total Price | Status     |\n");
    printf("======================================================================\n");

    while (current != NULL) {
        printf("| %-3d | %-7d | %-7d | %-7d | %-3d | %-11d | %-10s |\n",
               current->id,
               current->user_id,
               current->cart_id,
               current->item_id,
               current->quantity,
               current->total_price,
               current->status);
        current = current->next;
    }

    printf("======================================================================\n");
}

void PayTransaction(int user_id)
{
    Transaction trs[200];
    int trsCount = 0;

    FILE *ftrs = fopen("data/transaction.txt", "r");
    if (!ftrs) { perror("transaction.txt"); return; }

    printf("\n===========================================================\n");
    printf("| ID | Item_ID | Qty |    Total(Rp)   | Status |\n");
    printf("===========================================================\n");

    while (fscanf(ftrs, "%d,%d,%d,%d,%d,%d,%9s",
                  &trs[trsCount].id,
                  &trs[trsCount].user_id,
                  &trs[trsCount].cart_id,
                  &trs[trsCount].item_id,
                  &trs[trsCount].quantity,
                  &trs[trsCount].total_price,
                  trs[trsCount].status) == 7)
    {
        if (trs[trsCount].user_id == user_id &&
            strcmp(trs[trsCount].status, "PENDING") == 0)
        {
            printf("| %-2d | %-7d | %-3d | %-13d | %-7s |\n",
                   trs[trsCount].id,
                   trs[trsCount].item_id,
                   trs[trsCount].quantity,
                   trs[trsCount].total_price,
                   trs[trsCount].status);
        }
        trsCount++;
    }
    fclose(ftrs);
    printf("===========================================================\n");

    if (trsCount == 0) {
        printf("Tidak ada transaksi.\n");
        return;
    }

    int pilihId;
    printf("Masukkan ID transaksi yang ingin dibayar: ");
    scanf("%d", &pilihId);

    int idx = -1;
    for (int i = 0; i < trsCount; ++i) {
        if (trs[i].id == pilihId &&
            trs[i].user_id == user_id &&
            strcmp(trs[i].status, "PENDING") == 0)
        {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("Transaksi tidak ditemukan / sudah dibayar.\n");
        return;
    }

    int hargaBayar = trs[idx].total_price;

    char uline[256], uname[50], dom[50];
    int  uid, upin, usaldo;
    char users[200][256];
    int  ucnt = 0, userIndex = -1;

    FILE *fusr = fopen("data/user.txt", "r");
    if (!fusr) { perror("user.txt"); return; }

    while (fgets(users[ucnt], sizeof(users[ucnt]), fusr)) {
        if (sscanf(users[ucnt], "%d,%49[^,],%d,%d,%49[^\n]",
                   &uid, uname, &upin, &usaldo, dom) == 5)
        {
            if (uid == user_id) {
                userIndex = ucnt;
            }
            ucnt++;
        }
    }
    fclose(fusr);

    if (userIndex == -1) {
        printf("Data user tidak ditemukan!\n");
        return;
    }

    sscanf(users[userIndex], "%d,%[^,],%d,%d,%[^\n]",
           &uid, uname, &upin, &usaldo, dom);

    if (usaldo < hargaBayar) {
        printf("Saldo tidak cukup (saldo: %d, harga: %d).\n", usaldo, hargaBayar);
        return;
    }

    usaldo -= hargaBayar;
    sprintf(users[userIndex], "%d,%s,%d,%d,%s\n",
            uid, uname, upin, usaldo, dom);

    strcpy(trs[idx].status, "PAID");

    fusr = fopen("data/user.txt", "w");
    if (!fusr) { perror("user.txt tulis"); return; }
    for (int i = 0; i < ucnt; ++i)
        fputs(users[i], fusr);
    fclose(fusr);

    ftrs = fopen("data/transaction.txt", "w");
    if (!ftrs) { perror("transaction.txt tulis"); return; }
    for (int i = 0; i < trsCount; ++i)
        fprintf(ftrs, "%d,%d,%d,%d,%d,%d,%s\n",
                trs[i].id, trs[i].user_id, trs[i].cart_id,
                trs[i].item_id, trs[i].quantity,
                trs[i].total_price, trs[i].status);
    fclose(ftrs);

    printf("Pembayaran berhasil!\n");
    printf("Saldo Anda sekarang: %d\n", usaldo);
    
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

void UpdateUserSaldoById(int user_id, int new_saldo) {
    FILE *file = fopen("data/user.txt", "r");
    if (!file) {
        perror("Gagal membuka file user");
        return;
    }

    char lines[100][256];
    int ids[100];
    int count = 0;
    char username[50], domisili[50];
    int id, pin, saldo;

    // Membaca file ke array
    while (fgets(lines[count], sizeof(lines[count]), file)) {
        if (sscanf(lines[count], "%d,%49[^,],%d,%d,%49[^\n]",
                   &id, username, &pin, &saldo, domisili) == 5) {
            ids[count] = id;
            if (id == user_id) {
                // Update saldo di string baris
                sprintf(lines[count], "%d,%s,%d,%d,%s\n",
                        id, username, pin, new_saldo, domisili);
            }
            count++;
        }
    }
    fclose(file);

    // Tulis ulang file
    file = fopen("data/user.txt", "w");
    if (!file) {
        perror("Gagal menulis file user");
        return;
    }

    for (int i = 0; i < count; i++) {
        fputs(lines[i], file);
    }

    fclose(file);
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

void GenerateTransactionListByUser(TQueue *TList, int user_id, const char *statusFilter) {
    Transaction *newTrs;
    char line[200];
    int id, uid, cart_id, item_id, qty, total;
    char status[20];

    /* kosongkan queue lebih dulu */
    CreateEmptyTransaction(TList);

    FILE *file = fopen("data/transaction.txt", "r");
    if (!file) {
        perror("Error opening transaction.txt");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%d,%d,%d,%d,%d,%19s",
                   &id, &uid, &cart_id, &item_id, &qty, &total, status) != 7)
            continue;

        /* pilih transaksi milik user & (opsional) status tertentu */
        if (uid == user_id &&
            (statusFilter == NULL || strcmp(status, statusFilter) == 0)) {

            AllocateTransaction(&newTrs);
            if (!newTrs) continue;

            newTrs->id          = id;
            newTrs->user_id     = uid;
            newTrs->cart_id     = cart_id;
            newTrs->item_id     = item_id;
            newTrs->quantity    = qty;
            newTrs->total_price = total;
            strcpy(newTrs->status, status);
            newTrs->next        = NULL;

            /* enqueue */
            if (IsTrsEmpty(TList)) {
                TList->Front = newTrs;
                TList->Rear  = newTrs;
            } else {
                TList->Rear->next = newTrs;
                TList->Rear       = newTrs;
            }
        }
    }
    fclose(file);
}
