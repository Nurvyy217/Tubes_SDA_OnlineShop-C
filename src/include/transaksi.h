#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include "environment.h"
#include "katalog.h"
#include "printTemplate.h"

#define MAX_TRANSACTION 3          /* Jumlah transaksi maksimum user sekali proses  */

/*  Struktur node untuk merepresentasikan satu transaksi                     */
typedef struct Transaction *trsAddress;
typedef struct Transaction {
    int  id;                       /* ID unik transaksi                       */
    int  user_id;                  /* ID user pemilik transaksi               */
    int  cart_id;                  /* ID keranjang yang dikonversi            */
    int  item_id;                  /* ID item utama (hanya satu item)         */
    int  quantity;                 /* Banyaknya item                          */
    int  total_price;              /* Total harga (quantity × harga item)     */
    char status[10];               /* Status: "PENDING", "PAID", "SHIPPING"   */
    trsAddress next;               /* Pointer ke transaksi berikutnya (queue) */
} Transaction;

/*  Struktur Queue berbasis linked list untuk antrean transaksi berstatus PAID*/
typedef struct TQueue {
    trsAddress Front;              /* Head queue                              */
    trsAddress Rear;               /* Tail queue                              */
} TQueue;

// MAIN
void AllocateTransaction(Transaction **Trs);
/*
* Meng-alokasikan memori untuk node Transaction baru.
* IS : *Trs bernilai NULL
* FS : *Trs menunjuk memori Transaction; NULL jika gagal
*/

void CreateEmptyTransaction(TQueue *TQueue);
/*
* Membuat antrean (queue) transaksi kosong.
* IS : TQueue belum terinisialisasi
* FS : Front dan Rear bernilai NULL
*/

boolean IsTrsEmpty(TQueue *TQueue);
/*
* Mengecek apakah queue transaksi kosong.
* IS : TQueue list sudah dibuat
* FS : Mengembalikan true jika kosong, false jika tidak
*/

void Dequeue(TQueue *TList);
/*
* Memproses transaksi paling depan (status PAID) → ubah jadi SHIPPING.
* IS : TList berisi antrean transaksi berstatus PAID (hasil GenerateTransactionList)
* FS : Node pertama dihapus, file “transaction.txt” ter-update, user mendapat info
*/

// FILES
void SaveTransactionToFile(int user_id, int cart_id,int item_id, int quantity, int total_price);
/*
* Menyimpan transaksi baru ke file “data/transaction.txt” dengan status PENDING.
* IS : File mungkin sudah ada/berisi
* FS : Baris baru tercatat di file, ID otomatis di­-increment
*/

void GenerateTransactionList(TQueue *TList);
/*
* Memuat semua transaksi ber-status PAID dari file ke dalam queue.
* IS : File “transaction.txt” ada dan TList tidak kosong
* FS : TList terisi node Transaksi ber-status PAID, urut sesuai file
*/

void GenerateTransactionListByUser(TQueue *TList, int user_id, const char *statusFilter);
/*
* Memuat transaksi milik user tertentu (dan opsional filter status) ke queue.
* IS : File ada, TList tidak kosong
* FS : TList berisi transaksi milik user dengan status cocok (NULL = semua status)
*/

// HELPER
int CountTransactionByUser(TQueue Q, int user_id);
/*
* Menghitung jumlah transaksi milik user_id di dalam queue.
* IS : List Queue sudah ada
* FS : Mengembalikan jumlah transaksi milik user_id
*/

void PayTransaction(int user_id);
/*
* Menampilkan transaksi PENDING milik user, meminta konfirmasi, memotong saldo user & mengubah status menjadi PAID.
* IS : File “transaction.txt” dan “user.txt” ada, user_id valid
* FS : Saldo user & status transaksi ter-update di file
*/

void PrintTransaction(TQueue TList);
/*
* Menampilkan isi queue (transaksi) dalam bentuk tabel.
* IS : TList valid; bisa kosong
* FS : Tabel transaksi tercetak di terminal
*/

void UpdateUserSaldoById(int user_id, int new_saldo);
/*
* Memperbarui saldo user tertentu di file "data/user.txt".
* IS : File "data/user.txt" dapat dibuka dan user_id valid atau mungkin tidak ada.
* FS : Saldo user dengan user_id yang diberikan diupdate menjadi new_saldo, dan seluruh data user ditulis ulang ke file.
*/


#endif