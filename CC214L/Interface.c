#include "CandyCompany.h"

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

void displayTree(Node *root)
{
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

    if (root->left)
        displayTree(root->left);
    if (root->right)
        displayTree(root->right);
}
