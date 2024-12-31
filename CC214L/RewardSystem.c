#include "CandyCompany.h"

void updateGoldFromCandy(Node *node)
{
    node->gold += 20;
}

void distributeCandy(Node *root, Node *parent)
{
    if (root == NULL || parent == NULL)
        return;

    distributeCandyUpward(root, parent);
    saveTree(root);
}

void distributeCandyUpward(Node *root, Node *startNode)
{
    if (root == NULL || startNode == NULL)
        return;

    Node *current = startNode;
    while (current != NULL)
    {
        current->candy++;
        updateGoldFromCandy(current);
        if (current == root)
            break;
        current = findParent(root, current);
    }
}

void addChildren(Node *parent, Node *root, int childGold)
{
    if (parent == NULL)
        return;

    if (parent->left != NULL && parent->right != NULL)
    {
        printf("'%s' has already reached max employees to hire.\n", parent->name);
    }

    else
    {
        char answer[4];
        int choice;
        printf("\nDo you want to hire employee(s) under '%s'? (yes/no):", parent->name);
        scanf("%s", answer);

        if (strcasecmp(answer, "yes") == 0)
        {
            printf("\nHow many employee/s will '%s' hire? (max of 2): ", parent->name);
            scanf("%d", &choice);

            if (choice == 1)
            {
                if (parent->left == NULL)
                {
                    char leftName[50];
                    printf("\nEnter name for left-hand man: ");
                    scanf("%s", leftName);

                    parent->left = createNode(leftName, childGold);

                    printf("Hired left-hand man '%s' with %d gold\n", leftName, childGold);
                    distributeCandy(root, parent);
                }

                else
                {
                    printf("'%s' already has a left-hand man\n", parent->name);

                    if (parent->right == NULL)
                    {
                        char rightName[50];
                        printf("\nEnter name for right-hand man: ");
                        scanf("%s", rightName);
                        parent->right = createNode(rightName, childGold);
                        printf("Hired right-hand man '%s' with %d gold\n", rightName, childGold);
                        distributeCandy(root, parent);
                    }

                    else
                    {
                        printf("'%s' already has a right-hand man\n", parent->name);
                    }
                }
            }

            if (choice == 2)
            {
                if (parent->left == NULL)
                {
                    char leftName[50];
                    printf("\nEnter name for left-hand man: ");
                    scanf("%s", leftName);

                    parent->left = createNode(leftName, childGold);

                    printf("Hired left-hand man '%s' with %d gold\n", leftName, childGold);
                    distributeCandy(root, parent);
                }

                else
                {
                    printf("'%s' already has a left-hand man\n", parent->name);
                }

                if (parent->right == NULL)
                {
                    char rightName[50];
                    printf("\nEnter name for right-hand man: ");
                    scanf("%s", rightName);
                    parent->right = createNode(rightName, childGold);
                    printf("Hired right-hand man '%s' with %d gold\n", rightName, childGold);
                    distributeCandy(root, parent);
                }

                else
                {
                    printf("'%s' already has a right-hand man\n", parent->name);
                }
            }
        }
    }

    if (parent->left != NULL)
    {
        addChildren(parent->left, root, childGold - 10);
    }

    if (parent->right != NULL)
    {
        addChildren(parent->right, root, childGold - 10);
    }

    saveTree(root);
}
