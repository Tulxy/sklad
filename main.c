#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ean[14];
    char name[50];
    double purchase_price;
    double sale_price;
    int quantity;
    int vat_level;
} Product;

Product *warehouse = NULL;
int product_count = 0;
const char *DB_FILE = "warehouse.csv";

void save_to_file();
void load_from_file();

// Funkce pro přidání/úpravu paměti
void add_product() {
    Product *temp = realloc(warehouse, (product_count + 1) * sizeof(Product));
    if (!temp) {
        printf("Chyba pameti!\n");
        return;
    }
    warehouse = temp;

    printf("Zadejte EAN: ");
    scanf("%13s", warehouse[product_count].ean);
    printf("Zadejte nazev: ");
    scanf("%49s", warehouse[product_count].name);
    printf("Nakupni cena (bez DPH): ");
    scanf("%lf", &warehouse[product_count].purchase_price);
    printf("Prodejni cena (bez DPH): ");
    scanf("%lf", &warehouse[product_count].sale_price);
    printf("Pocet kusu: ");
    scanf("%d", &warehouse[product_count].quantity);
    printf("DPH (v %%): ");
    scanf("%d", &warehouse[product_count].vat_level);

    product_count++;
    save_to_file();
    printf("Produkt uspesne pridan a ulozen.\n");
}

void show_details(int i) {
    double price_with_vat = warehouse[i].sale_price * (1 + (warehouse[i].vat_level / 100.0));

    printf("\n--- DETAIL PRODUKTU ---\n");
    printf("EAN: %s | Nazev: %s\n", warehouse[i].ean, warehouse[i].name);
    printf("Skladem: %d ks\n", warehouse[i].quantity);
    printf("Nakupni cena: %.2f Kc\n", warehouse[i].purchase_price);
    printf("Prodejni cena: %.2f Kc (bez DPH) | %.2f Kc (s %d%% DPH)\n",
            warehouse[i].sale_price, price_with_vat, warehouse[i].vat_level);
    printf("-----------------------\n");
}

void list_all() {
    if (product_count == 0) {
        printf("Sklad je prazdny.\n");
        return;
    }
    for (int i = 0; i < product_count; i++) {
        printf("%d. [%s] %s - %d ks\n", i, warehouse[i].ean, warehouse[i].name, warehouse[i].quantity);
    }
}

void search_by_name() {
    char term[50];
    printf("Zadejte nazev k vyhledani: ");
    scanf("%49s", term);
    for (int i = 0; i < product_count; i++) {
        if (strstr(warehouse[i].name, term)) {
            show_details(i);
        }
    }
}

void delete_product() {
    list_all();
    if (product_count == 0) return;

    int id;
    printf("Zadejte ID ke smazani: ");
    scanf("%d", &id);

    if (id >= 0 && id < product_count) {
        for (int i = id; i < product_count - 1; i++) {
            warehouse[i] = warehouse[i + 1];
        }
        product_count--;
        warehouse = realloc(warehouse, product_count * sizeof(Product));
        save_to_file();
        printf("Smazano.\n");
    }
}

void save_to_file() {
    FILE *f = fopen(DB_FILE, "w");
    if (!f) return;

    for (int i = 0; i < product_count; i++) {
        fprintf(f, "%s;%s;%.2f;%.2f;%d;%d\n",
                warehouse[i].ean, warehouse[i].name, warehouse[i].purchase_price,
                warehouse[i].sale_price, warehouse[i].quantity, warehouse[i].vat_level);
    }
    fclose(f);
}

void load_from_file() {
    FILE *f = fopen(DB_FILE, "r");
    if (!f) return;

    Product temp;
    while (fscanf(f, " %13[^;];%49[^;];%lf;%lf;%d;%d\n",
           temp.ean, temp.name, &temp.purchase_price,
           &temp.sale_price, &temp.quantity, &temp.vat_level) == 6) {

        warehouse = realloc(warehouse, (product_count + 1) * sizeof(Product));
        warehouse[product_count] = temp;
        product_count++;
    }
    fclose(f);
    printf("Data nactena ze souboru (%d produktu).\n", product_count);
}

int main() {
    load_from_file();
    int choice;

    while (1) {
        printf("\n--- SKLAD (Dynamicky) ---\n");
        printf("1. Vypsat produkty\n2. Pridat produkt\n3. Hledat podle nazvu\n4. Smazat produkt\n5. Ukoncit\n");
        printf("Vase volba: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: list_all(); break;
            case 2: add_product(); break;
            case 3: search_by_name(); break;
            case 4: delete_product(); break;
            case 5:
                free(warehouse);
                return 0;
            default: printf("Neplatna volba.\n");
        }
    }
}