#ifndef KATALOG_H
#define KATALOG_H
#define MAX 100
#define Nil NULL

// Struct Katalog Produk
typedef int infoJumlah;
typedef char barang;
typedef int infoHarga;
typedef struct PRODUK* addressProduk;
typedef struct PRODUK{
    infoJumlah jumlah; // jumlah barang
    barang barang[MAX]; // nama barang 
    infoHarga harga; // harga barang 
    addressProduk next; // pointer ke next produk
}PRODUK;

// Struct Katalog Jenis
typedef char jenisProduk;
typedef struct JENIS* addressJenis; 
typedef struct JENIS{
    jenisProduk Jenis[MAX]; // jenis barang 
    addressJenis next_jenis; // pointer ke jenis
    addressProduk produkJenis; // pointer ke produk 
}JENIS;

typedef struct {
    addressJenis First;   
}List;

// MODUL KATALOG
void Katalog(); 
// IS : admin tidak dapat mengontrol katalog
// FS : admin dapat mengontrol penuh katalog 

// MODUL KONSTRUKTOR
addressProduk alokasi_Produk(int harga, int jumlah, char* barang);
// IS : Tidak ada NODE yang dibuat untuk produk
// FS : Terdapat sebuah NODE untuk produk
addressJenis alokasi_Jenis(char* jenis);
// IS : Tidak ada NODE yang dibuat untuk Jenis Barang
// FS : Tedapat sebuah NODE untuk Jenis barang

// MODUL CONTROL LIST
void addProduk(List *P, int harga, int jumlah, char* barang, char* jenis);
// IS : list produk tidak ada atau bisa saja ada 
// FS : list produk terdapat sebuah node atau list bertambah
void addJenis(List *P, char* Jenis);
// IS : list jenis tidak ada atau bisa saja ada
// FS : list produk terdapat sebuah node atau list bertambah
void delProduk(List *P, char* produk, char* jenis);
// IS : list produk ada
// FS : salah satu node telah dihapus dari list
void delJenis(List *P, char* jenis);
// IS : list Jenis ada 
// FS : salah satu node jenis telah dihapus dari list dan semua produk dalam jenis tersebut pun ikut terhapus

// MODUL NON CONTROL
void printKatalog(List P);
// IS : list belum di print ke terminal
// FS : list sudah di print ke terminal

// FILE OPERATION OF KATALOG



#endif