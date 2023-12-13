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

// Struct for customer details
struct customer
{
    char name[MAX_STRING];
    char phone[MAX_STRING];
};

// Struct for menu items
struct items
{
    char **item; // double pointer for dynamic array of strings
    float price;
    int qty;
    enum Category category;
};

// Struct for orders
struct orders
{
    struct customer *customer; // pointer to struct customer
    char date[MAX_STRING];
    int numOfItems;
    struct items *itm;                                          // pointer to struct items
    float (*calculateTotal)(struct items *itm, int numOfItems); // function pointer
};

// Function to calculate total price
float calculateTotal(struct items *itm, int numOfItems)
{
    float total = 0;
    for (int i = 0; i < numOfItems; i++)
    {
        total += itm[i].qty * itm[i].price;
    }
    return total;
}

// Function to generate bill header
void generateBillHeader(struct customer *customer, char date[MAX_STRING])
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

// Function to generate bill body
void generateBillBody(struct items *itm)
{
    printf("%s \t\t", itm->item[0]); // Assuming only one item for simplicity
    printf("%d\t\t", itm->qty);
    printf("%.2f\t\t\n", itm->qty * itm->price);
}

// Function to generate bill footer
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

// Function to print bill details
void printBillDetails(struct orders *order)
{
    float tot = order->calculateTotal(order->itm, order->numOfItems);
    generateBillHeader(order->customer, order->date);

    for (size_t i = 0; i < order->numOfItems; i++)
    {
        generateBillBody(&order->itm[i]);
    }

    generateBillFooter(tot);
}

// Function to handle case 1
void generateInvoice(FILE *fp)
{
    struct orders ord;
    char saveBill = 'y';

    printf("\nPlease enter the name of the customer:\t");
    ord.customer = malloc(sizeof(struct customer));
    fgets(ord.customer->name, sizeof(ord.customer->name), stdin);
    ord.customer->name[strcspn(ord.customer->name, "\n")] = '\0';

    printf("\nPlease enter the phone number of the customer:\t");
    fgets(ord.customer->phone, sizeof(ord.customer->phone), stdin);
    ord.customer->phone[strcspn(ord.customer->phone, "\n")] = '\0';

    strcpy(ord.date, __DATE__);
    printf("\nPlease enter the number of items:\t");
    int num;
    scanf("%d", &num);
    ord.numOfItems = num;

    ord.itm = malloc(num * sizeof(struct items));

    float total = 0;
    for (size_t i = 0; i < num; i++)
    {
        while (getchar() != '\n')
            ; // Flush the input buffer
        printf("\n\nPlease enter the item %d:\t", i + 1);
        ord.itm[i].item = malloc(sizeof(char *));
        ord.itm[i].item[0] = malloc(MAX_STRING * sizeof(char));
        fgets(ord.itm[i].item[0], MAX_STRING, stdin);
        ord.itm[i].item[0][strcspn(ord.itm[i].item[0], "\n")] = '\0';

        printf("Please enter the quantity:\t");
        scanf("%d", &ord.itm[i].qty);
        printf("Please enter the unit price:\t");
        scanf("%f", &ord.itm[i].price);

        total += ord.itm[i].qty * ord.itm[i].price;
    }

    // Assign the function pointer
    ord.calculateTotal = calculateTotal;

    generateBillHeader(ord.customer, ord.date);
    for (size_t i = 0; i < ord.numOfItems; i++)
    {
        generateBillBody(&ord.itm[i]);
    }
    generateBillFooter(total);

    printf("\nDo you want to save the invoice? [y/n]\t");
    scanf(" %c", &saveBill);

    if (saveBill == 'y')
    {
        fseek(fp, 0, SEEK_END); // Move the file pointer to the end of the file
        fprintf(&ord, sizeof(struct orders), 1, fp);
        printf("\nSuccessfully saved");
    }

    // Free allocated memory
    free(ord.customer);
    for (int i = 0; i < ord.numOfItems; i++)
    {
        free(ord.itm[i].item[0]);
        free(ord.itm[i].item);
    }
    free(ord.itm);
}

// Function to handle case 2
void showAllInvoices(FILE *fp)
{
    struct orders order;

    fp = fopen("RestaurantBill.txt", "r+");
    if (fp != NULL)
    {
        while (fread(&order, sizeof(struct orders), 1, fp))
        {
            // Print bill details
            printBillDetails(&order);
        }
        fclose(fp);

        // Free memory for customer's name and phone outside the loop
        //free(order.customer);
    }
    else
    {
        perror("Error opening file for reading");
    }
}

// Function to handle case 3
void searchInvoice(FILE *fp)
{
    char name[MAX_STRING];

    printf("\nEnter the name of the customer:\t");
    // Flush the input buffer
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    fp = fopen("RestaurantBill.txt", "r");
    if (fp != NULL)
    {
        int invoiceFound = 0;
        printf("\n\t*****Invoices of %s*****\n", name);

        struct orders order;
        while (fread(&order, sizeof(struct orders), 1, fp))
        {
            float tot = order.calculateTotal(order.itm, order.numOfItems);
            // Use case-insensitive comparison for names
            if (_stricmp(order.customer->name, name) == 0)
            {
                generateBillHeader(order.customer, order.date);
                for (size_t i = 0; i < order.numOfItems; i++)
                {
                    generateBillBody(&order.itm[i]);
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
    else
    {
        perror("Error opening file for reading");
    }
}

// Function to handle case 4
void exitProgram()
{
    printf("\n\t\t Exit Successfully\n\n");
    exit(0);
}

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

        printf("You have chosen %d", opt);

        switch (opt)
        {
        case 1:
            fp = fopen("RestaurantBill.txt", "a+");
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
            fp = fopen("RestaurantBill.txt", "r");
            if (fp != NULL)
            {
                showAllInvoices(fp);
                fclose(fp);
            }
            break;

        case 3:
            fp = fopen("RestaurantBill.txt", "r");
            if (fp != NULL)
            {
                searchInvoice(fp);
                fclose(fp);
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
