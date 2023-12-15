#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 50
#define MAX_ITEMS 50
#define FILE_NAME "RestaurantBill.bin"
#define INVOICE_COUNTER_FILE "InvoiceCounter.bin"

enum Operation
{
    GENERATE_INVOICE = 1,
    SHOW_ALL_INVOICES,
    SEARCH_INVOICE,
    DELETE_INVOICE,
    EXIT_PROGRAM
};

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
    struct Item items[MAX_ITEMS];
};

// Function pointer for printing bill section
typedef void (*PrintBillSection)(struct Item);

// Function pointer for comparison function
typedef int (*ComparisonFunction)(struct Order *, char *);

// Double pointer for dynamic array of strings
typedef char **StringArray;

#define DISCOUNT_RATE 0.1
#define TAX_RATE 0.09

// Macro function for total calculation
#define CALCULATE_TOTAL(qty, price) ((qty) * (price))

void flushInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Function pointer example 1
void printItemName(struct Item item)
{
    printf("%s\n", item.name);
}

// Function pointer example 2
void printItemQuantity(struct Item item)
{
    printf("%d\n", item.quantity);
}

// Double pointer and malloc example
StringArray createDynamicStringArray(int size)
{
    return (StringArray)malloc(size * sizeof(char *));
}

// Double pointer and calloc example
StringArray createInitializedDynamicStringArray(int size)
{
    return (StringArray)calloc(size, sizeof(char *));
}

void freeDynamicStringArray(StringArray array, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(array[i]);
    }
    free(array);
}

// Function to generate bill header
void generateBillHeader(int invoiceNumber, char customer[MAX_STRING], char phone[MAX_STRING], char date[MAX_STRING])
{
    printf("\n\n");
    printf("\t\tASOOM Restaurant");
    printf("\n\t\t----------------");
    printf("\nInvoice Number: %d", invoiceNumber);
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", customer);
    printf("\nPhone: %s", phone);
    printf("\n--------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n--------------------------------------\n\n");
}

// Function to generate bill body
void generateBillBody(char itemName[MAX_STRING], int quantity, float price)
{
    printf("%s \t\t", itemName);
    printf("%d\t\t", quantity);
    printf("%.2f\t\t\n", CALCULATE_TOTAL(quantity, price));
}

// Function to generate bill footer
void generateBillFooter(float total)
{
    printf("\n");
    float discount = DISCOUNT_RATE * total;
    float netTotal = total - discount;
    float TAX = TAX_RATE * netTotal;
    float grandTotal = netTotal + TAX;
    printf("\n--------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", netTotal);
    printf("\nDiscount @%.0f%%\t\t\t%.2f", DISCOUNT_RATE * 100, discount);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nTAX @%.0f%%\t\t\t\t%.2f", TAX_RATE * 100, TAX);
    printf("\n--------------------------------------\n");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n--------------------------------------\n");
}

// Function to save invoice to file
void saveInvoiceToFile(struct Order *order)
{
    FILE *fp = fopen(FILE_NAME, "ab+");
    if (fp != NULL)
    {
        if (fwrite(order, sizeof(struct Order), 1, fp) != 1)
        {
            printf("\nError writing to file");
        }
        else
        {
            printf("\nSuccessfully saved");
        }
        fclose(fp);
    }
    else
    {
        printf("\nError opening file %s for writing", FILE_NAME);
    }
}

int loadAndUpdateInvoiceCounter()
{
    int invoiceCounter = 1; // Default starting value

    FILE *counterFile = fopen(INVOICE_COUNTER_FILE, "rb");
    if (counterFile != NULL)
    {
        fread(&invoiceCounter, sizeof(int), 1, counterFile);
        fclose(counterFile);
    }

    // Update the counter for the next use
    FILE *updateCounterFile = fopen(INVOICE_COUNTER_FILE, "wb");
    if (updateCounterFile != NULL)
    {
        invoiceCounter++;
        fwrite(&invoiceCounter, sizeof(int), 1, updateCounterFile);
        fclose(updateCounterFile);
    }
    else
    {
        printf("\nError opening file %s for writing", INVOICE_COUNTER_FILE);
    }

    return invoiceCounter;
}



// Function to generate invoice number
int generateInvoiceNumber()
{
    static int invoiceCounter = 1;
    return invoiceCounter++;
}

