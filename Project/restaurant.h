/*#ifndef RESTAURANT_H
#define RESTAURANT_H

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

void generateBillHeader(char name[50], char date[30]);
void generateBillBody(char item[30], int qty, float price);
void generateBillFooter(float total);

void saveOrderToFile(struct orders ord);
void showAllInvoices();
void searchInvoice(char name[50]);

#endif // RESTAURANT_H*/