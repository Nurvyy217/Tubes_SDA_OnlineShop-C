#include <stdio.h>
#include "../include/stack.h"
#include <stdlib.h>
#include <string.h>

void CreateEmpty(Stack *S)
{
    Top(*S) = NULL;
}

void Push(Stack *S, Node *tree) {
    addressStack newNode = (addressStack)malloc(sizeof(StackNode));
    if (newNode != NULL) {
        strcpy(City(newNode), tree->name);
        Next(newNode) = Top(*S);
        Top(*S) = newNode;
    }
}

void Pop(Stack *S) {
    if (Top(*S) == NULL) return;
    addressStack temp = Top(*S);
    printf("%s", City(temp)); 
    Top(*S) = Next(temp);
    free(temp);
}

void print_route(Node *target)
{
     if (!target)
    {
        printf("Node tidak ditemukan.\n");
        return;
    }

    Stack S;
    CreateEmpty(&S);

    Node *temp = target;
    while (temp) {
        Push(&S, temp);
        temp = temp->parent;
    }
    int first = 1;
    while (Top(S)) {
        if (!first) printf(" -> ");
        Pop(&S);
        first = 0;
    }
    printf("\n");
}

void PrintRuteKota(TreeManager *tm, const char *tujuan)
{
    Node *target = find_node_by_name(tm, (char *)tujuan);
    print_route(target);
}