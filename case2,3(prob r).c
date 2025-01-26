case 2:
            fp = fopen("RestaurantBill.bin", "rb");
            if (fp != NULL)
            {
                while (fread(&order, sizeof(struct orders), 1, fp))
                {
                    order.customer = malloc(sizeof(struct customer));
                    float tot = order.calculateTotal(order.itm, order.numOfItems);
                    generateBillHeader(order.customer, order.date);
                    for (size_t i = 0; i < order.numOfItems; i++)
                    {
                        generateBillBody(&order.itm[i]);
                    }
                    generateBillFooter(tot);
                    printf("Customer: %s\n", order.customer->name);
                    printf("Phone: %s\n", order.customer->phone);
                    printf("--------------------------------------\n");

                    // Free memory for customer's name and phone
                    free(order.customer);
                }
                fclose(fp);
            }
            break;

        case 3:
            printf("\nEnter the name of the customer:\t");
            // Flush the input buffer
            char name[MAX_STRING];
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            fp = fopen("RestaurantBill.bin", "rb");
            printf("\n\t*****Invoices of %s*****\n", name);

            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = order.calculateTotal(order.itm, order.numOfItems);
                if (!strcmp(order.customer->name, name))
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
            break;
