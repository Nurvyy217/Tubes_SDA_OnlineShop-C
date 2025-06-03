#include <stdio.h>
#include "../include/tree.h"
#include <string.h>
#include <stdlib.h>
#include "../include/stack.h"


void InitTree(TreeManager *tm)
{
    // Initialize the TreeManager
    tm->node_count = 0;

    // Check if file exists
    FILE *file = fopen(TREE_FILE, "r");
    if (!file)
    {
        // File doesn't exist, create default tree and save it
        insert_default_tree(tm);
        save_tree(tm);
    }
    else
    {
        // Check if file is empty
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fclose(file);

        if (fileSize == 0)
        {
            // File exists but is empty, create default tree
            insert_default_tree(tm);
            save_tree(tm);
        }
        else
        {
            // File exists and has content, load the tree
            load_tree(tm);
        }
    }
}

void save_tree(TreeManager *tm)
{
    FILE *file = fopen(TREE_FILE, "w");
    if (!file)
    {
        printf("Error: Cannot open tree file for writing\n");
        return;
    }

    for (int i = 0; i < tm->node_count; i++)
    {
        fprintf(file, "%d,%s,%d\n",
                tm->nodes[i]->id,
                tm->nodes[i]->name,
                tm->nodes[i]->parent_id);
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

    // Clear existing nodes
    for (int i = 0; i < tm->node_count; i++)
    {
        free(tm->nodes[i]);
    }
    tm->node_count = 0;

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        TreeNode *node = malloc(sizeof(TreeNode));
        sscanf(line, "%d,%[^,],%d",
               &node->id,
               node->name,
               &node->parent_id);

        node->parent = NULL;
        node->first_child = NULL;
        node->next_sibling = NULL;
        tm->nodes[tm->node_count++] = node;
    }
    fclose(file);

    // Build parent-child and sibling relationships
    for (int i = 0; i < tm->node_count; i++)
    {
        TreeNode *child = tm->nodes[i];
        if (child->parent_id == 0)
            continue;

        TreeNode *parent = NULL;
        for (int j = 0; j < tm->node_count; j++)
        {
            if (tm->nodes[j]->id == child->parent_id)
            {
                parent = tm->nodes[j];
                break;
            }
        }
        if (parent)
        {
            child->parent = parent;
            if (!parent->first_child)
            {
                parent->first_child = child;
            }
            else
            {
                TreeNode *sibling = parent->first_child;
                while (sibling->next_sibling)
                {
                    sibling = sibling->next_sibling;
                }
                sibling->next_sibling = child;
            }
        }
    }
}

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
        TreeNode *node = malloc(sizeof(TreeNode));
        node->id = entries[i].id;
        strcpy(node->name, entries[i].name);
        node->parent_id = entries[i].parent_id;
        node->parent = NULL;
        node->first_child = NULL;
        node->next_sibling = NULL;
        tm->nodes[tm->node_count++] = node;
    }
}

TreeNode *find_node_by_name(TreeManager *tm, char *name)
{
    for (int i = 0; i < tm->node_count; i++)
    {
        if (strcasecmp(tm->nodes[i]->name, name) == 0)
            return tm->nodes[i];
    }
    return NULL;
}


// Helper untuk mendapatkan lebar subtree
int subtree_width(TreeNode *node) {
    if (!node) return 0;
    if (!node->first_child) return (int)strlen(node->name);
    int width = 0;
    TreeNode *child = node->first_child;
    while (child) {
        width += subtree_width(child) + 4; // 4 spasi antar anak
        child = child->next_sibling;
    }
    return width;
}

// Print node pada posisi tertentu
void print_at(char canvas[][MAX_WIDTH], int row, int col, const char *text) {
    for (int i = 0; text[i] && col + i < MAX_WIDTH; i++)
        canvas[row][col + i] = text[i];
}

// Recursive print
int print_tree_centered(TreeNode *node, char canvas[][MAX_WIDTH], int row, int col) {
    if (!node) return 0;
    int name_len = (int)strlen(node->name);

    // Hitung total width subtree
    int total_width = subtree_width(node);
    if (total_width < name_len) total_width = name_len;

    // Posisi node di tengah subtree
    int node_col = col + total_width / 2 - name_len / 2;
    print_at(canvas, row, node_col, node->name);

    // Print garis ke anak-anak
    TreeNode *child = node->first_child;
    int child_col = col;
    while (child) {
        int child_width = subtree_width(child);
        int child_name_len = (int)strlen(child->name);
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
        child = child->next_sibling;
    }
    return total_width;
}

void print_tree_horizontal_centered(TreeManager *tm) {
    // Cari root
    TreeNode *root = NULL;
    for (int i = 0; i < tm->node_count; i++) {
        if (tm->nodes[i]->parent_id == 0) {
            root = tm->nodes[i];
            break;
        }
    }
    if (!root) return;

    // Siapkan canvas kosong
    char canvas[40][MAX_WIDTH];
    for (int i = 0; i < 40; i++)
        for (int j = 0; j < MAX_WIDTH; j++)
            canvas[i][j] = ' ';

    print_tree_centered(root, canvas, 0, 0);

    // Print canvas
    for (int i = 0; i < 40; i++) {
        int last = MAX_WIDTH - 1;
        while (last >= 0 && canvas[i][last] == ' ') last--;
        if (last > 0)
            printf("%.*s\n", last + 1, canvas[i]);
    }
}