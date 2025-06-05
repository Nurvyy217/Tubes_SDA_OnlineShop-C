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

void Push(Stack *S, TreeNode *tree);
void Pop(Stack *S);
void CreateEmpty(Stack *S);
void print_route(TreeNode *target);

#endif