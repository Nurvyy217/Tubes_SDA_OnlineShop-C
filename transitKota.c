#include <stdio.h>
#include "transitKota.h"
#include <string.h>
#include <stdlib.h>

#define TREE_FILE "tree.txt"

void InitTree(TreeManager *tm) {
    // Initialize the TreeManager
    tm->node_count = 0;
    
    // Check if file exists
    FILE *file = fopen(TREE_FILE, "r");
    if (!file) {
        // File doesn't exist, create default tree and save it
        insert_default_tree(tm);
        save_tree(tm);
    } else {
        // Check if file is empty
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fclose(file);
        
        if (fileSize == 0) {
            // File exists but is empty, create default tree
            insert_default_tree(tm);
            save_tree(tm);
        } else {
            // File exists and has content, load the tree
            load_tree(tm);
        }
    }
}

void save_tree(TreeManager *tm) {
    FILE *file = fopen(TREE_FILE, "w");
    if (!file) {
        printf("Error: Cannot open tree file for writing\n");
        return;
    }

    for (int i = 0; i < tm->node_count; i++) {
        fprintf(file, "%d,%s,%d\n", 
            tm->nodes[i]->id,
            tm->nodes[i]->name,
            tm->nodes[i]->parent_id);
    }

    fclose(file);
}

void load_tree(TreeManager *tm) {
    FILE *file = fopen(TREE_FILE, "r");
    if (!file) {
        printf("Error: Cannot open tree file\n");
        return;
    }

    // Clear existing nodes
    for (int i = 0; i < tm->node_count; i++) {
        free(tm->nodes[i]);
    }
    tm->node_count = 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Node *node = malloc(sizeof(Node));
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

void insert_default_tree(TreeManager *tm) {
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

    for (size_t i = 0; i < sizeof(entries) / sizeof(entries[0]); i++) {
        Node *node = malloc(sizeof(Node));
        node->id = entries[i].id;
        strcpy(node->name, entries[i].name);
        node->parent_id = entries[i].parent_id;
        node->parent = NULL;
        node->first_child = NULL;
        node->next_sibling = NULL;
        tm->nodes[tm->node_count++] = node;
    }
}

Node* find_node_by_name(TreeManager *tm, char *name) {
    for (int i = 0; i < tm->node_count; i++) {
        if (strcasecmp(tm->nodes[i]->name, name) == 0) return tm->nodes[i];
    }
    return NULL;
}

void print_route(Node *target) {
    if (!target) {
        printf("Node tidak ditemukan.\n");
        return;
    }

    int depth = 0;
    Node *temp = target;
    while (temp) {
        depth++;
        temp = temp->parent;
    }

    Node *stack[depth];

    depth = 0;
    while (target) {
        stack[depth++] = target;
        target = target->parent;
    }

    for (int i = depth - 1; i >= 0; i--) {
        printf("%s", stack[i]->name);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

void PrintRuteKota(TreeManager *tm, const char *tujuan) {
    Node *target = find_node_by_name(tm, (char *)tujuan);
    print_route(target);
}