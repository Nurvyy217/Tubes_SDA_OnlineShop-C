#ifndef TRANSIT_KOTA_H
#define TRANSIT_KOTA_H

#define TREE_FILE "data/tree.txt"
#define MAX_WIDTH 200

#define Id(T) (T)->id
#define Name(T) (T)->name
#define ParentId(T) (T)->parent_id
#define Parent(T) (T)->parent
#define FirstChild(T) (T)->first_child
#define NextSibling(T) (T)->next_sibling
#define NodeCount(T) (T).node_count
#define Nodes(T) (T).nodes


typedef struct TreeNode *addressTree;
// Struktur node untuk merepresentasikan kota dalam tree
typedef struct TreeNode {
    int id;                         // ID unik kota
    char name[100];                 // Nama kota
    int parent_id;                  // ID parent (0 jika root)
    addressTree parent;        // Pointer ke parent
    addressTree first_child;   // Pointer ke anak pertama
    addressTree next_sibling;  // Pointer ke saudara berikutnya
} TreeNode;

// Struktur manajer tree untuk menyimpan semua node
typedef struct {
    addressTree nodes[20];           // Array pointer ke semua node
    int node_count;                 // Jumlah node dalam tree
} TreeManager;

void InitTree(TreeManager *tm);
/*
 * Inisialisasi tree dari file, atau buat default jika file kosong/tidak ada
 * IS : TreeManager belum terisi data tree
 * FS : TreeManager terisi data tree dari file atau default
 */

void load_tree(TreeManager *tm);
/*
 * Memuat tree dari file TREE_FILE ke TreeManager
 * IS : File TREE_FILE ada dan berisi data tree, TreeManager kosong
 * FS : TreeManager terisi node-node dari file, relasi parent-child terbentuk
 */

addressTree find_node_by_name(TreeManager *tm, char *name);
/*
 * Mencari node berdasarkan nama kota (case-insensitive)
 * IS : TreeManager sudah terisi node
 * FS : Mengembalikan pointer ke node dengan nama sesuai, atau NULL jika tidak ada
 */

void save_tree(TreeManager *tm);
/*
 * Menyimpan tree ke file TREE_FILE
 * IS : TreeManager sudah terisi node
 * FS : Semua node tree tersimpan ke file TREE_FILE
 */

void insert_default_tree(TreeManager *tm);
/*
 * Mengisi TreeManager dengan data tree default (hardcoded)
 * IS : TreeManager kosong
 * FS : TreeManager terisi node default (Jawa Barat & Jabodetabek)
 */

void print_tree_horizontal_centered(TreeManager *tm);
/*
 * Menampilkan tree secara horizontal dan terpusat di terminal
 * IS : TreeManager sudah terisi node
 * FS : Struktur tree tampil di terminal secara visual
 */

int print_tree_centered(addressTree node, char canvas[][MAX_WIDTH], int row, int col);
/*
 * Fungsi rekursif untuk print tree ke canvas (dipakai internal)
 * IS : Canvas kosong, node valid
 * FS : Node dan subtree-nya tergambar di canvas pada posisi yang sesuai
 */

void print_tree_at(char canvas[][MAX_WIDTH], int row, int col, const char *text);
/*
 * Print string pada posisi tertentu di canvas (dipakai internal)
 * IS : Canvas kosong/terisi sebagian
 * FS : Text tampil di canvas pada baris dan kolom yang ditentukan
 */

int subtree_width(addressTree node);
/*
 * Menghitung lebar subtree (jumlah kolom yang dibutuhkan)
 * IS : Node valid
 * FS : Mengembalikan lebar subtree dari node tersebut
 */

void showCityList(TreeManager *tm);
/*
 * Menampilkan daftar nama kota yang tersedia di tree, dipisahkan koma
 * IS : TreeManager sudah terisi node
 * FS : Semua nama kota tampil di terminal, dipisahkan koma
 */

#endif