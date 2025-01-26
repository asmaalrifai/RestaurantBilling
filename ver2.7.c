#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 50
#define MAX_ITEMS 50
#define MAX_ORDERS 50

enum Operation
{
    GENERATE_INVOICE = 1,
    SHOW_ALL_INVOICES,
    SEARCH_INVOICE,
    DELETE_INVOICE,
    EXIT_PROGRAM
};

// Macro function to flush input buffer
#define FLUSH_INPUT_BUFFER()                        \
    do                                              \
    {                                               \
        int c;                                      \
        while ((c = getchar()) != '\n' && c != EOF) \
            ;                                       \
    } while (0)

struct Item
{
    char name[MAX_STRING];
    float price;
    int quantity;
};

struct Customer
{
    char name[MAX_STRING];
    char phone[MAX_STRING];
};

struct Order
{
    int invoiceNumber;
    struct Customer customerInfo;
    char date[MAX_STRING];
    int numOfItems;
    struct Item *items; // Using dynamic memory for array of items
    float total;
};

// Function pointer type for printing the bill
typedef void (*PrintBillFunction)(struct Order *);

void flushInputBuffer()
{
    FLUSH_INPUT_BUFFER();
}

int generateInvoiceNumber()
{
    static int invoiceCounter = 1;
    return invoiceCounter++;
}

// Function to print the bill header
void generateBillHeader(int invoiceNumber, char *customerName, char *phone, char *date)
{
    printf("\n\n");
    printf("\t\tASOOM Restaurant");
    printf("\n\t\t----------------");
    printf("\nInvoice Number: %d", invoiceNumber);
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", customerName);
    printf("\nPhone: %s", phone);
    printf("\n--------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n--------------------------------------\n\n");
}

// Function to print the bill body
void generateBillBody(struct Item *item)
{
    printf("%-20s", item->name);  // Adjust the width for better formatting
    printf("%-10d", item->quantity);
    printf("%.2f\n", item->quantity * item->price);
}

