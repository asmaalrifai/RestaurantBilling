#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 50

// Enum for menu item categories
enum Category
{
    MAIN_COURSE,
    DESSERT,
    DRINK
};

// Struct for menu items
struct MenuItem
{
    char *itemName;
    float price;
    int quantity;
    enum Category category;
};

// Struct for customer details
struct Customer
{
    char name[MAX_STRING];
    char phone[MAX_STRING];
};

// Struct for orders
struct Order
{
    struct Customer *customer;
    char date[MAX_STRING];
    int numOfItems;
    struct MenuItem *items;
    float (*calculateTotal)(struct MenuItem *items, int numOfItems);
};

// Function to calculate total price
float calculateTotal(struct MenuItem *items, int numOfItems)
{
    float total = 0;
    for (int i = 0; i < numOfItems; i++)
    {
        total += items[i].quantity * items[i].price;
    }
    return total;
}

// Function to display all invoices from the file
void showAllInvoices(FILE *fp);

// Function to free memory allocated for menu items
void freeMenuItems(struct MenuItem *items, int numOfItems);

// Function to generate bill header
void generateBillHeader(struct Customer *customer, char date[MAX_STRING]);

// Function to generate bill body
void generateBillBody(struct MenuItem *item);

// Function to generate bill footer
void generateBillFooter(float total);

// Function to print bill details
void printBillDetails(struct Order *order);

// Function to handle case 1
void generateInvoice(FILE *fp);

// Function to search for an invoice by customer name
void searchInvoice(FILE *fp);

// Function to handle case 4
void exitProgram();

