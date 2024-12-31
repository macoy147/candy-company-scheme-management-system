#include "CandyCompany.h"

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
            addChildren(root, root, 90);
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

                searchNode(root, searchName);
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