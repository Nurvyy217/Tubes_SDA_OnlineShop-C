#include <stdio.h>
#include "transitKota.h"
#include <string.h>
#include <stdlib.h>

// Node *nodes[100];
// int node_count = 0;

void InitTree(sqlite3 *db, TreeManager *tm) {
    int rc = sqlite3_open("nbtree.db", &db);
    if (rc) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    create_table_if_not_exists(db);
    insert_default_tree(db);
    load_tree(tm, db);

    sqlite3_close(db);
}



void PrintRuteKota(TreeManager *tm, const char *tujuan) {
    Node *target = find_node_by_name(tm, (char *)tujuan);
    print_route(target);
}

Node* find_node_by_name(TreeManager *tm, char *name) {
    for (int i = 0; i < tm->node_count; i++) {
        if (strcasecmp(tm->nodes[i]->name, name) == 0) return tm->nodes[i];
    }
    return NULL;
}

// Buat tabel nbtree jika belum ada
void create_table_if_not_exists(sqlite3 *db) {
    const char *sql =
        "CREATE TABLE IF NOT EXISTS nbtree ("
        "id INTEGER PRIMARY KEY, "
        "name TEXT NOT NULL, "
        "parent_id INTEGER, "
        "FOREIGN KEY(parent_id) REFERENCES nbtree(id));";
    char *errmsg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}

// Insert data default ke tabel
void insert_default_tree(sqlite3 *db) {
    const char *check_sql = "SELECT COUNT(*) FROM nbtree;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, check_sql, -1, &stmt, 0);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    if (count > 0) return;

    const char *insert_sql = "INSERT INTO nbtree (id, name, parent_id) VALUES (?, ?, ?);";
    sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);

    struct {
        int id;
        const char *name;
        int parent_id;
    } entries[] = {
        {1, "Bandung", 0},
        {2, "Cimahi", 1}, {3, "Sumedang", 1}, {4, "Garut", 1},
        {5, "Cianjur", 2}, {6, "Purwakarta", 2},
        {7, "Sukabumi", 5}, {8, "Bogor", 5},
        {9, "Depok", 8}, {10, "Jakarta", 9}, {11, "Tangerang", 10},
        {12, "Karawang", 6}, {13, "Subang", 6},
        {14, "Majalengka", 3}, {15, "Indramayu", 14},
        {16, "Tasik", 4}, {17, "Ciamis", 16}, {18, "Banjar", 17}, {19, "Pangandaran", 18}
    };

    for (int i = 0; i < sizeof(entries) / sizeof(entries[0]); i++) {
        sqlite3_bind_int(stmt, 1, entries[i].id);
        sqlite3_bind_text(stmt, 2, entries[i].name, -1, SQLITE_STATIC);
        if (entries[i].parent_id == 0)
            sqlite3_bind_null(stmt, 3);
        else
            sqlite3_bind_int(stmt, 3, entries[i].parent_id);
            sqlite3_step(stmt);
            sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
}

// Bangun tree dari hasil query
void load_tree(TreeManager *tm, sqlite3 *db) {
    const char *sql = "SELECT id, name, parent_id FROM nbtree;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Node *node = malloc(sizeof(Node));
        node->id = sqlite3_column_int(stmt, 0);
        strcpy(node->name, (const char *)sqlite3_column_text(stmt, 1));
        node->parent_id = sqlite3_column_type(stmt, 2) == SQLITE_NULL ? 0 : sqlite3_column_int(stmt, 2);
        node->parent = NULL;
        node->first_child = NULL;
        node->next_sibling = NULL;
        tm->nodes[tm->node_count++] = node;
    }
    sqlite3_finalize(stmt);

    // Bangun hubungan parent-child dan sibling
    for (int i = 0; i < tm->node_count; i++) {
        Node *child = tm->nodes[i];
        if (child->parent_id == 0) continue;

        Node *parent = NULL;
        for (int j = 0; j < tm->node_count; j++) {
            if (tm->nodes[j]->id == child->parent_id) {
                parent = tm->nodes[j];
                break;
            }
        }
        if (parent) {
            child->parent = parent;
            if (!parent->first_child) {
                parent->first_child = child;
            } else {
                Node *sibling = parent->first_child;
                while (sibling->next_sibling) {
                    sibling = sibling->next_sibling;
                }
                sibling->next_sibling = child;
            }
        }
    }
}

// Cetak rute dari root ke node tujuan
void print_route(Node *target) {
    if (!target) {
        printf("Node tidak ditemukan.\n");
        return;
    }

    Node *stack[100];
    int top = 0;

    while (target) {
        stack[top++] = target;
        target = target->parent;
    }

    for (int i = top - 1; i >= 0; i--) {
        printf("%s", stack[i]->name);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

// int main() {
//     sqlite3 *db;
//     int rc = sqlite3_open("nbtree.db", &db);
//     if (rc) {
//         fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
//         return 1;
//     }

//     create_table_if_not_exists(db);
//     insert_default_tree(db);
//     load_tree(db);

//     char tujuan[100];
//     printf("Masukkan kota tujuan: ");
//     scanf("%s", tujuan);

//     Node *target = find_node_by_name(tujuan);
//     print_route(target);

//     sqlite3_close(db);
//     return 0;
// }

