#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 50
#define MAX_ITEMS 50

struct Item {
    char name[MAX_STRING];
    float price;
    int quantity;
};

struct Order {
    char customer[MAX_STRING];
    char date[MAX_STRING];
    int numOfItems;
    struct Item items[MAX_ITEMS];
};

void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void generateBillHeader(char customer[MAX_STRING], char date[MAX_STRING]) {
    printf("\n\n");
    printf("\t\tASOOM Restaurant");
    printf("\n\t\t----------------");
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", customer);
    printf("\n--------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n--------------------------------------\n\n");
}

void generateBillBody(char itemName[MAX_STRING], int quantity, float price) {
    printf("%s \t\t", itemName);
    printf("%d\t\t", quantity);
    printf("%.2f\t\t\n", quantity * price);
}

void generateBillFooter(float total) {
    printf("\n");
    float discount = 0.1 * total;
    float netTotal = total - discount;
    float TAX = 0.09 * netTotal;
    float grandTotal = netTotal + TAX;
    printf("\n--------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", netTotal);
    printf("\nDiscount @10\t\t\t%.2f", discount);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nTAX @9\t\t\t\t%.2f", TAX);
    printf("\n--------------------------------------\n");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n--------------------------------------\n");
}

void saveInvoiceToFile(struct Order *order) {
    FILE *fp = fopen("RestaurantBill.bin", "ab+");
    if (fp != NULL) {
        fwrite(order, sizeof(struct Order), 1, fp);
        printf("\nSuccessfully saved");
        fclose(fp);
    } else {
        printf("\nError saving");
    }
}

void generateInvoice() {
    struct Order currentOrder;
    char saveBill = 'y';

    while (getchar() != '\n'); // Flush the input buffer

    printf("\nPlease enter the name of the customer:\t");
    fgets(currentOrder.customer, sizeof(currentOrder.customer), stdin);
    currentOrder.customer[strcspn(currentOrder.customer, "\n")] = '\0'; // Remove newline character
    strcpy(currentOrder.date, __DATE__);
    
    printf("\nPlease enter the number of items:\t");
    scanf("%d", &currentOrder.numOfItems);

    float total = 0;

    for (size_t i = 0; i < currentOrder.numOfItems; i++) {
        while (getchar() != '\n'); // Flush the input buffer
        printf("\n\nPlease enter the item %d:\t", i + 1);
        fgets(currentOrder.items[i].name, sizeof(currentOrder.items[i].name), stdin);
        currentOrder.items[i].name[strcspn(currentOrder.items[i].name, "\n")] = '\0';
        printf("Please enter the quantity:\t");
        scanf("%d", &currentOrder.items[i].quantity);
        printf("Please enter the unit price:\t");
        scanf("%f", &currentOrder.items[i].price);

        total += currentOrder.items[i].quantity * currentOrder.items[i].price;
    }

    generateBillHeader(currentOrder.customer, currentOrder.date);
    
    for (size_t i = 0; i < currentOrder.numOfItems; i++) {
        generateBillBody(currentOrder.items[i].name, currentOrder.items[i].quantity, currentOrder.items[i].price);
    }

    generateBillFooter(total);

    printf("\nDo you want to save the invoice? [y/n]\t");
    scanf(" %c", &saveBill);

    if (saveBill == 'y') {
        saveInvoiceToFile(&currentOrder);
    }
}

void showAllInvoices() {
    FILE *fp = fopen("RestaurantBill.bin", "rb");
    struct Order savedOrder;

    printf("\n  *****Your Previous Invoices*****\n");

    while (fread(&savedOrder, sizeof(struct Order), 1, fp)) {
        float tot = 0;
        generateBillHeader(savedOrder.customer, savedOrder.date);

        for (size_t i = 0; i < savedOrder.numOfItems; i++) {
            generateBillBody(savedOrder.items[i].name, savedOrder.items[i].quantity, savedOrder.items[i].price);
            tot += savedOrder.items[i].quantity * savedOrder.items[i].price;
        }

        generateBillFooter(tot);
        printf("Customer: %s\n", savedOrder.customer); // Print customer name with every bill
        printf("--------------------------------------\n");
    }

    fclose(fp);
}

void searchInvoice() {
    char name[MAX_STRING];
    int invoiceFound = 0;
    FILE *fp = fopen("RestaurantBill.bin", "rb");
    struct Order savedOrder;

    printf("\nEnter the name of the customer:\t");
    while (getchar() != '\n'); // Flush the input buffer
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("\n\t*****Invoices of %s*****\n", name);

    while (fread(&savedOrder, sizeof(struct Order), 1, fp)) {
        float tot = 0;
        if (!strcmp(savedOrder.customer, name)) {
            generateBillHeader(savedOrder.customer, savedOrder.date);

            for (size_t i = 0; i < savedOrder.numOfItems; i++) {
                generateBillBody(savedOrder.items[i].name, savedOrder.items[i].quantity, savedOrder.items[i].price);
                tot += savedOrder.items[i].quantity * savedOrder.items[i].price;
            }

            generateBillFooter(tot);
            invoiceFound = 1;
        }
    }

    if (!invoiceFound) {
        printf("The invoice for %s doesn't exist", name);
    }

    fclose(fp);
}

int main(void) {
    int opt;
    char contFlag = 'y';

    while (contFlag == 'y') {
        printf("\t==========ASOOM Restaurant==========");
        printf("\n\nPlease select your preferred operation:\t");
        printf("\n\n1. Generate Invoice");
        printf("\n2. Show all Invoices");
        printf("\n3. Search Invoice");
        printf("\n4. Exit");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                generateInvoice();
                break;

            case 2:
                showAllInvoices();
                break;

            case 3:
                searchInvoice();
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

    printf("\n\n");

    return 0;
}
