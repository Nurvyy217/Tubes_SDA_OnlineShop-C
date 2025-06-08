// ...existing code...
#include <stdio.h>
#include "../include/tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/stack.h"

// Inisialisasi Tree
void InitTree(TreeManager *tm)
{
    NodeCount((*tm)) = 0;

    // Check file ada atau tidak
    FILE *file = fopen(TREE_FILE, "r");
    if (!file)
    {
        // Jika file tidak ada, buat file baru dan isi dengan data default
        insert_default_tree(tm);
        save_tree(tm);
        load_tree(tm);
    }
    else
    {
        // Jika file ada, cek apakah kosong atau tidak
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fclose(file);

        if (fileSize == 0)
        {
            // Jika file kosong, isi dengan data default
            insert_default_tree(tm);
            save_tree(tm);
            load_tree(tm);
        }
        else
        {
            // Jika file tidak kosong, muat tree dari file
            load_tree(tm);
        }
    }
}

// Menyimpan tree dari TreeManager ke file
void save_tree(TreeManager *tm)
{
    FILE *file = fopen(TREE_FILE, "w");
    if (!file)
    {
        printf("Error: Cannot open tree file for writing\n");
        return;
    }

    // Memasukkan data node dari TreeManager ke file
    for (int i = 0; i < NodeCount((*tm)); i++)
    {
        fprintf(file, "%d,%s,%d\n",
                Id(Nodes((*tm))[i]),
                Name(Nodes((*tm))[i]),
                ParentId(Nodes((*tm))[i]));
    }

    fclose(file);
}

void load_tree(TreeManager *tm)
{
    FILE *file = fopen(TREE_FILE, "r");
    if (!file)
    {
        printf("Error: Cannot open tree file\n");
        return;
    }

    // Kosongkan TreeManager sebelum memuat data baru
    for (int i = 0; i < NodeCount((*tm)); i++)
    {
        free(Nodes((*tm))[i]);
    }
    NodeCount((*tm)) = 0;

    // Mengisi TreeManager dengan data dari file
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        addressTree node = malloc(sizeof(TreeNode));
        sscanf(line, "%d,%[^,],%d",
               &Id(node),
               Name(node),
               &ParentId(node));

        Parent(node) = NULL;
        FirstChild(node) = NULL;
        NextSibling(node) = NULL;
        Nodes((*tm))[NodeCount((*tm))++] = node;
    }
    fclose(file);

    // Membuat relasi parent-child dan brother-sibling
    for (int i = 0; i < NodeCount((*tm)); i++)
    {
        addressTree child = Nodes((*tm))[i];
        if (ParentId(child) == 0)
            continue;

        addressTree parent = NULL;
        for (int j = 0; j < NodeCount((*tm)); j++)
        {
            if (Id(Nodes((*tm))[j]) == ParentId(child))
            {
                parent = Nodes((*tm))[j];
                break;
            }
        }
        if (parent) //jika parent tidak NULL
        {
            Parent(child) = parent;
            if (!FirstChild(parent)) //Jika parent belum punya anak (NULL)
            {
                FirstChild(parent) = child;
            }
            else //Jika parent sudah punya anak
            {
                addressTree sibling = FirstChild(parent);
                while (NextSibling(sibling)) //selama nextSibling tidak NULL
                {
                    sibling = NextSibling(sibling);
                }
                NextSibling(sibling) = child; // Menambahkan child sebagai sibling terakhir
            }
        }
    }
}

// Memasukkan data default ke dalam TreeManager tapi belum ada relasi parent-child
void insert_default_tree(TreeManager *tm)
{
    struct
    {
        int id;
        const char *name;
        int parent_id;
    } entries[] = {
        {1, "Bandung", 0},
        {2, "Cimahi", 1},
        {3, "Sumedang", 1},
        {4, "Garut", 1},
        {5, "Cianjur", 2},
        {6, "Purwakarta", 2},
        {7, "Sukabumi", 5},
        {8, "Bogor", 5},
        {9, "Depok", 8},
        {10, "Jakarta", 9},
        {11, "Tangerang", 10},
        {12, "Karawang", 6},
        {13, "Subang", 6},
        {14, "Majalengka", 3},
        {15, "Indramayu", 14},
        {16, "Tasik", 4},
        {17, "Ciamis", 16},
        {18, "Banjar", 17},
        {19, "Pangandaran", 18}};

    for (size_t i = 0; i < sizeof(entries) / sizeof(entries[0]); i++)
    {
        addressTree node = malloc(sizeof(TreeNode));
        Id(node) = entries[i].id;
        strcpy(Name(node), entries[i].name);
        ParentId(node) = entries[i].parent_id;
        Parent(node) = NULL;
        FirstChild(node) = NULL;
        NextSibling(node) = NULL;
        Nodes((*tm))[NodeCount((*tm))++] = node; // Menambahkan node ke dalam array nodes TreeManager
    }
}


