#include <stdio.h>
#include <stdlib.h>
#include "ecommerce.h"

void writeProductsToFile(const char *filename, const struct products *productArray, int numberOfProducts) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numberOfProducts; ++i) {
        fprintf(file, "%d,%s,%s,%.2f,%.2f,%d\n",
                productArray[i].id,
                productArray[i].name,
                productArray[i].category,
                productArray[i].price,
                productArray[i].gst,
                productArray[i].qty);
    }

    fclose(file);
}

int readProductsFromFile(const char *filename, struct products *productArray, int maxProducts) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 0;
    }

    int count = 0;

    while (fscanf(file, "%d,%49[^,],%49[^,],%lf,%lf,%d\n",
                  &productArray[count].id,
                  productArray[count].name,
                  productArray[count].category,
                  &productArray[count].price,
                  &productArray[count].gst,
                  &productArray[count].qty) == 6) {
        count++;

        if (count >= maxProducts) {
            break;
        }
    }

    fclose(file);
    return count;
}

void displayProducts(const struct products *productArray, int numberOfProducts) {
    printf("%-5s %-20s %-20s %-10s %-10s %-5s\n", "ID", "Name", "Category", "Price", "GST", "Qty");

    for (int i = 0; i < numberOfProducts; ++i) {
        printf("%-5d %-20s %-20s %-10.2f %-10.2f %-5d\n",
               productArray[i].id,
               productArray[i].name,
               productArray[i].category,
               productArray[i].price,
               productArray[i].gst,
               productArray[i].qty);
    }
}


void deleteProduct(struct products *productArray, int *numberOfProducts, int productId) {
    int found = 0;
    for (int i = 0; i < *numberOfProducts; ++i) {
        if (productArray[i].id == productId) {
            for (int j = i; j < *numberOfProducts - 1; ++j) {
                productArray[j] = productArray[j + 1];
            }
            found = 1;
            break;
        }
    }

    if (found) {
        (*numberOfProducts)--;
        printf("Product with ID %d deleted successfully.\n", productId);
    } else {
        printf("Product with ID %d not found.\n", productId);
    }
}


void updateProduct(struct products *productArray, int numberOfProducts, int productId) {
    int found = 0;
    for (int i = 0; i < numberOfProducts; ++i) {
        if (productArray[i].id == productId) {
            printf("Enter new details for product %d:\n", productId);
            printf("Name: ");
            scanf(" %49[^\n]", productArray[i].name);
            printf("Category: ");
            scanf(" %49[^\n]", productArray[i].category);
            printf("Price: ");
            scanf("%lf", &productArray[i].price);
            printf("GST: ");
            scanf("%lf", &productArray[i].gst);
            printf("Quantity: ");
            scanf("%d", &productArray[i].qty);

            found = 1;
            printf("Product with ID %d updated successfully.\n", productId);
            break;
        }
    }

    if (!found) {
        printf("Product with ID %d not found.\n", productId);
    }
}

void writeUpdatedProductsToFile(const char *filename, const struct products *productArray, int numberOfProducts) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numberOfProducts; ++i) {
        fprintf(file, "%d,%s,%s,%.2f,%.2f,%d\n",
                productArray[i].id,
                productArray[i].name,
                productArray[i].category,
                productArray[i].price,
                productArray[i].gst,
                productArray[i].qty);
    }

    fclose(file);
}

