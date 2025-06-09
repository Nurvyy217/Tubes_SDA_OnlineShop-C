#ifndef KERANJANG_H
#define KERANJANG_H

#include "environment.h"
#include "katalog.h"
#include "transaksi.h"

/* Struktur node untuk satu entri keranjang */
typedef struct Cart *cartAddress;
typedef struct Cart {
    int id;             /* ID unik keranjang                         */
    int user_id;        /* ID user pemilik keranjang                 */
    int item_id;        /* ID barang dalam katalog                   */
    int quantity;       /* Jumlah barang                             */
    cartAddress next;   /* Pointer ke node keranjang berikutnya      */
} Cart;

/* Struktur list untuk menyimpan kumpulan keranjang */
typedef struct { 
    cartAddress First;  /* Pointer ke elemen pertama dalam list      */
} CartList;

// MAIN
void CreateEmptyCart(CartList *CList);
/*
* Membuat list keranjang kosong.
* IS : CList belum terisi
* FS : First bernilai NULL
*/

void AllocateCart(Cart **newCart);
/*
* Mengalokasikan memori untuk node Cart baru.
* IS : node *newCart bernilai NULL
* FS : node *newCart menunjuk memori Cart; NULL jika gagal
*/

void AddCart(CartList *CList, int user_id);
/*
* Menambahkan barang ke keranjang pengguna.
* IS : CList sudah dimuat, user_id valid
* FS : Keranjang diperbarui atau item ditambahkan baru
*/

void InsertLast(CartList *list, cartAddress newCart);
/*
* Menambahkan node Cart ke akhir list.
* IS : list valid, newCart sudah dialokasikan
* FS : newCart ditambahkan ke akhir list
*/

void PrintCart(CartList CList, int user_id, boolean *item);
/*
* Menampilkan isi keranjang milik user dalam bentuk tabel.
* IS : CList terdefinisi, user_id valid
* FS : Isi keranjang tercetak, *item true jika ada item
*/

cartAddress GetCartById(CartList CList, int cart_id);
/*
* Mengembalikan pointer ke cart dengan ID tertentu.
* IS : CList terdefinisi
* FS : Mengembalikan alamat cart yang sesuai, NULL jika tidak ditemukan
*/

void CheckOut(CartList *CList, TQueue *TList, List *P, int id_user);
/*
* Melakukan proses checkout untuk keranjang tertentu.
* IS : Semua struktur data dan file valid
* FS : Transaksi tercatat, keranjang dihapus, stok barang dikurangi
*/

// FILES
void AddToFile(int id, int user_id, int item_id, int quantity);
/*
* Menambahkan baris baru ke file cart.txt.
* IS : Parameter valid
* FS : Data keranjang tersimpan ke file
*/

void RewriteCartFile(CartList CList);
/*
* Menulis ulang seluruh isi list keranjang ke file cart.txt.
* IS : CList valid
* FS : File cart.txt mencerminkan isi CList saat ini
*/

// HELPER
void GenerateCartList(CartList *CList);
/*
* Memuat isi file cart.txt ke dalam list keranjang.
* IS : File cart.txt tersedia
* FS : CList berisi semua data dari file
*/

void LoadTempCartList(CartList *CList);
/*
* Memuat isi file cart_history.txt sebagai list keranjang temporer.
* IS : File cart_history.txt tersedia
* FS : CList terisi data historis keranjang
*/

int GetLastCartID(CartList activeList, CartList tempList);
/*
* Mendapatkan ID terbesar dari kedua list keranjang.
* IS : Kedua list valid
* FS : Mengembalikan nilai ID terbesar sebagai acuan ID baru
*/

int GetPrice(int item_id);
/*
* Mengambil harga dari suatu item berdasarkan ID.
* IS : File katalog tersedia
* FS : Mengembalikan harga item atau 0 jika tidak ditemukan
*/

void DeleteCartById(CartList *CList, int cart_id);
/*
* Menghapus cart berdasarkan ID dan memperbarui file.
* IS : CList valid dan file dapat diakses
* FS : Cart dihapus dari memori dan file, riwayat disimpan
*/

#endif