// Mencari node berdasarkan nama kota menggunakan traversal pre order
addressTree find_node_by_name(TreeManager *tm, char *name)
{
    // Cari root (parent_id == 0)
    addressTree root = NULL;
    for (int i = 0; i < NodeCount((*tm)); i++) {
        if (ParentId(Nodes((*tm))[i]) == 0) {
            root = Nodes((*tm))[i];
            break;
        }
    }
    if (!root) return NULL;

    addressTree temp = root;
    bool flag = true; // boolean: 0 = resmi (masuk child), 1 = kembali ke parent
    while (temp) { 
    //selama temp tidak null
        if (strcasecmp(Name(temp), name) == 0) //jika nama ditemukan, langsung return node
            return temp;

        
        if (FirstChild(temp) && flag) { // jika ada anak dan belum kembali
            temp = FirstChild(temp);
        } else if (NextSibling(temp)) {
            temp = NextSibling(temp);
            flag = true;
        } else {
            temp = Parent(temp);
            flag = false;
        }
    }
    return NULL;
}

int subtree_width(addressTree node) {
    if (!node) return 0;
    if (!FirstChild(node)) return (int)strlen(Name(node));
    int width = 0;
    addressTree child = FirstChild(node);
    while (child) {
        width += subtree_width(child) + 4; // 4 spasi antar anak
        child = NextSibling(child);
    }
    return width;
}

void print_tree_at(char canvas[][MAX_WIDTH], int row, int col, const char *text) {
    for (int i = 0; text[i] && col + i < MAX_WIDTH; i++)
        canvas[row][col + i] = text[i];
}

int print_tree_centered(addressTree node, char canvas[][MAX_WIDTH], int row, int col) {
    if (!node) return 0;
    int name_len = (int)strlen(Name(node));

    // Hitung total width subtree
    int total_width = subtree_width(node);
    if (total_width < name_len) total_width = name_len;

    // Posisi node di tengah subtree
    int node_col = col + total_width / 2 - name_len / 2;
    print_tree_at(canvas, row, node_col, Name(node));

    // Print garis ke anak-anak
    addressTree child = FirstChild(node);
    int child_col = col;
    while (child) {
        int child_width = subtree_width(child);
        int child_name_len = (int)strlen(Name(child));
        int child_node_col = child_col + child_width / 2 - child_name_len / 2;

        // Garis vertikal dari parent ke child
        int parent_mid = node_col + name_len / 2;
        int child_mid = child_node_col + child_name_len / 2;
        int line_row = row + 1;
        if (parent_mid == child_mid) {
            canvas[line_row][parent_mid] = '|';
        } else {
            // Garis miring/horisontal
            int start = parent_mid < child_mid ? parent_mid : child_mid;
            int end = parent_mid > child_mid ? parent_mid : child_mid;
            for (int i = start; i <= end; i++)
                canvas[line_row][i] = '-';
            canvas[line_row][parent_mid] = '+';
            canvas[line_row][child_mid] = '+';
            canvas[line_row + 1][child_mid] = '|';
        }

        // Rekursif ke anak
        print_tree_centered(child, canvas, row + 2, child_col);
        child_col += child_width + 4;
        child = NextSibling(child);
    }
    return total_width;
}

void print_tree_horizontal_centered(TreeManager *tm) {
    addressTree root = NULL;
    for (int i = 0; i < NodeCount((*tm)); i++) {
        if (ParentId(Nodes((*tm))[i]) == 0) {
            root = Nodes((*tm))[i];
            break;
        }
    }
    if (!root) return;

    char canvas[40][MAX_WIDTH];
    for (int i = 0; i < 40; i++)
        for (int j = 0; j < MAX_WIDTH; j++)
            canvas[i][j] = ' ';

    print_tree_centered(root, canvas, 0, 0);

    for (int i = 0; i < 40; i++) {
        int last = MAX_WIDTH - 1;
        while (last >= 0 && canvas[i][last] == ' ') last--;
        if (last > 0)
            printf("%.*s\n", last + 1, canvas[i]);
    }
}

void showCityList(TreeManager *tm) {
    printf("Daftar kota yang tersedia:\n");
    for (int i = 0; i < NodeCount((*tm)); i++) {
        printf("%s", Name(Nodes((*tm))[i]));
        if (i < NodeCount((*tm)) - 1) printf(", ");
    }
    printf("\n");
}
