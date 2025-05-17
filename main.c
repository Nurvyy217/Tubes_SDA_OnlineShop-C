#include <stdio.h>
#include <windows.h>
#include "styleText.h"
#include "login.h"
#include "katalog.h"
#include "katalog.c"

int main(){
    char choice1, choice2;
    // printf("Welcome to online shop\n");
    // Sleep(3000);
    // system("cls");
    // printf("LOGIN / REGISTRASI\n");
    // printf("\t\t\t\t\t<=====================================>\n");
    // printf("\n\n\n\nPilihan: ");scanf(" %c", &choice1);
	// system("cls");
    // if (choice1 == '1') {
    // 	printf("1.ADMIN / 2. USER");
    // 	printf("\t\t\t\t\t<=====================================>\n");
    // 	printf("\n\n\n\nPilihan: ");scanf(" %c",&choice2);
    // 	system("cls");
    // 	if(choice2 == '1'){
    // 		loginAdmin();
	// 	}
    //     else if(choice2 == '2'){
    //     	loginUser();
	// }
    // } else if (choice1 == '2') {
    // 	system("cls");
    //     registrasi();
    // } else {
    //     printf("Pilihan tidak valid. Silakan jalankan ulang program.\n");
    // }


    // test modul katalog 
    // AKTIFKAN JIKA ANDA PENASARAN HEHE
    List katalog;
    katalog.First = Nil;

    // Tambah jenis barang
    addJenis(&katalog, "Elektronik");
    addJenis(&katalog, "Pakaian");
    addJenis(&katalog, "Makanan");

    // Tambah produk ke jenis Elektronik
    addProduk(&katalog, 2000000, 10, "Laptop", "Elektronik");
    addProduk(&katalog, 500000, 20, "Smartphone", "Elektronik");

    // Tambah produk ke jenis Pakaian
    addProduk(&katalog, 150000, 30, "Kaos", "Pakaian");
    addProduk(&katalog, 250000, 15, "Jaket", "Pakaian");

    // Tambah produk ke jenis Makanan
    addProduk(&katalog, 10000, 50, "Roti", "Makanan");

    printf("\n=== Katalog Awal ===\n");
    printKatalog(katalog);

    // Tambah stok produk
    printf("\n\nTambah stok Kaos +10 ");
    addStokProduk(&katalog, 10, "Kaos");

    // Kurangi stok produk
    printf("\nKurangi stok Laptop -5");
    minusStokProduk(&katalog, 5, "Laptop");
    printf("\nupdate harga Labtop");
    updateHargaProduk(&katalog, 3000000, "Laptop");

    // Hapus produk
    printf("\nHapus produk Smartphone dari Elektronik");
    delProduk(&katalog, "Smartphone", "Elektronik");

    // Hapus jenis
    printf("\nHapus jenis Makanan beserta produknya");
    delJenis(&katalog, "Makanan");

    printf("\n\n=== Katalog Setelah Update ===\n");
    printKatalog(katalog);

    return 0;
}