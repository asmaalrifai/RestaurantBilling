#include "items.h"
#include "orders.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
// #include <cstdio>

int main(void)
{
    int opt;
    char contFlag = 'y';
    char name[50];
    struct orders ord;

    // dashboard
    while (contFlag == 'y')
    {
        printf("\t==========ASOOM Restaurant==========");
        printf("\n\nPlease select your preferred operation:\t");
        printf("\n\n1. Generate Invoice");
        printf("\n2. Show all Invoices");
        printf("\n3. Search Invoice");
        printf("\n4. Exit");

        printf("\nYour choice:\t");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:
            printf("\nPlease enter the name of the customer:\t");
            while (getchar() != '\n')
                ;
            fgets(ord.customer, sizeof(ord.customer), stdin);
            ord.customer[strcspn(ord.customer, "\n")] = '\0'; // Remove newline character
            strcpy(ord.date, __DATE__);
            printf("\nPlease enter the number of items:\t");
            scanf("%d", &ord.numOfItems);

            for (size_t i = 0; i < ord.numOfItems; i++)
            {
                while (getchar() != '\n')
                    ; // Flush the input buffer
                printf("\n\nPlease enter the item %d:\t", i + 1);
                fgets(ord.itm[i].item, sizeof(ord.itm[i].item), stdin);
                ord.itm[i].item[strcspn(ord.itm[i].item, "\n")] = '\0';
                printf("Please enter the quantity:\t");
                scanf("%d", &ord.itm[i].qty);
                printf("Please enter the unit price:\t");
                scanf("%f", &ord.itm[i].price);
            }

            generateBillHeader(ord.customer, ord.date);
            for (size_t i = 0; i < ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            generateBillFooter(ord.numOfItems); // Pass total items as an argument
            saveOrderToFile(ord);
            break;

        case 2:
            showAllInvoices();
            break;

        case 3:
            printf("\nEnter the name of the customer:\t");
            while (getchar() != '\n')
                ; // Flush the input buffer
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            searchInvoice(name);
            break;

        case 4:
            printf("\n\t\t Exit Successfully\n\n");
            exit(0);
            break;

        default:
            printf("\nInvalid option.\n");
            break;
        }

        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf(" %c", &contFlag);
    }

    return 0;
}
