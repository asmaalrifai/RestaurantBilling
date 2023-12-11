#include "items.h"
#include "orders.h"
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

void saveOrderToFile(struct orders ord)
{
    FILE *fp;
    char saveBill = 'y';

    printf("\nDo you want to save the invoice? [y/n]\t");
    scanf(" %c", &saveBill);

    if (saveBill == 'y')
    {
        fp = fopen("RestaurantBill.bin", "ab+");
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
}

void showAllInvoices()
{
    FILE *fp;
    struct orders order;

    fp = fopen("RestaurantBill.bin", "rb");
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
}

void searchInvoice(char name[50])
{
    FILE *fp;
    struct orders order;
    int invoiceFound = 0;

    fp = fopen("RestaurantBill.bin", "rb");
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
}