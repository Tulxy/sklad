#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 1000

struct Product {
    int index;
    char name[50];
    int price;
    int quantity;
};

struct Product warehouse[MAX_PRODUCTS];
int product_count = 0;

/* printf("4. Show product details");
printf("\n");
printf("5. Delete product");
printf("\n");
printf("6. Edit product");
printf("\n");
*/

int menu_text() {
    printf("\nMenu: ");
    printf("\n");
    printf("1. Show all products");
    printf("\n");
    printf("2. Search name");
    printf("\n");
    printf("3. Search by price");
    printf("\n");
    printf("4. Add product");
    printf("\n");
    printf("5. Delete product");
    printf("\n");
    printf("6. Update product");
    printf("\n");
    printf("7. Exit");
    printf("\n\n");

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");
    return choice;
}

void show_products() {
    for (int i = 0; i < product_count; i++) {
        printf("ID: %d\n", warehouse[i].index);
        printf("Product name: %s", warehouse[i].name);
    }
}

void add_product() {
    char name[50];
    int price, quantity;

    if (product_count >= MAX_PRODUCTS) {
        printf("Maximum number of products reached.\n");
    }

    printf("Enter the name of the product: ");
    scanf("%s", name);
    printf("Enter the price of the product: ");
    scanf("%d", &price);
    printf("Enter the quantity of the product: ");
    scanf("%d", &quantity);

    warehouse[product_count].index = product_count;
    strcpy(warehouse[product_count].name, name);
    warehouse[product_count].price = price;
    warehouse[product_count].quantity = quantity;

    product_count++;
}

void search_product_by_name() {
}

void search_product_by_price() {
}

void show_details() {
}

void menu(void) {
    int choice;
    do {
        choice = menu_text();
        switch (choice) {
            case 1:
                show_products();
                break;
            case 2:
                search_product_by_name();
                break;
            case 3:
                search_product_by_price();
                break;
            case 4:
                add_product();
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice");
        }
    } while (choice <= 7);
}

int main(void) {
    menu();

    return 0;
}
