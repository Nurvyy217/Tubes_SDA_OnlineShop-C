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

    printf("===============================================================================================\n");
    printf("| ID  | User ID | Cart ID | Item ID | Qty | Total Price | Status     | Route                \n");
    printf("===============================================================================================\n");

    while (current != NULL) {
        printf("| %-3d | %-7d | %-7d | %-7d | %-3d | %-11d | %-10s | %-20s \n",
               current->id,
               current->user_id,
               current->cart_id,
               current->item_id,
               current->quantity,
               current->total_price,
               current->status,
               current->route);
        current = current->next;
    }

    printf("===============================================================================================\n");
}
int PayTransaction(int user_id)
{
    TQueue pendingTrx;
    GenerateTransactionListByUser(&pendingTrx, user_id, "PENDING");

    clear_screen();
    print_title("PEMBAYARAN BARANG", WIDTH);
    printf("\n==============================================================\n");
    printf("| ID | Item_ID | Qty |    Total(Rp)   | Status | Rute         \n");
    printf("==============================================================\n");
    
    Transaction *curr = pendingTrx.Front;
    int count = 0;
    
    while (curr != NULL) {
        printf("| %-2d | %-7d | %-3d | %-13d | %-7s | %s\n",
            curr->id, curr->item_id, curr->quantity,
            curr->total_price, curr->status, curr->route);
            count++;
            curr = curr->next;
    }
    
    printf("==============================================================\n");

    if (count == 0) {
        printf("Tidak ada transaksi PENDING.\n");
        return 0;
    }

    int pilihId;
    printf("Masukkan ID transaksi yang ingin dibayar: ");
    scanf("%d", &pilihId);

    // Cari transaksi berdasarkan ID
    Transaction *target = pendingTrx.Front;
    while (target != NULL && target->id != pilihId)
        target = target->next;

    if (target == NULL) {
        printf("Transaksi tidak ditemukan atau tidak PENDING.\n");
        return 0;
    }

    // Proses pembayaran
    int hargaBayar = target->total_price;

    // Baca data user
    FILE *fusr = fopen("data/user.txt", "r");
    if (!fusr) { perror("user.txt"); return 0; }

    char users[200][256], uname[50], dom[50];
    int  uid, upin, usaldo, ucnt = 0, userIndex = -1;

    while (fgets(users[ucnt], sizeof(users[ucnt]), fusr)) {
        sscanf(users[ucnt], "%d,%49[^,],%d,%d,%49[^\n]",
               &uid, uname, &upin, &usaldo, dom);

        if (uid == user_id)
            userIndex = ucnt;

        ucnt++;
    }
    fclose(fusr);

    if (userIndex == -1) {
        printf("Data user tidak ditemukan!\n");
        return 0;
    }

    sscanf(users[userIndex], "%d,%[^,],%d,%d,%[^\n]",
           &uid, uname, &upin, &usaldo, dom);

    if (usaldo < hargaBayar) {
        printf("Saldo tidak cukup (saldo: %d, harga: %d).\n", usaldo, hargaBayar);
        return 0;
    }

    usaldo -= hargaBayar;
    sprintf(users[userIndex], "%d,%s,%d,%d,%s\n", uid, uname, upin, usaldo, dom);

    // Update file user
    fusr = fopen("data/user.txt", "w");
    if (!fusr) { perror("user.txt tulis"); return 0; }
    for (int i = 0; i < ucnt; ++i)
        fputs(users[i], fusr);
    fclose(fusr);

    // Update transaksi (ubah status jadi PAID dan route tetap sama)
    FILE *ftrs = fopen("data/transaction.txt", "r");
    if (!ftrs) { perror("transaction.txt"); return 0; }

    Transaction allTrs[200];
    int trsCount = 0;
    char line[300];

    while (fgets(line, sizeof(line), ftrs)) {
        int n = sscanf(line, "%d,%d,%d,%d,%d,%d,%19[^,],%199[^\n]",
                    &allTrs[trsCount].id, &allTrs[trsCount].user_id,
                    &allTrs[trsCount].cart_id, &allTrs[trsCount].item_id,
                    &allTrs[trsCount].quantity, &allTrs[trsCount].total_price,
                    allTrs[trsCount].status, allTrs[trsCount].route);

        if (n == 8) {
            if (allTrs[trsCount].id == pilihId &&
                allTrs[trsCount].user_id == user_id) {
                strcpy(allTrs[trsCount].status, "PAID");
                // Jika ingin update route juga saat bayar, tambahkan di sini, misal:
                // strcpy(allTrs[trsCount].route, "RUTE BARU");
            }
            trsCount++;
        } else {
            // Jika parsing gagal, abaikan baris ini (atau bisa log error)
        }
    }
    fclose(ftrs);

    ftrs = fopen("data/transaction.txt", "w");
    if (!ftrs) { perror("transaction.txt tulis"); return 0; }
    for (int i = 0; i < trsCount; ++i) {
        fprintf(ftrs, "%d,%d,%d,%d,%d,%d,%s,%s\n",
                allTrs[i].id, allTrs[i].user_id, allTrs[i].cart_id,
                allTrs[i].item_id, allTrs[i].quantity,
                allTrs[i].total_price, allTrs[i].status, allTrs[i].route);
    }
    fclose(ftrs);

    printf("Pembayaran berhasil!\n");
    printf("Saldo Anda sekarang: %d\n", usaldo);
    return 1;
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
        while (fscanf(file, "%d,%d,%d,%d,%d,%d,%[^,],%[^\n]",
                    &allTrans[count].id, &allTrans[count].user_id,
                    &allTrans[count].cart_id, &allTrans[count].item_id,
                    &allTrans[count].quantity, &allTrans[count].total_price,
                    allTrans[count].status, allTrans[count].route) == 8) {

            if (allTrans[count].id == deleted->id &&
                strcmp(allTrans[count].status, "PAID") == 0) {

                // Hanya ubah status, biarkan route tetap
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
            fprintf(file, "%d,%d,%d,%d,%d,%d,%s,%s\n",
                    allTrans[i].id, allTrans[i].user_id,
                    allTrans[i].cart_id, allTrans[i].item_id,
                    allTrans[i].quantity, allTrans[i].total_price,
                    allTrans[i].status, allTrans[i].route);
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

    while (fgets(lines[count], sizeof(lines[count]), file)) {
        if (sscanf(lines[count], "%d,%49[^,],%d,%d,%49[^\n]",
                   &id, username, &pin, &saldo, domisili) == 5) {
            ids[count] = id;
            if (id == user_id) {
                sprintf(lines[count], "%d,%s,%d,%d,%s\n",
                        id, username, pin, new_saldo, domisili);
            }
            count++;
        }
    }
    fclose(file);

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
int SaveOrUpdateTransaction(const char *mode,int id_to_update,int user_id, int cart_id, int item_id, int quantity, int total_price,const char *status, const char *route)
{
    if (strcmp(mode, "baru") == 0) {
        FILE *readFile = fopen("data/transaction.txt", "r");
        int new_id = 1;
        char line[300];
        if (readFile) {
            while (fgets(line, sizeof(line), readFile)) {
                int temp_id;
                if (sscanf(line, "%d,", &temp_id) == 1 && temp_id >= new_id) {
                    new_id = temp_id + 1;
                }
            }
            fclose(readFile);
        }

        FILE *file = fopen("data/transaction.txt", "a");
        if (!file) {
            perror("Gagal membuka transaction.txt untuk append");
            return -1;
        }

        fprintf(file, "%d,%d,%d,%d,%d,%d,%s,%s\n",
                new_id, user_id, cart_id, item_id, quantity, total_price, status, route);
        fclose(file);

        printf("Berhasil menambahkan transaksi baru dengan ID %d\n", new_id);
        return new_id;

    } else if (strcmp(mode, "update") == 0) {
        FILE *file = fopen("data/transaction.txt", "r");
        if (!file) {
            perror("Gagal membuka transaction.txt untuk baca");
            return -1;
        }

        Transaction *records = NULL;
        size_t count = 0, capacity = 10;
        records = malloc(capacity * sizeof(Transaction));
        if (!records) {
            fclose(file);
            perror("Memory allocation gagal");
            return -1;
        }

        char line[300];
        while (fgets(line, sizeof(line), file)) {
            Transaction tr;
            int n = sscanf(line, "%d,%d,%d,%d,%d,%d,%19[^,],%199[^\n]",
                           &tr.id, &tr.user_id, &tr.cart_id, &tr.item_id,
                           &tr.quantity, &tr.total_price, tr.status, tr.route);
            if (n == 8) {
                if (count == capacity) {
                    capacity *= 2;
                    Transaction *temp = realloc(records, capacity * sizeof(Transaction));
                    if (!temp) {
                        free(records);
                        fclose(file);
                        perror("Memory allocation gagal");
                        return -1;
                    }
                    records = temp;
                }
                records[count++] = tr;
            }
        }
        fclose(file);

        // Cari dan update
        bool found = false;
        for (size_t i = 0; i < count; i++) {
            if (records[i].id == id_to_update) {
                records[i].user_id = user_id;
                records[i].cart_id = cart_id;
                records[i].item_id = item_id;
                records[i].quantity = quantity;
                records[i].total_price = total_price;
                strcpy(records[i].status, status);
                strcpy(records[i].route, route);
                found = true;
                break;
            }
        }

        if (!found) {
            printf("ID transaksi %d tidak ditemukan untuk diupdate.\n", id_to_update);
            free(records);
            return -1;
        }

        // Tulis ulang
        file = fopen("data/transaction.txt", "w");
        if (!file) {
            perror("Gagal membuka transaction.txt untuk tulis ulang");
            free(records);
            return -1;
        }

        for (size_t i = 0; i < count; i++) {
            fprintf(file, "%d,%d,%d,%d,%d,%d,%s,%s\n",
                    records[i].id, records[i].user_id, records[i].cart_id, records[i].item_id,
                    records[i].quantity, records[i].total_price, records[i].status, records[i].route);
        }

        fclose(file);
        free(records);
        printf("Berhasil mengupdate transaksi dengan ID %d\n", id_to_update);
        return id_to_update;
    }

    printf("Mode tidak dikenali: %s\n", mode);
    return -1;
}

// HELPER
void GenerateTransactionList(TQueue *TList) {
    Transaction *newTrs;
    char line[300];
    int id, user_id, cart_id, item_id, quantity, total_price;
    char status[20];
    char route[200];

    CreateEmptyTransaction(TList);

    FILE *file = fopen("data/transaction.txt", "r");
    if (!file) {
        perror("Error opening transaction.txt");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        int n = sscanf(line, "%d,%d,%d,%d,%d,%d,%19[^,],%199[^\n]",
                       &id, &user_id, &cart_id, &item_id, &quantity,
                       &total_price, status, route);
        if (n == 8) {
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
                    strcpy(newTrs->route, route);
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

void GenerateTransactionListByUser(TQueue *TList, int user_id, const char *statusFilter) {
    Transaction *newTrs;
    char line[300];
    int id, uid, cart_id, item_id, qty, total;
    char status[20], route[200];

    CreateEmptyTransaction(TList);

    FILE *file = fopen("data/transaction.txt", "r");
    if (!file) {
        perror("Error opening transaction.txt");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%d,%d,%d,%d,%d,%19[^,],%199[^\n]",
                   &id, &uid, &cart_id, &item_id, &qty, &total, status, route) != 8)
            continue;

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
            strcpy(newTrs->route, route);
            newTrs->next        = NULL;

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