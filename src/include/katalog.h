#ifndef KATALOG_H
#define KATALOG_H
#define MAX 100
#define Nil NULL
#include <stdbool.h>
#define FILE_KATALOG "data/katalog.txt"


// Struct Katalog Produk
typedef int infoJumlah;
typedef char barang;
typedef int infoHarga;
typedef struct PRODUK* addressProduk;
typedef struct PRODUK{
    int id;
    infoJumlah stok; // stok barang
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

// MODUL KATALOG INTERFACE
// IS : admin tidak dapat mengontrol katalog
// FS : admin dapat mengontrol penuh katalog 
void adminKatalog(); 


// MODUL KONSTRUKTOR
// IS : Tidak ada NODE yang dibuat untuk produk
// FS : Terdapat sebuah NODE untuk produk
addressProduk alokasi_Produk(int harga, int stok, char* barang, int id);

// IS : Tidak ada NODE yang dibuat untuk Jenis Barang
// FS : Tedapat sebuah NODE untuk Jenis barang
addressJenis alokasi_Jenis(char* jenis);


// MODUL CONTROL LIST
// IS : list produk tidak ada atau bisa saja ada 
// FS : list produk terdapat sebuah node atau list bertambah
void addProduk(List *P, int harga, int stok, char* barang, char* jenis, int id);

// IS : list jenis tidak ada atau bisa saja ada
// FS : list produk terdapat sebuah node atau list bertambah
void addJenis(List *P, char* Jenis);

// IS : list produk ada
// FS : salah satu node telah dihapus dari list
void delProduk(List *P, char* produk, char* jenis);

// IS : list Jenis ada 
// FS : salah satu node jenis telah dihapus dari list dan semua produk dalam jenis tersebut pun ikut terhapus
void delJenis(List *P, char* jenis);

// IS : data stok produk ada dan belum bertambah
// FS : data stok produk bertambah nilainya
void addStokProduk(List *P, int stok, char* produk);

// IS : data stok produk ada dan belum berkurang
// FS : data stok produk berkurang nilainya
void minusStokProduk(List *P, int stock, char* produk);

// IS : data harga produk ada
// FS : data harga produk di update
void updateHargaProduk(List *P, int harga, char* produk);


/*MODUL NON CONTROL*/ 

// IS : semua list produk belum di print ke terminal
// FS : semua list produk sudah di print ke terminal
void printKatalog(List P);

// IS : terdapat pointer yang menunjuk ke arah sembarang
// FS : mengembalikan pointer yang menunjuk ke arah node barang yang dituju
addressProduk searchProduk(List *P, char* barang);

// IS : node memiliki data harga
// FS : mengembalikan nilai dari data harga yang dicari
int getHargaProduk(List *P, char* barang);

// IS : node memiliki data stok
// FS : mengembalikkan nilai dari data stok yang dicari
int getStokProduk(List *P, char* barang);

// IS : nilai duplikasi jenis false
// FS : mengembalikan nilai boolean duplikasi jenis bisa true dan bisa false
bool isDuplikatJenis(List *P, char* jenis);

// IS : nilai duplikasi produk false
// FS : mengembalikan nilai boolean duplikasi produk bisa true dan bisa false
bool isDuplikatProduk(addressProduk P, char* produk);

// IS : list produk spesifik dari sebuah jenis belum di print ke terminal 
// FS : list produk spesifik dari sudah jenis belum di print ke terminal 
void userPrintKatalogByKategori(List P);

// IS : node produk memiliki sebuah id
// FS : mengembalikan nilai dari id produk paling tinggi
int getMaxIdOfProduk(List P);



/* FILE OPERATION OF KATALOG */   

// IS : file .txt bisa kosong bisa tidak, data belum disimpan di file
// FS : file .txt terupdate, data telah disimpan di file 
void saveKatalogToFile(List L);

// IS : file .txt bisa kosong dan bisa tidak, data tidak diambil ke program
// FS : file .txt diambil ke DLL dan bisa di manipulasi dalam program
void loadKatalogFromFile(List *L);




#endif