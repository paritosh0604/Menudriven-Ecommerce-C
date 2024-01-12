#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ecommerce.h"
#include"customer.c"
#include"shopkeeper.c"
void writeUserToFile(const char *username, const char *password, const char *userType) {
    FILE *file = fopen("users.txt", "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s\n", username, password, userType);

    fclose(file);
}
int verifyUser(const char *username, const char *password, const char *userType) {
    FILE *file = fopen("users.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    char line[150];
    while (fgets(line, sizeof(line), file)) {
        char storedUsername[50], storedPassword[50], storedUserType[50];
        sscanf(line, "%49[^,],%49[^,],%49[^\n]", storedUsername, storedPassword, storedUserType);

        if (strcmp(username, storedUsername) == 0 &&
            strcmp(password, storedPassword) == 0 &&
            strcmp(userType, storedUserType) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
int main() {
    int choice;
    int numberOfProducts;
    struct products *productArray;

    do {
        printf("Enter your choice\n");
        printf("Enter 1 to Sign Up\n");
        printf("Enter 2 to Sign In\n");
        printf("Enter 3 to Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char username[50], password[50], user_type[50];
                printf("Enter the username\n");
                scanf("%s", username);
                printf("Enter the password\n");
                scanf("%s", password);
                printf("Enter the user type\n");
                scanf("%s", user_type);
                writeUserToFile(username, password, user_type);
                break;
            }
            case 2: {
                char username[50], password[50], user_type[50];
                printf("Enter the username\n");
                scanf("%s", username);
                printf("Enter the password\n");
                scanf("%s", password);
                printf("Enter the user type\n");
                scanf("%s", user_type);
                if (verifyUser(username, password, user_type)) {
                    printf("Authentication successful.\n");
                    if (strcmp(user_type, "customer") == 0) {
                        int c1;
                        do {
                            printf("Enter your choice\n");
                            printf("Enter 1 to Display Products\n");
                            printf("Enter 2 to Order Products\n");
                            printf("Enter 3 to Display Order Products\n");
                            printf("Enter 4 to Exit\n");
                            scanf("%d", &c1);
                            struct products readProductArray[100];
                            int numberOfReadProducts;
                            switch (c1) {
                                case 1:
                                    numberOfReadProducts = readProductsFromFile("products.txt", readProductArray, 100);
                                    displayProducts(readProductArray, numberOfReadProducts);
                                    break;
                                case 2:
                                    orderProducts(username, productArray, numberOfProducts);
                                    break;
                                case 3:displayOrderProducts(username);
                                    break;
                                case 4:
                                    printf("Exiting \n");
                                    break;
                                default:
                                    printf("Invalid choice\n");
                                    break;
                            }
                        } while (c1 != 4);
                    } else if (strcmp(user_type, "shopkeeper") == 0) {
                        int c2;
                        do {
                            printf("Enter your choice\n");
                            printf("Enter 1 to Add Products\n");
                            printf("Enter 2 to Update Products\n");
                            printf("Enter 3 to Delete Products\n");
                            printf("Enter 4 to Exit\n");
                            scanf("%d", &c2);

                            switch (c2) {
                                case 1:
                                    printf("Enter the number of products: ");
                                    scanf("%d", &numberOfProducts);

                                    productArray = (struct products *)malloc(numberOfProducts * sizeof(struct products));

                                    if (productArray == NULL) {
                                        printf("Memory allocation failed.\n");
                                        return 1;
                                    }

                                    for (int i = 0; i < numberOfProducts; ++i) {
                                        printf("Enter details for product %d:\n", i + 1);
                                        printf("ID: ");
                                        scanf("%d", &productArray[i].id);
                                        printf("Name: ");
                                        scanf("%s", productArray[i].name);
                                        printf("Category: ");
                                        scanf("%s", productArray[i].category);
                                        printf("Price: ");
                                        scanf("%lf", &productArray[i].price);
                                        printf("GST: ");
                                        scanf("%lf", &productArray[i].gst);
                                        printf("Quantity: ");
                                        scanf("%d", &productArray[i].qty);
                                    }

                                    writeProductsToFile("products.txt", productArray, numberOfProducts);
                                    break;
                                case 2:
                                    printf("Enter the ID of the product to update: ");
                                    int productIdToUpdate;
                                    scanf("%d", &productIdToUpdate);
                                    numberOfProducts = readProductsFromFile("products.txt", productArray, 100);
                                    updateProduct(productArray, numberOfProducts, productIdToUpdate);
                                    writeUpdatedProductsToFile("products.txt", productArray, numberOfProducts);
                                    break;

                                case 3:
                                    printf("Enter the ID of the product to delete: ");
                                    int productIdToDelete;
                                    scanf("%d", &productIdToDelete);
                                    numberOfProducts = readProductsFromFile("products.txt", productArray, 100);
                                    deleteProduct(productArray, &numberOfProducts, productIdToDelete);
                                    writeUpdatedProductsToFile("products.txt", productArray, numberOfProducts);
                                    break;
                                    case 4:
                                    printf("Exiting \n");
                                    break;

                                default:
                                    printf("Invalid choice\n");
                                    break;
                            }
                        } while (c2 != 4);
                    }
                } else {
                    printf("Authentication failed.\n");
                }
                break;
            }
            case 3:
                printf("Exiting \n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 3);

    if (productArray != NULL) {
        free(productArray);
    }

    return 0;
}

