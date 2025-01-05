#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void typePrint(const char *text, useconds_t delay)
{
    while (*text)
    {
        putchar(*text++);
        fflush(stdout);
        usleep(delay);
    }
}

void clearScreen()
{   
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void loadingScreen()
{
    const char *loadingText = "Setting up";
    const int barLength = 30; // Length of the progress bar
    

    printf("\n\n\n");

    for (int i = 0; i <= barLength; i++)
    {
        // Display progress bar
        printf("\r[");
        for (int j = 0; j < barLength; j++)
        {
            if (j < i)
            {
                printf("#"); // Completed part of the bar
            }
            else
            {
                printf(" "); // Remaining part of the bar
            }
        }
        printf("] %d%% ", (i * 100) / barLength); // Display percentage

        printf("%s", loadingText);

        // Cycle of dots
        for (int k = 0; k < (i % 3) + 1; k++)
        {
            printf(".");
            fflush(stdout);
            usleep(100000);
        }

        // Clear the dots after animation for next cycle
        printf("\r");
        for (int j = 0; j < 50; j++)
            printf(" ");
        printf("\r");
        fflush(stdout);
    }
    sleep(1);

    printf("Setup Complete!\n");
    sleep(1.5);

    
    clearScreen();

    printf("\n\n\n");
    printf("=========================================\n");
    printf("       WELCOME TO THE \"CANDY COMPANY       \n");
    printf("         SCHEME MANAGEMENT SYSTEM\"                  \n");
    printf("=========================================\n\n");
    sleep(1.5);

    clearScreen();

    printf("\n\n\n");
    printf("=========================================\n");
    printf("         BSIT 2A DSA FINAL PROJECT       \n");
    printf("=========================================\n");
    printf("                 BY:                     \n");
    printf("     Marco Montellano                \n");
    printf("     Fanny Rose Caballes                 \n");
    printf("     Benjie Sumile                   \n");
    printf("     Angel Mae Santosidad                \n");
    printf("     Hazzel Canama                   \n");
    printf("     Vincent Bernabe Romeo                \n");
    printf("     Justin Dumon                    \n");
    printf("=========================================\n\n");
    

    sleep(3);
}

    typedef struct Node
{
    char name[50];
    int gold;
    int candy;
    struct Node *left;
    struct Node *right;
} Node;

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

Node *findNode(Node *root, const char *name)
{
    if (root == NULL || strcmp(root->name, name) == 0)
        return root;

    Node *left = findNode(root->left, name);
    if (left != NULL)
        return left;

    return findNode(root->right, name);
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

void freeNode(Node *node) {
    if (node == NULL) return;
    
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

Node* removeEmployee(Node* root, const char* name) {
    if (root == NULL) return NULL;

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

void updateGoldFromCandy(Node *node)
{
    node->gold += 20;
}

void distributeCandyUpward(Node *root, Node *parent)
{
    if (root == NULL || parent == NULL)
        return;

    Node *current = parent;

    while (current != NULL)
    {
        current->candy++;

        updateGoldFromCandy(current); 

        if (current == root)
            break;

        current = findParent(root, current);
    }
}

void distributeCandy(Node *root, Node *parent)
{
    if (root == NULL || parent == NULL)
        return;

    distributeCandyUpward(root, parent);

    saveTree(root);
}


void displayTree(Node *root) {
    if (root == NULL)
        return;

    char buffer[256];

    snprintf(buffer, sizeof(buffer), "\n'%s' - Total Gold: %d, Total Candy: %d\n", root->name, root->gold, root->candy);
    typePrint(buffer, 1000);

    snprintf(buffer, sizeof(buffer), "    Left-hand: '%s' ", root->left ? root->left->name : "[VACANT]");
    typePrint(buffer, 1000);

    if (root->left) 
    {
        snprintf(buffer, sizeof(buffer), "Gold: %d, Candy: %d\n", root->left->gold, root->left->candy);
        typePrint(buffer, 1000);
    }

    snprintf(buffer, sizeof(buffer), "    Right-hand: '%s' ", root->right ? root->right->name : "[VACANT]");
    typePrint(buffer, 1000);

    if (root->right) 
    {
        snprintf(buffer, sizeof(buffer), "Gold: %d, Candy: %d",
                 root->right->gold, root->right->candy);
        typePrint(buffer, 1000);
    }
    

    typePrint("\n", 100000);
    
    if (root->left) displayTree(root->left);
    if (root->right) displayTree(root->right);
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

void searchNode(Node *root, char *name, int *found)
{
    if (root == NULL)
        return;

    if (strcasecmp(root->name, name) == 0)
    {
        printf("\n'%s' - Total Gold: %d, Total Candy: %d\n", root->name, root->gold, root->candy);
        *found = 1;
        return;
    }

    searchNode(root->left, name, found);
    searchNode(root->right, name, found);
}

int displayMenu()
{
    int choice;
    printf("\n\n\n======== Company Menu ========\n");
    printf(" 1. Display Company Structure\n");
    printf(" 2. Add New Employee\n");
    printf(" 3. Search for an Employee\n");
    printf(" 4. Remove an Employee\n");
    printf(" 5. Exit\n");
    printf(" Input Choice (1-5): ");
    scanf("%d", &choice);

    return choice;
}

int main()
{
    clearScreen();
    loadingScreen();

    Node *root = NULL;
    char choice;
    int menuChoice;

    root = loadTreeFromFile();

    if (root == NULL)
    {
        clearScreen();
        printf("\n\nNo existing CEO found. Do you want to hire one? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y')
        {
            char rootName[50];
            printf("\nEnter name for the CEO: ");
            scanf("%s", rootName);

            root = createNode(rootName, 100);

            printf("'%s' is hired with %d gold\n", rootName, root->gold);

            saveTree(root);

           // addChildren(root, root, 90);
        }

        printf("\n\nPress [ENTER] to Proceed...");
        getchar();
        getchar();
    }

    while (1)
    {
        clearScreen();
        menuChoice = displayMenu();

        switch (menuChoice)
        {
            case 1:
                clearScreen();
                if (root == NULL)
                {
                    printf("\nNo data exists! Please hire employees first.\n");
                }

                else
                {
                    printf("\nCurrent Company Structure:\n");
                    displayTree(root);
                }
                
                sleep(1);
                printf("\n\nPress [ENTER] to Proceed...");
                getchar();
                getchar();
                break;

            case 2:
                clearScreen();
                if (root == NULL)
                {
                    printf("No data exists! ");

                    usleep(500000);

                    printf("Hiring a new CEO");
                    for (int i = 1; i <= 3; i++)
                    {
                        printf(".");
                        usleep(500000);
                    }

                    printf("\nEnter name for the CEO: ");
                    char rootName[50];
                    scanf("%s", rootName);

                    root = createNode(rootName, 100);

                    printf("'%s' is hired with %d gold\n", rootName, root->gold);

                    saveTree(root);

                    printf("\n\nPress [ENTER] to Proceed...");
                    getchar();
                    getchar();
                }

                else
                {
                    addChildren(root, root, 90);

                    saveTree(root);

                    printf("\n\nPress [ENTER] to Proceed...");
                    getchar();
                    getchar();
                }
                
                break;

            case 3:
                clearScreen();
                if (root == NULL)
                {
                    printf("No data exists! Please hire employees first.\n");
                }
                else
                {
                    char searchName[50];
                    printf("Enter the name of the employee to search: ");
                    scanf("%s", searchName);

                    printf("\nSearching for '%s'", searchName);
                    for (int i = 1; i <= 3; i++)
                    {
                        printf(".");
                        usleep(500000);
                    }
                    printf("\n");

                    int found = 0; 

                    searchNode(root, searchName, &found);

                    if (!found )// same sa found == 0
                    {
                        printf("\nEmployee '%s' not found in the company.\n", searchName);
                    }
                }
                printf("\n\nPress [ENTER] to Proceed...");
                getchar();
                getchar();
                break;

            case 4:
                clearScreen();

                if (root == NULL)
                {
                    printf("No data exists! Please hire employees first.\n");
                }
                else
                {
                    char removeName[50];
                    printf("Enter the name of the employee to remove: ");
                    scanf("%s", removeName);

                    // Don't allow removing the CEO if they have employees
                    if (strcasecmp(root->name, removeName) == 0 && (root->left != NULL || root->right != NULL))
                    {
                        printf("\nCannot remove the CEO while they have employees!\n");
                        printf("Please remove all subordinates first.\n");
                    }

                    else
                    {
                        printf("\nWarning: Removing '%s' will also remove all their subordinates.", removeName);
                        printf("\nAre you sure you want to proceed? (y/n): ");
                        char confirm;
                        scanf(" %c", &confirm);

                        if (confirm == 'y' || confirm == 'Y')
                        {
                            printf("\nRemoving '%s'", removeName);

                            for (int i = 1; i <= 3; i++)
                            {
                                printf(".");
                                usleep(500000);
                            }

                            printf("\n");

                            Node *result = removeEmployee(root, removeName);

                            if (result != root)
                            { 
                                root = result;
                                if (root == NULL)
                                {
                                    printf("\nCompany is now empty. All employees have been removed.\n");
                                    remove("candyDatabase.txt");
                                }
                                else
                                {
                                    printf("\n'%s' and their subordinates have been removed.\n", removeName);
                                    saveTree(root);
                                }
                            }

                            else
                            {
                                printf("\n'%s' and their subordinates have been removed.\n", removeName);
                                saveTree(root);
                            }
                        }
                        else
                        {
                            printf("\nCancelling");
                            for (int i = 1; i <= 3; i++)
                            {
                                printf(".");
                                usleep(500000);
                            }
                            printf("\nRemoval cancelled.\n");
                        }
                    }
                }
                
                printf("\n\nPress [ENTER] to Proceed...");
                getchar();
                getchar();
                break;

            case 5:
                printf("\nExiting Program");
                for (int i = 1; i <= 3; i++)
                {
                    printf(".");
                    usleep(500000);
                }
                printf("\n");
                printf("\nData has been saved!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
                printf("\n\nPress [ENTER] to Proceed...");
                getchar();
                getchar();
            }
    }

    return 0;
}