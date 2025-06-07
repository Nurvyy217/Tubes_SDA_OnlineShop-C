#ifndef ADMIN_H
#define ADMIN_H

#include "../include/tree.h"

void ProsesTransaksi(TreeManager *tm);
/*
 * Memproses transaksi yang dilakukan oleh admin
 * IS : Data transaksi belum diproses
 * FS : Transaksi diproses sesuai prosedur admin
 */

void loginAdmin();
/*
 * Melakukan proses login untuk admin
 * IS : Admin belum login
 * FS : Admin berhasil login jika data benar, atau gagal jika salah
 */
#endif