// Function to generate invoice
void generateInvoice()
{
    struct Order currentOrder;
    char saveBill = 'y';

    // Increment the invoice counter when generating a new invoice
    currentOrder.invoiceNumber = generateInvoiceNumber();

    while (getchar() != '\n')
        ;

    printf("\nPlease enter the name of the customer:\t");
    fgets(currentOrder.customerInfo.name, sizeof(currentOrder.customerInfo.name), stdin);
    currentOrder.customerInfo.name[strcspn(currentOrder.customerInfo.name, "\n")] = '\0';

    printf("Please enter the phone number of the customer:\t");
    fgets(currentOrder.customerInfo.phone, sizeof(currentOrder.customerInfo.phone), stdin);
    currentOrder.customerInfo.phone[strcspn(currentOrder.customerInfo.phone, "\n")] = '\0';

    strcpy(currentOrder.date, __DATE__);

    printf("\nPlease enter the number of items:\t");
    scanf("%d", &currentOrder.numOfItems);

    float total = 0;

    for (size_t i = 0; i < currentOrder.numOfItems; i++)
    {
        while (getchar() != '\n')
            ;
        printf("\n\nPlease enter the item %d:\t", i + 1);
        fgets(currentOrder.items[i].name, sizeof(currentOrder.items[i].name), stdin);
        currentOrder.items[i].name[strcspn(currentOrder.items[i].name, "\n")] = '\0';
        printf("Please enter the quantity:\t");
        scanf("%d", &currentOrder.items[i].quantity);
        printf("Please enter the unit price:\t");
        scanf("%f", &currentOrder.items[i].price);

        total += CALCULATE_TOTAL(currentOrder.items[i].quantity, currentOrder.items[i].price);
    }

    generateBillHeader(currentOrder.invoiceNumber, currentOrder.customerInfo.name, currentOrder.customerInfo.phone, currentOrder.date);

    for (size_t i = 0; i < currentOrder.numOfItems; i++)
    {
        generateBillBody(currentOrder.items[i].name, currentOrder.items[i].quantity, currentOrder.items[i].price);
    }

    generateBillFooter(total);

    printf("\nDo you want to save the invoice? [y/n]\t");
    scanf(" %c", &saveBill);

    if (saveBill == 'y')
    {
        saveInvoiceToFile(&currentOrder);
    }
}

// Function to show all invoices
void showAllInvoices()
{
    FILE *fp = fopen("RestaurantBill.bin", "rb");
    struct Order savedOrder;

    printf("\n  *****Your Previous Invoices*****\n");

    while (fread(&savedOrder, sizeof(struct Order), 1, fp))
    {
        float tot = 0;
        generateBillHeader(savedOrder.invoiceNumber, savedOrder.customerInfo.name, savedOrder.customerInfo.phone, savedOrder.date);

        for (size_t i = 0; i < savedOrder.numOfItems; i++)
        {
            generateBillBody(savedOrder.items[i].name, savedOrder.items[i].quantity, savedOrder.items[i].price);
            tot += CALCULATE_TOTAL(savedOrder.items[i].quantity, savedOrder.items[i].price);
        }

        generateBillFooter(tot);
        printf("Customer: %s\nPhone: %s\n", savedOrder.customerInfo.name, savedOrder.customerInfo.phone);
        printf("--------------------------------------\n");
    }

    fclose(fp);
}

// Comparison function for searching by invoice number
int searchByInvoiceNumber(struct Order *order, char *target)
{
    return order->invoiceNumber == atoi(target);
}

// Comparison function for searching by customer name
int searchByCustomerName(struct Order *order, char *target)
{
    return strcmp(order->customerInfo.name, target) == 0;
}

// Comparison function for searching by phone number
int searchByPhoneNumber(struct Order *order, char *target)
{
    return strcmp(order->customerInfo.phone, target) == 0;
}

// Function to search or delete invoice based on criteria function
void searchOrDeleteInvoice(ComparisonFunction criteriaFunction, char *searchTerm, int isDelete)
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
                    generateBillBody(savedOrder.items[i].name, savedOrder.items[i].quantity, savedOrder.items[i].price);
                    tot += CALCULATE_TOTAL(savedOrder.items[i].quantity, savedOrder.items[i].price);
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

// Function to search for an invoice
void searchInvoice()
{
    char searchTerm[MAX_STRING];
    ComparisonFunction criteriaFunctions[] = {searchByInvoiceNumber, searchByCustomerName, searchByPhoneNumber};

    printf("\nSelect search criteria:\n");
    printf("1. Invoice Number\n");
    printf("2. Customer Name\n");
    printf("3. Phone Number\n");

    int choice;
    printf("Your choice (1-3):\t");
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

// Function to delete an invoice
void deleteInvoice()
{
    char searchTerm[MAX_STRING];
    ComparisonFunction criteriaFunctions[] = {searchByInvoiceNumber, searchByCustomerName, searchByPhoneNumber};

    printf("\nSelect search criteria:\n");
    printf("1. Invoice Number\n");
    printf("2. Customer Name\n");
    printf("3. Phone Number\n");

    int choice;
    printf("Your choice (1-3):\t");
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

    // Increment the invoice counter when generating a new invoice
    int invoiceCounter = loadAndUpdateInvoiceCounter();

    // Example of using function pointers
    PrintBillSection printFunctionPointers[] = {printItemName, printItemQuantity};
    struct Item exampleItem = {"Example Item", 10.5, 3};

    for (int i = 0; i < 2; i++)
    {
        printFunctionPointers[i](exampleItem);
    }

    // Example of using double pointer and malloc
    int size = 5;
    StringArray dynamicArray = createDynamicStringArray(size);

    // Example of using double pointer and calloc
    StringArray initializedArray = createInitializedDynamicStringArray(size);

    

    while (contFlag == 'y')
    {
        printf("\t==========ASOOM Restaurant==========");
        printf("\n\nPlease select your preferred operation:\t");
        printf("\n\n%d. Generate Invoice", GENERATE_INVOICE);
        printf("\n%d. Show all Invoices", SHOW_ALL_INVOICES);
        printf("\n%d. Search Invoice", SEARCH_INVOICE);
        printf("\n%d. Delete Invoice", DELETE_INVOICE);
        printf("\n%d. Exit", EXIT_PROGRAM);

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

            // Example of freeing dynamic string array
            freeDynamicStringArray(dynamicArray, size);
            freeDynamicStringArray(initializedArray, size);

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
