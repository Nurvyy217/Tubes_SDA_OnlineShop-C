#ifndef KATALOG_H
#define KATALOG_H
#define MAX 100

// Struct Katalog Produk
typedef int infoJumlah;
typedef char barang;
typedef int harga;
typedef struct PRODUK* addressProduk;
typedef struct PRODUK{
    infoJumlah jumlah; // jumlah barang
    barang barang[MAX]; // nama barang 
    harga harga; // harga barang 
    addressProduk next; // pointer ke next produk
}PRODUK;

// Struct Katalog Jenis
typedef char jenisProduk;
typedef struct Jenis* addressJenis; 
typedef struct Jenis{
    jenisProduk Jenis[MAX]; // jenis barang 
    addressJenis next_jenis; // pointer ke jenis
    addressProduk produkJenis; // pointer ke produk 
}Jenis;

typedef struct{
    addressProduk First;
}produkFirst;

typedef struct {
    addressJenis First;   
}jenisFirst;

// modul konstrukktor
addressProduk alokasi_Produk(int harga, int jumlah, char* barang);
// IS : Tidak ada NODE yang dibuat untuk produk
// FS : Terdapat sebuah NODE untuk produk
addressJenis alokasi_Jenis(char* jenis);
// IS : Tidak ada NODE yang dibuat untuk Jenis Barang
// FS : Tedapat sebuah NODE untuk Jenis barang

// modul control 
void addProduk(produkFirst *P, int harga, int jumlah, char* barang);
// IS : list produk tidak ada atau bisa saja ada 
// FS : list produk terdapat sebuah node atau list bertambah
void addJenis(jenisFirst *P, char* Jenis);
// IS : list jenis tidak ada atau bisa saja ada
// FS : list produk terdapat sebuah node atau list bertambah





#endif