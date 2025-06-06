#ifndef STACK_H
#define STACK_H

#define City(N) (N)->city
#define Next(N) (N)->next
#define Top(S) (S).Top
#include "tree.h"

typedef struct StackNode *addressStack;

typedef struct StackNode
{
    char city[100];
    addressStack next;
} StackNode;

typedef struct Stack
{
    addressStack Top;
} Stack;

void CreateEmpty(Stack *S);
/*
 * Membuat stack kosong
 * IS : Stack belum tentu kosong
 * FS : Stack dijamin kosong (Top = NULL)
 */

void Push(Stack *S, TreeNode *tree);
/*
 * Menambahkan nama kota dari node tree ke stack 
 * IS : Stack bisa kosong atau berisi data
 * FS : Stack bertambah satu node di atas berisi nama kota dari tree
 */

void Pop(Stack *S);
/*
 * Menghapus node paling atas stack dan menampilkan nama kota
 * IS : Stack bisa kosong atau berisi data
 * FS : Node paling atas dihapus, nama kota dicetak, memori node dibebaskan
 */

void print_route(TreeNode *target);
/*
 * Menampilkan rute dari root ke node target menggunakan stack
 * IS : Stack kosong, node target valid
 * FS : Rute dari root ke target dicetak ke layar dengan urutan yang benar
 */

#endif