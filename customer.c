
void orderProducts(const char *username, struct products *productArray, int numberOfProducts) {
    struct order newOrder;
    strcpy(newOrder.username, username);
    newOrder.total = 0.0;

    int orderQuantity;
    int productId;
    int productIndex;

    for (int i = 0; i < 100; ++i) {
        printf("Enter product ID to order (or -1 to finish): ");
        scanf("%d", &productId);

        if (productId == -1) {
            break;
        }

        productIndex = -1;
        for (int j = 0; j < numberOfProducts; ++j) {
            if (productArray[j].id == productId) {
                productIndex = j;
                break;
            }
        }

        if (productIndex == -1) {
            printf("Product with ID %d not found.\n", productId);
            continue;
        }

        printf("Enter quantity for product ID %d: ", productId);
        scanf("%d", &orderQuantity);

        if (orderQuantity <= 0 || orderQuantity > productArray[productIndex].qty) {
            printf("Invalid quantity.\n");
            continue;
        }


        newOrder.items[i] = productArray[productIndex];
        newOrder.quantities[i] = orderQuantity;
        newOrder.total += (productArray[productIndex].price + productArray[productIndex].gst) * orderQuantity;


        productArray[productIndex].qty -= orderQuantity;
    }


    FILE *orderFile = fopen("orders.txt", "a");
    if (orderFile == NULL) {
        printf("Error opening order file for writing.\n");
        return;
    }

    fprintf(orderFile, "%s,%.2f\n", newOrder.username, newOrder.total);

    for (int i = 0; i < 100; ++i) {
        if (newOrder.items[i].id != 0) {
            fprintf(orderFile, "%d,%s,%d,%.2f,%d\n", newOrder.items[i].id, newOrder.items[i].name,
                    newOrder.quantities[i], newOrder.items[i].price, newOrder.items[i].qty);
        } else {
            break;
        }
    }

    fclose(orderFile);


    writeProductsToFile("products.txt", productArray, numberOfProducts);

    printf("Order placed successfully.\n");
}


void displayOrderProducts(const char *username) {
    FILE *orderFile = fopen("orders.txt", "r");
    if (orderFile == NULL) {
        printf("Error opening order file for reading.\n");
        return;
    }

    char line[150];
    int orderCount = 0;

    while (fgets(line, sizeof(line), orderFile)) {
        char storedUsername[50];
        double total;
        sscanf(line, "%49[^,],%lf", storedUsername, &total);

        if (strcmp(username, storedUsername) == 0) {
            orderCount++;
            printf("Order %d - Total: $%.2f\n", orderCount, total);


            int productId, quantity;
            char productName[50];
            double price;

            while (fscanf(orderFile, "%d,%49[^,],%d,%lf,%*d\n", &productId, productName, &quantity, &price) == 5) {
                if (productId == 0) {
                    break;
                }

                printf("  Product ID: %d, Name: %s, Quantity: %d, Price: %.2f\n", productId, productName, quantity, price);
            }
        }
    }

    fclose(orderFile);

    if (orderCount == 0) {
        printf("No orders found for the user %s.\n", username);
    }
}
