# 👟 AlpenliShop

**AlpenliShop** adalah aplikasi *online shop sepatu* berbasis terminal yang dikembangkan menggunakan bahasa pemrograman **C**. Aplikasi ini terdiri dari dua program: `admin` dan `user`. Setiap program memiliki fitur yang berbeda dan memanfaatkan berbagai struktur data seperti Stack, Queue, Tree, Linked List, dan Double Linked List.


---
## 🎯 Tujuan Pembuatan Program

Tujuan pembuatan program ini adalah untuk memenuhi tugas akhir mata kuliah **Struktur Data dan Algoritma (Praktek)**.


---

## 🧩 Fitur Aplikasi

### 👤 Fitur untuk User
- Registrasi User
- Login User
- Menu User
- Top Up Saldo
- Lihat Produk
- Beli Produk
- Masukkan Produk ke Keranjang
- Lihat Keranjang Saya
- Info / Riwayat Transaksi

### 👨‍💼 Fitur untuk Admin
- Login Admin
- Proses Transaksi
- Print Tree daftar kota pengiriman (Jawa Barat & Jabodetabek)
- Kelola Katalog Produk (CRUD):
  - Tambah Produk
  - Lihat Produk
  - Ubah Produk
  - Hapus Produk

---

## 👥 Pembagian Tugas

### Muhammad Hasbi Hardian
- ADT User: Login, Menu, Top Up, dll
- ADT Admin: Login, Menu, dll
- Membuat ADT **Stack** untuk print rute pengiriman
- Membuat ADT **Tree** untuk menyimpan daftar kota
- Kontribusi helper seperti input PIN sensor (`XXXX`)

### Muhammad Faliq Siddiq Azzaki
- Kontribusi ADT User dan ADT Admin
- Membuat ADT **Double Linked List** untuk katalog produk

### Nabil Mudzaki Al Muharam
- Kontribusi ADT User dan ADT Admin
- Membuat ADT **Queue** untuk transaksi user
- Membuat ADT **Single Linked List** untuk keranjang belanja

---

## ⚙️ Cara Menjalankan Aplikasi

### 1. Siapkan Compiler
Pastikan Anda telah menginstal compiler seperti:
- GCC (melalui MSYS/MinGW)
- Terminal: PowerShell atau CMD

### 2. Tambahkan File `environment.h`
Karena file `include/environment.h` di-*ignore* di `.gitignore`, Anda perlu menambahkannya sendiri ke folder `include/`.

Isi dari `environment.h`:

```c
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#define WIDTH 60
#define HEIGHT 11

#define true 1
#define false 0

#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

```
### 3. Kompilasi Program dan Run Program
Buka terminal dan navigasikan ke direktori proyek, lalu jalankan perintah berikut untuk mengkompilasi program:

Untuk Admin:

Powershell:
```Powershell
./admin.bat
./admin.exe
```

cmd:
```Command Prompt
admin.bat
admin.exe
```


Untuk User:

Powershell:
```Powershell
./user.bat
./user.exe
```

cmd:
```Command Prompt
user.bat
user.exe
```

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

```
MIT License

Copyright (c) 2024 AlpenliShop

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```