#include "CandyCompany.h"

Node *createNode(char *name, int gold)
{
    Node *newNode = malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->gold = gold;
    newNode->candy = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *findNode(Node *root, const char *name)
{
    if (root == NULL || strcmp(root->name, name) == 0)
        return root;

    Node *left = findNode(root->left, name);
    if (left != NULL)
        return left;

    return findNode(root->right, name);
}

void freeNode(Node *node)
{
    if (node == NULL)
        return;

    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

Node *removeEmployee(Node *root, const char *name)
{
    if (root == NULL)
        return NULL;

    if (root->left != NULL)
    {
        if (strcasecmp(root->left->name, name) == 0)
        {
            freeNode(root->left);
            root->left = NULL;
            return root;
        }
        root->left = removeEmployee(root->left, name);
    }

    if (root->right != NULL)
    {
        if (strcasecmp(root->right->name, name) == 0)
        {
            freeNode(root->right);
            root->right = NULL;
            return root;
        }
        root->right = removeEmployee(root->right, name);
    }

    if (strcasecmp(root->name, name) == 0)
    {
        freeNode(root);
        return NULL;
    }

    return root;
}

Node *findParent(Node *root, Node *target)
{
    if (root == NULL || root->left == target || root->right == target)
        return root;

    Node *left = findParent(root->left, target);
    if (left != NULL)
        return left;

    return findParent(root->right, target);
}

void searchNode(Node *root, char *name)
{
    if (root == NULL)
        return;

    if (strcasecmp(root->name, name) == 0)
    {
        printf("\n'%s' - Total Gold: %d, Total Candy: %d\n", root->name, root->gold, root->candy);
        return;
    }

    else
    {
        searchNode(root->left, name);
        searchNode(root->right, name);
    }
}
