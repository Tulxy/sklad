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

void load_test_data() {
    // Laptop
    warehouse[0].index = 0;
    strcpy(warehouse[0].name, "Laptop");
    warehouse[0].price = 25000;
    warehouse[0].quantity = 5;

    // Mouse
    warehouse[1].index = 1;
    strcpy(warehouse[1].name, "Mouse");
    warehouse[1].price = 500;
    warehouse[1].quantity = 20;

    // Keyboard
    warehouse[2].index = 2;
    strcpy(warehouse[2].name, "Keyboard");
    warehouse[2].price = 1500;
    warehouse[2].quantity = 15;

    // Monitor
    warehouse[3].index = 3;
    strcpy(warehouse[3].name, "Monitor");
    warehouse[3].price = 8000;
    warehouse[3].quantity = 8;

    // Headphones
    warehouse[4].index = 4;
    strcpy(warehouse[4].name, "Headphones");
    warehouse[4].price = 2500;
    warehouse[4].quantity = 12;

    product_count = 5;
    printf("Test data loaded: 5 products added.\n\n");
}

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
    printf("5. Show details");
    printf("\n");
    printf("6. Delete product");
    printf("\n");
    printf("7. Edit product");
    printf("\n");
    printf("8. Exit");
    printf("\n\n");

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");
    return choice;
}


// Vypíše všechny produkty na skladě
void show_products() {
    for (int i = 0; i < product_count; i++) {
        printf("ID: %d. ", warehouse[i].index);
        printf("Product name: %s\n", warehouse[i].name);
    }
}

// Zkontroluje jestli nebyl překročen limit produktů a pak uživatel zadá informace o produktu a ten se přidá na sklad
void add_product() {
    char name[50];
    int price, quantity;

    if (product_count >= MAX_PRODUCTS) {
        printf("Maximum number of products reached.\n");
        return;
    }

    printf("Enter the name of the product: ");
    scanf("%49s", name);

    for (int i = 0; i < product_count; i++) {
        if (strcmp(name, warehouse[i].name) == 0) {
            printf("Product with this name already exists!\n");
            return;
        }
    }
    strcpy(warehouse[product_count].name, name);


    printf("Enter the price of the product: ");
    scanf("%d", &price);
    if (price >= 0) {
        warehouse[product_count].price = price;
    } else {
        printf("Invalid price.\n");
        return;
    }

    printf("Enter the quantity of the product: ");
    scanf("%d", &quantity);
    if (quantity >= 0) {
        warehouse[product_count].quantity = quantity;
    } else {
        printf("Invalid quantity.\n");
        return;
    }

    warehouse[product_count].index = product_count;

    printf("New product added!"
           "Product name: %s\n", name);
    printf("Product price: %d\n", warehouse[product_count].price);
    printf("Product quantity: %d\n", warehouse[product_count].quantity);

    product_count++;
}

// Vypíše informace o produktu
void show_product_info(const int product_index) {
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║            PRODUCT DETAILS            ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    printf("ID: %d\n", warehouse[product_index].index);
    printf("Name: %s\n", warehouse[product_index].name);
    printf("Price: %d Kč\n", warehouse[product_index].price);
    if (warehouse[product_index].quantity > 0) {
        printf("Quantity: %d\n", warehouse[product_index].quantity);
        printf("Total value: %d Kč\n", warehouse[product_index].price * warehouse[product_index].quantity);
    } else {
        printf("Out of stock.\n");
    }
    printf("═══════════════════════════════════════\n\n");
}

// Zeptá se uživatele jakého produktu detaily chce vidět a zavolá funkci která je vypíše "show_product_info()"
void show_details() {
    if (product_count == 0) {
        printf("No product exists.\n");
        return;
    }

    show_products();
    printf("\n");

    int product_index;
    printf("Enter product ID to show details: ");
    scanf("%d", &product_index);

    if (product_index < 0 || product_index >= product_count) {
        printf("Invalid product ID.\n");
        return;
    }

    show_product_info(product_index);
}

/* Vyhledá produkt podle jména
 * Pokud najde zavolá funkci "show_product_info"
 * Pokud nenajde vypíše že nenašel a ukončí funkci
*/
void search_product_by_name() {
    if (product_count == 0) {
        printf("No product exists.\n");
        return;
    }

    char search_name[50];
    printf("Enter the name of the product: ");
    scanf("%49s", search_name);

    int found = 0;
    for (int i = 0; i < product_count; i++) {
        if (strcmp(search_name, warehouse[i].name) == 0) {
            printf("Product Found!\n");
            show_product_info(i);
            found = 1;
        }
    }
    if (!found) {
        printf("No product found.\n");
    }
}

