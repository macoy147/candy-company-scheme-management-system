#ifndef CANDY_COMPANY_H
#define CANDY_COMPANY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Structure definition
typedef struct Node
{
    char name[50];
    int gold;
    int candy;
    struct Node *left;
    struct Node *right;
} Node;

// Interface functions
void typePrint(const char *text, useconds_t delay);
void clearScreen(void);
void loadingScreen(void);
int displayMenu(void);
void displayTree(Node *root);

// Tree Operations
Node *createNode(char *name, int gold);
Node *findNode(Node *root, const char *name);
void freeNode(Node *node);
Node *removeEmployee(Node *root, const char *name);
Node *findParent(Node *root, Node *target);
void searchNode(Node *root, char *name);

// Reward System
void updateGoldFromCandy(Node *node);
void distributeCandyUpward(Node *root, Node *startNode);
void distributeCandy(Node *root, Node *parent);
void addChildren(Node *parent, Node *root, int childGold);

// File Handling
void writeNode(FILE *file, Node *node, char *parentName, char *position);
void saveTreeToFile(Node *root, FILE *file, char *parentName, char *position);
void saveTree(Node *root);
Node *loadTreeFromFile(void);

#endif