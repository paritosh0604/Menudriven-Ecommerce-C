#ifndef ECOMMERCE_H
#define ECOMMERCE_H

struct products
{
    int id;
    char name[50];     // Fix: Array declaration in struct should be char name[50], not char[50] name;
    char category[50]; // Fix: Array declaration in struct should be char category[50], not char[50] category;
    double price;
    double gst;
    int qty;
};

struct user
{
    char username[50]; // Fix: Array declaration in struct should be char username[50], not char[50] username;
    char password[50]; // Fix: Array declaration in struct should be char password[50], not char[50] password;
    char user_type[50]; // Fix: Array declaration in struct should be char user_type[50], not char[50] user_type;
};

struct order
{
    char username[50];
    struct products items[100];
    int quantities[100]; // Add quantities for each item
    double total;
};
void writeProductsToFile(const char *filename, const struct products *productArray, int numberOfProducts);
int readProductsFromFile(const char *filename, struct products *productArray, int maxProducts);
void displayProducts(const struct products *productArray, int numberOfProducts);
void deleteProduct(struct products *productArray, int *numberOfProducts, int productId);
void updateProduct(struct products *productArray, int numberOfProducts, int productId);

#endif