/* Vyhledá produkt podle ceny
 * Pokud najde zavolá funkci "show_product_info"
 * Pokud nenajde vypíše že nenašel a ukončí funkci
*/
void search_product_by_price() {
    if (product_count == 0) {
        printf("No product exists.\n");
        return;
    }

    int search_min_price;
    int search_max_price;
    printf("Enter the minimal price of the product: ");
    scanf("%d", &search_min_price);
    printf("Enter the maximal price of the product: ");
    scanf("%d", &search_max_price);

    int found = 0;
    for (int i = 0; i < product_count; i++) {
        if (search_max_price >= warehouse[i].price && search_min_price <= warehouse[i].price) {
            printf("Product Found!\n");
            show_product_info(i);
            found = 1;
        }
    }
    if (!found) {
        printf("No product found.\n");
    }
}

// Smaže vybraný produkt a přeindexuje zbytek produktů
void delete_product() {
    if (product_count == 0) {
        printf("No products found.\n");
        return;
    }

    show_products();
    printf("\n");

    int index;
    printf("Enter ID of product you want to delete: ");
    scanf("%d", &index);

    if (index < 0 || index >= product_count) {
        printf("Invalid product ID.\n");
        return;
    }

    char deleted_name[50];
    strcpy(deleted_name, warehouse[index].name);

    for (int i = index; i < product_count - 1; i++) {
        warehouse[i] = warehouse[i + 1];
        warehouse[i].index = i;
    }

    product_count--;
    printf("\n✓ Product '%s' deleted successfully!\n", deleted_name);
}

// Výpis menu pro úpravy produktu
int edit_menu() {
    printf("What would you like to edit?\n");
    printf("1. Name\n");
    printf("2. Price\n");
    printf("3. Quantity\n");
    printf("4. Exit\n");

    int choice;
    scanf("%d", &choice);
    return choice;
}

// Úprava jména produktu
void edit_name(int product_index) {
    char new_name[50];
    printf("Enter the new product name: ");
    scanf("%49s", new_name);

    for (int i = 0; i < product_count; i++) {
        if (i != product_index && strcmp(new_name, warehouse[i].name) == 0) {
            printf("Product with this name already exists!\n");
            return;
        }
    }

    strcpy(warehouse[product_index].name, new_name);
    printf("Name updated!\n"
           "New product name: %s\n", new_name);
}

// Úprava ceny produktu
void edit_price(int product_index) {
    int new_price;
    printf("Enter the new price of the product: ");
    scanf("%d", &new_price);

    if (new_price < 0) {
        printf("Invalid price.\n");
        return;
    }
    warehouse[product_index].price = new_price;

    printf("Price updated!\n");
    printf("New price: %d\n", warehouse[product_index].price);
}

// Úprava kvantity produktu
void edit_quantity(int product_index) {
    int new_quantity;
    printf("Enter the new quantity of the product: ");
    scanf("%d", &new_quantity);

    if (new_quantity < 0) {
        printf("Invalid quantity. Must be >= 0\n");
        return;
    }

    warehouse[product_index].quantity = new_quantity;
    printf("Quantity updated!\n");
    printf("New quantity: %d\n", warehouse[product_index].quantity);
}

// Zavolá vybranou funkci
void product_edit_menu(int product_index) {
    int choice;

    do {
        choice = edit_menu();
        switch (choice) {
            case 1: edit_name(product_index); break;
            case 2: edit_price(product_index); break;
            case 3: edit_quantity(product_index); break;
            case 4: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice!\n"); break;
        }
    } while (choice != 4);
}

// Zavolá menu pro úpravy vybraného produktu a předá index vybraného produktu
void edit_product() {
    if (product_count == 0) {
        printf("No products found.\n");
        return;
    }

    show_products();

    printf("\n");

    int product_index;
    printf("Enter ID of product you want to edit: ");
    scanf("%d", &product_index);

    if (product_index < 0 || product_index >= product_count) {
        printf("Invalid product ID.\n");
        return;
    }

    product_edit_menu(product_index);
}

// Základní menu
void menu(void) {
    int choice;
    do {
        choice = menu_text();
        switch (choice) {
            case 1: show_products(); break;
            case 2: search_product_by_name(); break;
            case 3: search_product_by_price(); break;
            case 4: add_product(); break;
            case 5: show_details(); break;
            case 6: delete_product(); break;
            case 7: edit_product(); break;
            case 8: exit(0);
            default: printf("Invalid choice");
        }
    } while (choice <= 8);
}

// Hlavní loop
int main(void) {
    printf("Load test data? (1 = Yes, 0 = No): ");
    int load_test;
    scanf("%d", &load_test);

    if (load_test) {
        load_test_data();
    }

    menu();
    return 0;
}
