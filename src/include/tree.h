#ifndef TRANSIT_KOTA_H
#define TRANSIT_KOTA_H

#define TREE_FILE "data/tree.txt"
#define MAX_WIDTH 200

typedef struct TreeNode {
    int id;
    char name[100];
    int parent_id;
    struct TreeNode *parent;
    struct TreeNode *first_child;
    struct TreeNode *next_sibling;
} TreeNode;

typedef struct {
    TreeNode *nodes[100];
    int node_count;
} TreeManager;


void InitTree(TreeManager *tm);
void load_tree(TreeManager *tm);
TreeNode* find_node_by_name(TreeManager *tm, char *name);
void save_tree(TreeManager *tm);
void insert_default_tree(TreeManager *tm);
void print_tree_horizontal_centered(TreeManager *tm);
int print_tree_centered(TreeNode *node, char canvas[][MAX_WIDTH], int row, int col);
void print_at(char canvas[][MAX_WIDTH], int row, int col, const char *text);
int subtree_width(TreeNode *node);
#endif