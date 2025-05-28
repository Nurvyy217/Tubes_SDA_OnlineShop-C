// #ifndef TRANSIT_KOTA_H
// #define TRANSIT_KOTA_H

// #include "sqlite3.h"

// typedef struct Node {
//     int id;
//     char name[100];
//     int parent_id;
//     struct Node *parent;
//     struct Node *first_child;
//     struct Node *next_sibling;
// } Node;

// typedef struct {
//     Node *nodes[100];
//     int node_count;
// } TreeManager;

// void InitTree(sqlite3 **db, TreeManager *tm);
// void create_table_if_not_exists(sqlite3 *db);
// void insert_default_tree(sqlite3 *db);
// void load_tree(TreeManager *tm, sqlite3 *db);
// Node* find_node_by_name(TreeManager *tm, char *name);
// void print_route(Node *target);
// void PrintRuteKota(TreeManager *tm, const char *tujuan);

// #endif