// Function to print the bill footer
// Modify the generateBillFooter function definition
void generateBillFooter(float total)
{
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



// Function to save the invoice to a file
void saveInvoiceToFile(struct Order *order)
{
    FILE *fp = fopen("RestaurantBill.bin", "ab+");
    if (fp != NULL)
    {
        fwrite(order, sizeof(struct Order), 1, fp);
        printf("\nSuccessfully saved");
        fclose(fp);
    }
    else
    {
        printf("\nError saving");
    }
}

// Function to read the invoice from a file
void readInvoiceFromFile(struct Order *order)
{
    FILE *fp = fopen("RestaurantBill.bin", "rb");
    if (fp != NULL)
    {
        fread(order, sizeof(struct Order), 1, fp);
        fclose(fp);
    }
}

// Function to print the bill using function pointer
// Modify the printBill function
// Function to print the bill using function pointer
void printBill(struct Order *order)
{
    generateBillHeader(order->invoiceNumber, order->customerInfo.name, order->customerInfo.phone, order->date);
    for (int i = 0; i < order->numOfItems; i++)
    {
        generateBillBody(&(order->items[i]));
    }

    // Pass the total to generateBillFooter
    generateBillFooter(order->total);
}




// Function to generate an invoice
void generateInvoice()
{
    struct Order currentOrder;
    char saveBill = 'y';

    currentOrder.invoiceNumber = generateInvoiceNumber();

    FLUSH_INPUT_BUFFER();

    printf("\nPlease enter the name of the customer:\t");
    fgets(currentOrder.customerInfo.name, sizeof(currentOrder.customerInfo.name), stdin);
    currentOrder.customerInfo.name[strcspn(currentOrder.customerInfo.name, "\n")] = '\0';

    printf("Please enter the phone number of the customer:\t");
    fgets(currentOrder.customerInfo.phone, sizeof(currentOrder.customerInfo.phone), stdin);
    currentOrder.customerInfo.phone[strcspn(currentOrder.customerInfo.phone, "\n")] = '\0';

    strcpy(currentOrder.date, __DATE__);

    printf("\nPlease enter the number of items:\t");
    scanf("%d", &currentOrder.numOfItems);

    // Allocate memory for array of items
    currentOrder.items = (struct Item *)malloc(currentOrder.numOfItems * sizeof(struct Item));

    float total = 0;

    for (int i = 0; i < currentOrder.numOfItems; i++)
    {
        FLUSH_INPUT_BUFFER();
        printf("\n\nPlease enter the item %d:\t", i + 1);
        fgets(currentOrder.items[i].name, sizeof(currentOrder.items[i].name), stdin);
        currentOrder.items[i].name[strcspn(currentOrder.items[i].name, "\n")] = '\0';
        printf("Please enter the quantity:\t");
        scanf("%d", &currentOrder.items[i].quantity);
        printf("Please enter the unit price:\t");
        scanf("%f", &currentOrder.items[i].price);

        total += currentOrder.items[i].quantity * currentOrder.items[i].price;
    }

    currentOrder.total = total;

    // Save the invoice to file
    saveInvoiceToFile(&currentOrder);

    // Print the bill using function pointer
    PrintBillFunction printBillFunction = printBill;
    printBillFunction(&currentOrder);

    // Free allocated memory
    free(currentOrder.items);
}

// Function to show all invoices
void showAllInvoices()
{
    FILE *fp = fopen("RestaurantBill.bin", "rb");
    struct Order savedOrder;

    printf("\n  *****Your Previous Invoices*****\n");

    while (fread(&savedOrder, sizeof(struct Order), 1, fp))
    {
        // Print the bill using function pointer
        PrintBillFunction printBillFunction = printBill;
        printBillFunction(&savedOrder);

        printf("Customer: %s\nPhone: %s\n", savedOrder.customerInfo.name, savedOrder.customerInfo.phone);
        printf("--------------------------------------\n");
    }

    fclose(fp);
}

typedef int (*SearchCriteria)(struct Order *, char *);

int searchByInvoiceNumber(struct Order *order, char *target)
{
    return order->invoiceNumber == atoi(target);
}

int searchByCustomerName(struct Order *order, char *target)
{
    return strcmp(order->customerInfo.name, target) == 0;
}

int searchByPhoneNumber(struct Order *order, char *target)
{
    return strcmp(order->customerInfo.phone, target) == 0;
}

void searchOrDeleteInvoice(SearchCriteria criteriaFunction, char *searchTerm, int isDelete)
{
    FILE *fp = fopen("RestaurantBill.bin", "rb");
    struct Order savedOrder;

    printf("\nEnter the %s:\t", isDelete ? "invoice number, customer name, or phone number to delete" : "search term");

    while (getchar() != '\n')
        ;

    fgets(searchTerm, MAX_STRING, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = '\0';

    int found = 0;

    FILE *tempFile = fopen("temp.bin", "wb");

    while (fread(&savedOrder, sizeof(struct Order), 1, fp))
    {
        if (criteriaFunction(&savedOrder, searchTerm))
        {
            found = 1;
            if (!isDelete)
            {
                float tot = 0;
                generateBillHeader(savedOrder.invoiceNumber, savedOrder.customerInfo.name, savedOrder.customerInfo.phone, savedOrder.date);

                for (size_t i = 0; i < savedOrder.numOfItems; i++)
                {
                    generateBillBody(&(savedOrder.items[i]));
                    tot += savedOrder.items[i].quantity * savedOrder.items[i].price;
                }

                generateBillFooter(tot);
                printf("Customer: %s\nPhone: %s\n", savedOrder.customerInfo.name, savedOrder.customerInfo.phone);
                printf("--------------------------------------\n");
            }
        }
        else
        {
            fwrite(&savedOrder, sizeof(struct Order), 1, tempFile);
        }
    }

    fclose(fp);
    fclose(tempFile);

    // Remove the original file and rename the temporary file if it's not a delete operation
    if (!isDelete)
    {
        remove("temp.bin");
    }
    else
    {
        remove("RestaurantBill.bin");
        rename("temp.bin", "RestaurantBill.bin");
    }

    if (!found)
    {
        printf("%s not found\n", isDelete ? "Invoice" : "No invoice matched the search term");
    }
}

void searchInvoice()
{
    char searchTerm[MAX_STRING];
    SearchCriteria criteriaFunctions[] = {searchByInvoiceNumber, searchByCustomerName, searchByPhoneNumber};

    printf("\nSelect search criteria:\n");
    printf("1. Invoice Number\n");
    printf("2. Customer Name\n");
    printf("3. Phone Number\n");

    int choice;
    printf("Your choice:\t");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 3)
    {
        searchOrDeleteInvoice(criteriaFunctions[choice - 1], searchTerm, 0);
    }
    else
    {
        printf("Invalid choice\n");
    }
}

void deleteInvoice()
{
    char searchTerm[MAX_STRING];
    SearchCriteria criteriaFunctions[] = {searchByInvoiceNumber, searchByCustomerName, searchByPhoneNumber};

    printf("\nSelect search criteria:\n");
    printf("1. Invoice Number\n");
    printf("2. Customer Name\n");
    printf("3. Phone Number\n");

    int choice;
    printf("Your choice:\t");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 3)
    {
        searchOrDeleteInvoice(criteriaFunctions[choice - 1], searchTerm, 1);
    }
    else
    {
        printf("Invalid choice\n");
    }
}

int main(void)
{
    int opt;
    char contFlag = 'y';

    while (contFlag == 'y')
    {
        printf("\t==========ASOOM Restaurant==========");
        printf("\n\nPlease select your preferred operation:\t");
        printf("\n\n1. Generate Invoice");
        printf("\n2. Show all Invoices");
        printf("\n3. Search Invoice");
        printf("\n4. Delete Invoice");
        printf("\n5. Exit");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);

        switch ((enum Operation)opt)
        {
        case GENERATE_INVOICE:
            generateInvoice();
            break;

        case SHOW_ALL_INVOICES:
            showAllInvoices();
            break;

        case SEARCH_INVOICE:
            searchInvoice();
            break;

        case DELETE_INVOICE:
            deleteInvoice();
            break;

        case EXIT_PROGRAM:
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
