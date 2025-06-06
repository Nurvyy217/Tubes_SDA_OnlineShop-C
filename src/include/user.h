#ifndef USER_H
#define USER_H

#include <stdio.h>
#include "katalog.h"
#include "tree.h"

// Path file user
#define USER_FILE "data/user.txt"

// Struktur data user
typedef struct
{
    int id;
    char username[50];
    int pin;
    int saldo;
    char domisili[50];
} User;

void initUserFile();
/*
 * Inisialisasi file user (buat jika belum ada)
 * IS : File user.txt bisa ada atau tidak ada
 * FS : File user.txt pasti ada (jika belum ada, dibuat baru)
 */

void registration();
/*
 * Registrasi user baru
 * IS : Data user belum ada di file user.txt
 * FS : Data user baru ditambahkan ke file user.txt jika valid
 */

void loginUser(TreeManager *tm, List P, User *user);
/*
 * Login user
 * IS : User belum login
 * FS : User berhasil login jika data benar, atau gagal jika salah
 */

void saveUser(User *u);
/*
 * Simpan user baru ke file
 * IS : Data user belum tersimpan di file
 * FS : Data user tersimpan di file user.txt
 */

int getLastUserId();
/*
 * Mendapatkan ID user terakhir
 * IS : Tidak diketahui ID terakhir user
 * FS : Mengembalikan ID user terbesar di file user.txt
 */

int isUsernameExists(const char *username);
/*
 * Cek apakah username sudah ada
 * IS : Tidak diketahui apakah username sudah terdaftar
 * FS : Mengembalikan true jika username sudah ada, false jika belum
 */

int getUserByUsername(const char *username, User *u);
/*
 * Ambil data user berdasarkan username
 * IS : Data user belum diketahui
 * FS : Data user diisi jika ditemukan, return 1 jika ada, 0 jika tidak
 */

void userMenu(User *user, TreeManager *tm, List P);
/*
 * Menu utama user
 * IS : User sudah login
 * FS : Menampilkan menu dan menjalankan fitur sesuai pilihan user
 */

void viewProduct(TreeManager *tm, User *user, List P);
/*
 * Menampilkan produk
 * IS : Produk belum ditampilkan
 * FS : Daftar produk ditampilkan ke user
 */

void topUp(User *user);
/*
 * Top up saldo user
 * IS : Saldo user belum bertambah
 * FS : Saldo user bertambah sesuai input
 */

void buyProduct(TreeManager *tm, User *user);
/*
 * Fitur beli produk
 * IS : User belum melakukan pembelian
 * FS : Proses pembelian produk berjalan sesuai input user
 */

 void orderInformation(User *user)
{
/*
* Menampilkan informasi pesanan user
* IS : User sudah login
* FS : Menampilkan detail pesanan yang telah dilakukan user
*/
}

#endif