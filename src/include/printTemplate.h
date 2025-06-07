#ifndef PRINT_TEMPLATE_H
#define PRINT_TEMPLATE_H

#include "environment.h"

void inputPin(int *pin);
/*
 * Meminta input PIN dari user dan menyimpannya ke variabel pin
 * IS : Variabel pin belum berisi input user
 * FS : Variabel pin berisi input PIN dari user
 */

void clear_screen();
/*
 * Membersihkan layar terminal/console
 * IS : Layar terminal bisa berisi tampilan apapun
 * FS : Layar terminal bersih/clear
 */

void print_center(const char *text, int width, int height);
/*
 * Menampilkan teks di tengah layar dengan lebar dan tinggi tertentu
 * IS : Teks belum ditampilkan di tengah layar
 * FS : Teks tampil di tengah layar sesuai width dan height
 */

void print_title(const char *title, int width);
/*
 * Menampilkan judul di tengah layar dengan lebar tertentu
 * IS : Judul belum ditampilkan
 * FS : Judul tampil di tengah layar sesuai width
 */

#endif