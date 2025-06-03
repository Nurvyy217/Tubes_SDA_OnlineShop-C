#ifndef TRANSIT_KOTA_H
#define TRANSIT_KOTA_H

#define TREE_FILE "data/tree.txt"

typedef struct Node {
    int id;
    char name[100];
    int parent_id;
    struct Node *parent;
    struct Node *first_child;
    struct Node *next_sibling;
} Node;

typedef struct {
    Node *nodes[100];
    int node_count;
} TreeManager;


void InitTree(TreeManager *tm);
void load_tree(TreeManager *tm);
Node* find_node_by_name(TreeManager *tm, char *name);
void save_tree(TreeManager *tm);
void insert_default_tree(TreeManager *tm);

#endif