#include <stdio.h>
#include "single_slit.h"
#include "n_slit.h"

int main(void)
{
    int choice;

    while (1)
    {
        printf("\n================================\n");
        printf("       DIFFRACTION LAB\n");
        printf("================================\n");

        printf("1. Single-Slit Diffraction\n");
        printf("2. N-Slit Diffraction\n");
        printf("3. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            single_slit_simulation();
        }
        else if (choice == 2)
        {
            n_slit_simulation();
        }
        else if (choice == 3)
        {
            printf("\nExiting DiffractionLab...\n");
            break;
        }
        else
        {
            printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}