#include "CandyCompany.h"

void writeNode(FILE *file, Node *node, char *parentName, char *position)
{
    fprintf(file, "%s,%s,%s,%d,%d\n", parentName ? parentName : "NULL", position ? position : "NULL", node->name, node->gold, node->candy);
}

void saveTreeToFile(Node *root, FILE *file, char *parentName, char *position)
{
    if (root == NULL)
        return;

    writeNode(file, root, parentName, position);
    saveTreeToFile(root->left, file, root->name, "left");
    saveTreeToFile(root->right, file, root->name, "right");
}

void saveTree(Node *root)
{
    if (root == NULL)
        return;

    FILE *file = fopen("candyDatabase.txt", "w");

    if (file == NULL)
    {
        printf("Error opening the file!\n");
        return;
    }

    saveTreeToFile(root, file, NULL, NULL);
    fclose(file);
}

Node *loadTreeFromFile()
{
    FILE *file = fopen("candyDatabase.txt", "r");
    if (file == NULL)
        return NULL;

    Node *root = NULL;
    char line[256];
    char parentName[50], position[10], name[50];
    int gold, candy;

    if (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d",
               parentName, position, name, &gold, &candy);
        root = createNode(name, gold);
        root->candy = candy;
    }

    rewind(file);

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d",
               parentName, position, name, &gold, &candy);

        if (strcmp(parentName, "NULL") == 0)
            continue;

        Node *parent = findNode(root, parentName);
        if (parent != NULL)
        {
            Node *newNode = createNode(name, gold);
            newNode->candy = candy;

            if (strcmp(position, "left") == 0)
                parent->left = newNode;
            else if (strcmp(position, "right") == 0)
                parent->right = newNode;
        }
    }

    fclose(file);
    return root;
}