int main(void)
{
    int opt;
    char contFlag = 'y';
    FILE *fp;

    // Dashboard
    while (contFlag == 'y')
    {
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

        printf("You have chosen %d\n", opt);

        switch (opt)
        {
        case 1:
            fp = fopen("RestaurantBill.bin", "ab+");
            if (fp != NULL)
            {
                generateInvoice(fp);
                fclose(fp);
            }
            else
            {
                perror("\nError opening file for saving");
            }
            break;

        case 2:
            fp = fopen("RestaurantBill.bin", "rb");
            if (fp != NULL)
            {
                showAllInvoices(fp);
                fclose(fp);
            }
            else
            {
                perror("\nError opening file for reading");
            }
            break;

        case 3:
            fp = fopen("RestaurantBill.bin", "rb");
            if (fp != NULL)
            {
                searchInvoice(fp);
                fclose(fp);
            }
            else
            {
                perror("\nError opening file for reading");
            }
            break;

        case 4:
            exitProgram();
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

// Function to read and display all invoices
void showAllInvoices(FILE *fp)
{
    struct Order ord;
    printf("test1");
    
    while (fread(&ord.numOfItems, sizeof(int), 1, fp) == 1)
    {
        printf("test2");
        // Allocate memory for customer and items
        ord.customer = malloc(sizeof(struct Customer));
        ord.items = malloc(ord.numOfItems * sizeof(struct MenuItem));

        // Read customer details
        fread(ord.customer->name, sizeof(char), MAX_STRING, fp);
        fread(ord.customer->phone, sizeof(char), MAX_STRING, fp);
        fread(ord.date, sizeof(char), MAX_STRING, fp);

        // Move the file pointer forward by the size of items details
        fseek(fp, ord.numOfItems * (MAX_STRING + sizeof(int) + sizeof(float)), SEEK_CUR);

        // Move the file pointer back to the beginning of the current invoice
        fseek(fp, -(ord.numOfItems * (MAX_STRING + sizeof(int) + sizeof(float)) + sizeof(int) + sizeof(char) * MAX_STRING * 3), SEEK_CUR);

        // Read items
        for (int i = 0; i < ord.numOfItems; i++)
        {
            printf("test3");
            ord.items[i].itemName = malloc(MAX_STRING * sizeof(char));
            fread(ord.items[i].itemName, sizeof(char), MAX_STRING, fp);
            fread(&ord.items[i].quantity, sizeof(int), 1, fp);
            fread(&ord.items[i].price, sizeof(float), 1, fp);
        }
        printf("test4");

        // Assign the function pointer
        ord.calculateTotal = calculateTotal;

        // Print invoice details
        printBillDetails(&ord);

        // Free allocated memory for customer and items
        free(ord.customer);
        freeMenuItems(ord.items, ord.numOfItems);
    }
}


void freeMenuItems(struct MenuItem *items, int numOfItems)
{
    for (int i = 0; i < numOfItems; i++)
    {
        free(items[i].itemName);
    }
    free(items);
}

void generateBillHeader(struct Customer *customer, char date[MAX_STRING])
{
    printf("\n\n");
    printf("\t\tASOOM Restaurant");
    printf("\n\t\t----------------");
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", customer->name);
    printf("\nPhone: %s", customer->phone);
    printf("\n--------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n--------------------------------------\n\n");
}

void generateBillBody(struct MenuItem *item)
{
    printf("%s \t\t", item->itemName); // Assuming only one item for simplicity
    printf("%d\t\t", item->quantity);
    printf("%.2f\t\t\n", item->quantity * item->price);
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

void printBillDetails(struct Order *order)
{
    float tot = order->calculateTotal(order->items, order->numOfItems);
    generateBillHeader(order->customer, order->date);

    for (size_t i = 0; i < order->numOfItems; i++)
    {
        generateBillBody(&order->items[i]);
    }

    generateBillFooter(tot);
}

void generateInvoice(FILE *fp)
{
    struct Order order;
    char saveBill = 'y';

    printf("\nPlease enter the name of the customer:\t");
    order.customer = malloc(sizeof(struct Customer));
    fgets(order.customer->name, sizeof(order.customer->name), stdin);
    order.customer->name[strcspn(order.customer->name, "\n")] = '\0';

    printf("\nPlease enter the phone number of the customer:\t");
    fgets(order.customer->phone, sizeof(order.customer->phone), stdin);
    order.customer->phone[strcspn(order.customer->phone, "\n")] = '\0';

    strcpy(order.date, __DATE__);
    printf("\nPlease enter the number of items:\t");
    int num;
    scanf("%d", &num);
    order.numOfItems = num;

    order.items = malloc(num * sizeof(struct MenuItem));

    float total = 0;
    for (size_t i = 0; i < num; i++)
    {
        while (getchar() != '\n')
            ; // Flush the input buffer
        printf("\n\nPlease enter the item %d:\t", i + 1);
        order.items[i].itemName = malloc(MAX_STRING * sizeof(char));
        fgets(order.items[i].itemName, MAX_STRING, stdin);
        order.items[i].itemName[strcspn(order.items[i].itemName, "\n")] = '\0';

        printf("Please enter the quantity:\t");
        scanf("%d", &order.items[i].quantity);
        printf("Please enter the unit price:\t");
        scanf("%f", &order.items[i].price);

        total += order.items[i].quantity * order.items[i].price;
    }

     // Assign the function pointer
    order.calculateTotal = calculateTotal;

    generateBillHeader(order.customer, order.date);
    for (size_t i = 0; i < order.numOfItems; i++)
    {
        generateBillBody(&order.items[i]);
    }
    generateBillFooter(total);


    printf("\nDo you want to save the invoice? [y/n]\t");
    scanf(" %c", &saveBill);

    if (saveBill == 'y')
    {
        printf("\nSuccessfully saved");
    }

    // Free allocated memory
    free(order.customer);
    for (int i = 0; i < order.numOfItems; i++)
    {
        free(order.items[i].itemName);
    }
    free(order.items);
}

void searchInvoice(FILE *fp)
{
    rewind(fp); // Reset file position indicator to the beginning

    char searchName[MAX_STRING];
    printf("\nEnter the customer name to search for:\t");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    struct Order order;

    while (fscanf(fp, "%49s %49s %49s %d", order.customer->name, order.customer->phone, order.date, &order.numOfItems) == 4)
    {
        if (strcmp(order.customer->name, searchName) == 0)
        {
            order.items = malloc(order.numOfItems * sizeof(struct MenuItem));

            for (size_t i = 0; i < order.numOfItems; i++)
            {
                order.items[i].itemName = malloc(MAX_STRING * sizeof(char));
                fscanf(fp, "%49s %d %f", order.items[i].itemName, &order.items[i].quantity, &order.items[i].price);
            }

            // Assign the function pointer
            order.calculateTotal = calculateTotal;

            printBillDetails(&order);

            // Free allocated memory
            freeMenuItems(order.items, order.numOfItems);

            return; // Stop searching after finding the first matching invoice
        }
        else
        {
            // Move file pointer to the end of the current invoice to skip its details
            fseek(fp, order.numOfItems * (MAX_STRING + sizeof(int) + sizeof(float)), SEEK_CUR);
        }
    }

    printf("\nInvoice not found for customer: %s\n", searchName);
}

void exitProgram()
{
    printf("\n\t\t Exit Successfully\n\n");
    exit(0);
}
