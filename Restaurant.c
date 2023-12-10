#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_STRING 50

struct items
{
    char item[20];
    float price;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

// function to generate bills
void generateBillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t\tASOOM Restaurant");
    printf("\n\t\t----------------");
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", name);
    printf("\n--------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n--------------------------------------\n\n");
}

void generateBillBody(char item[30], int qty, float price)
{
    printf("%s \t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t\n", qty * price);
}

void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float TAX = 0.09 * netTotal;
    float grandTotal = netTotal + TAX;
    printf("\n--------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", netTotal);
    printf("\nDiscount @10\t\t\t%.2f", dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nTAX @9\t\t\t\t%.2f", TAX);
    printf("\n--------------------------------------\n");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n--------------------------------------\n");
}

int main(void)
{
    int opt, num;
    struct orders ord;
    struct orders order;

    char saveBill = 'y', contFlag = 'y';
    char name[50];
    FILE *fp;

    // dashboard
    while (contFlag == 'y')
    {
        float total = 0;
        int invoiceFound = 0;
        printf("\t==========ASOOM Restaurant==========");
        printf("\n\nPlease select your preferred operation:\t");
        printf("\n\n1. Generate Invoice");
        printf("\n2. Show all Invoices");
        printf("\n3. Search Invoice");
        printf("\n4. Exit");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);

        // Flush the input buffer
        while (getchar() != '\n')
            ;

        printf("You have chosen %d", opt);

        switch (opt)
        {
        case 1:
            // system("cls");
            while (getchar() != '\n')
                ;

            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.customer, sizeof(ord.customer), stdin);
            ord.customer[strcspn(ord.customer, "\n")] = '\0'; // Remove newline character
            strcpy(ord.date, __DATE__);
            printf("\nPlease enter the number of items:\t");
            scanf("%d", &num);
            ord.numOfItems = num;

            for (size_t i = 0; i < num; i++)
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

                total += ord.itm[i].qty * ord.itm[i].price;
            }

            generateBillHeader(ord.customer, ord.date);
            for (size_t i = 0; i < ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            generateBillFooter(total);

            printf("\nDo you want to save the invoice? [y/n]\t");
            scanf(" %c", &saveBill);

            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.dat", "a+");
                if (fp != NULL)
                {
                    fwrite(&ord, sizeof(struct orders), 1, fp);
                    printf("\nSuccessfully saved");
                    fclose(fp);
                }
                else
                {
                    printf("\nError saving");
                }
            }
            break;

        case 2:
            // system("cls");
            fp = fopen("RestaurantBill.dat", "r");
            printf("\n  *****Your Previous Invoices*****\n");

            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                generateBillHeader(order.customer, order.date);
                for (size_t i = 0; i < order.numOfItems; i++)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
                printf("Customer: %s\n", order.customer); // Print customer name with every bill
                printf("--------------------------------------\n");
            }
            fclose(fp);
            break;

        case 3:
            printf("\nEnter the name of the customer:\t");
            while (getchar() != '\n')
                ; // Flush the input buffer
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            fp = fopen("RestaurantBill.dat", "r");
            printf("\n\t*****Invoices of %s*****\n", name);

            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                if (!strcmp(order.customer, name))
                {
                    generateBillHeader(order.customer, order.date);
                    for (size_t i = 0; i < order.numOfItems; i++)
                    {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                    invoiceFound = 1;
                }
            }
            if (!invoiceFound)
            {
                printf("The invoice for %s doesn't exist", name);
            }
            fclose(fp);
            break;
            break;

        case 4:
            printf("\n\t\t Exit Successfully\n\n");
            exit(0);
            break;
            
        case 5:
            fp = fopen("RestaurantBill.dat", "r");
            printf("\n *****All Saved Data*****\n");

            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                generateBillHeader(order.customer, order.date);
                for (size_t i = 0; i < order.numOfItems; i++)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
                printf("Customer: %s\n", order.customer);
                printf("--------------------------------------\n");
            }
            fclose(fp);
            break;

        default:
            printf("\nInvalid option.\n");
            break;
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf(" %c", &contFlag);
    }
    printf("\n\n");

    return 0;
}