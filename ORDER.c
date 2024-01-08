#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PRODUCTS 100
#define MAX_QUANTITY 1000
#define MAX_NAME 50

typedef struct
{
     char name[MAX_NAME];
     float price;
     int stock;
} product;

typedef struct
{
     int index;
     int quantity;
} Ord_prd;

product Products[MAX_PRODUCTS];
int num_Products = 0;

Ord_prd ordered_Products[MAX_PRODUCTS];
int numOrdered_Products = 0;

void press_any_key();
void show_UI();
void login_UI();
void exitp();
void admin_UI();

void list_products();
void add_products();
void remove_products();
void reset_list();
void list_only();

void order_UI();

void save_file();
void load_file();

void display_detailed_receipt(Ord_prd ordered_Products[], int numOrdered_Products, float grand_total);
void update_receipt(float amount_received, float grand_total);
void save_detailed_receipt(Ord_prd ordered_Products[], int numOrdered_Products, float grand_total);

int main()
{
     load_file();

     system("cls");

     printf("\t\t\t\t\t******************************");
     printf("\n\t\t\t\t\t  Welcome to Ordering Sytem!\n");
     printf("\t\t\t\t\t******************************");
     show_UI();

     return 0;
}

void press_any_key()
{
     printf("\n\n\nPress ENTER to go back... ");
     fflush(stdout);

     int ch;
     do
     {
          ch = getchar();
     } while (ch != EOF && ch != '\n' && ch != '\r');
}

void list_only()
{
     printf("\n\t\t\t\t - - - - Product List - - - - \n\n");
     printf("\t\t\t [%5s]    %-10s\t   %-8s\t  %-5s\n", "Index", "Product", "Price", "Stock");
     for (int i = 0; i < num_Products; i++)
     {
          printf("\t\t\t  [%2i ]     %-10s\t   Php %-7.2f\t   %-5i\n", i + 1, Products[i].name, Products[i].price, Products[i].stock);
     }
}

void reset_list()
{
     system("cls");

     printf("\n");
     char text1[] = {"Resetting list..  Please wait...\n"};
     for (int i = 0; text1[i] != '\0'; i++)
     {
          printf("%c", text1[i]);
          fflush(stdout);
          usleep(50000);
     }
     num_Products = 0;
     printf("\nProduct list has been reset. ");
     getchar();
     press_any_key();
}

void list_products()
{
     getchar();
     system("cls");
     if (num_Products > 0)
     {
          printf("\n\t\t\t\t - - - - Product List - - - - \n\n");
          printf("\t\t\t [%5s]    %-10s\t   %-8s\t  %-5s\n", "Index", "Product", "Price", "Stock");
          for (int i = 0; i < num_Products; i++)
          {
               printf("\t\t\t  [%2i ]     %-10s\t   Php %-7.2f\t   %-5i\n", i + 1, Products[i].name, Products[i].price, Products[i].stock);
          }
          press_any_key();
     }
     else
     {
          printf("\nTheres currently 0 item to be displayed!");
          press_any_key();
     }
}

void add_products()
{
     char chr;

     do
     {
          system("cls");
          printf("\n\t\t\t\t     - - - - A D D  P R O D U C T S - - - - \n\n");
          if (num_Products < MAX_PRODUCTS)
          {
               printf("\n\t\t\t   Enter Product Name:       ");
               scanf("%49s", Products[num_Products].name);
               printf("\t\t\t  Enter Product Price: [Php] ");
               scanf("%f", &Products[num_Products].price);
               printf("\t\t\tEnter Stock (max1000):       ");
               scanf("%i", &Products[num_Products].stock);
               if (Products[num_Products].stock > 1000)
               {
                    system("cls");
                    printf("\n\t\t\t\t Stock Exceeded... \n\n\t\t\t\t Stock will be automatically set to 1000.\n");
                    Products[num_Products].stock = MAX_QUANTITY;
               }
               num_Products++;
               printf("\n\t\t\t\t Product Added Succesfully!");
          }
          else
          {
               printf("\n\t\t\t Number of Products Exceeded!");
          }
          printf("\n\n\t\t\t\t Add products again? (y/n) ");
          scanf(" %c", &chr);
     } while (tolower(chr) == 'y');
}

void remove_products()
{
     system("cls");

     list_only();

     if (num_Products > 0)
     {
          int index;
          printf("\nEnter the index [#] of the product you want to remove: ");
          scanf("%i", &index);

          if (index > 0 && index <= num_Products)
          {
               for (int i = index - 1; i < num_Products - 1; i++)
               {
                    Products[i] = Products[i + 1];
               }
               num_Products--;
               printf("\nProduct removed succesfully!");
               getchar();
               press_any_key();
          }
          else
          {
               printf("\nInvalid Index!");
               getchar();
               press_any_key();
          }
     }
     else
     {
          printf("\nNo Product to remove.");
          getchar();
          press_any_key();
     }
}

void show_UI()
{
     int ui_choice;

     printf("\n\n\t\t\t\t\t1. Order\n\t\t\t\t\t2. Login (ADMIN)\n\t\t\t\t\t3. Exit\n\n\t\t\t\t\t--> ");
     scanf(" %i", &ui_choice);

     switch (ui_choice)
     {
     case 1:
          order_UI();
          break;
     case 2:
          login_UI();
          break;
     default:
          exitp();
          break;
     }
}

void login_UI()
{
     char username[15];
     char password[15];
     int attempts = 3;
     char choice;

     do
     {
          system("cls");
          printf("\n\n\n\t\t\t\t\tusername:  ");
          scanf("%s", username);
          scanf("%c");

          printf("\t\t\t\t\tpassword:  ");
          scanf("%s", password);

          if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
          {
               admin_UI();
               break;
          }
          else
          {
               system("cls");
               attempts--;
               printf("\nLogin Unsuccesful! Invalid username/password. \nYou have %i attempts left.", attempts);
               printf("\nInput again?(y/n)");
               scanf(" %c", &choice);
               choice = tolower(choice);
               if (attempts == 0)
               {
                    system("cls");
                    printf("\nSorry!\nYou have exceeded the maximum number of attempts!\n");
                    exitp();
                    break;
               }
          }
     } while (attempts > 0 && choice == 'y');
}

void admin_UI()
{
     int admin_choice;
     do
     {
          system("cls");
          printf("\t\t\t\t\t******************************");
          printf("\n\t\t\t\t\t     A D M I N  P A N E L  \n");
          printf("\t\t\t\t\t******************************");
          printf("\n\n\t\t\t\t\t1. List all Products\n\t\t\t\t\t2. Add Products\n\t\t\t\t\t3. Remove Products\n\t\t\t\t\t4. Reset List\n\t\t\t\t\t5. Save/Exit\n\n\n\t\t\t\t\t--> ");
          scanf("%i", &admin_choice);

          switch (admin_choice)
          {
          case 1:
               list_products();
               break;
          case 2:
               add_products();
               break;
          case 3:
               remove_products();
               break;
          case 4:
               reset_list();
               break;
          default:
               exitp();
               break;
          }

     } while (admin_choice != 5);
}

void exitp()
{
     save_file();

     system("cls");
     char text[] = {"Exiting program....\n\n\n\n"};
     for (int i = 0; text[i] != '\0'; i++)
     {
          printf("%c", text[i]);
          fflush(stdout);
          usleep(10000);
     }
     system("cls");
     exit(0);
}

void save_file()
{
     FILE *file = fopen("Save.dat", "wb");

     if (file != NULL)
     {
          fwrite(Products, sizeof(product), num_Products, file);
          fclose(file);
     }
     else
     {
          printf("\nError saving to file.");
     }
}

void load_file()
{
     FILE *file = fopen("Save.dat", "rb");

     if (file != NULL)
     {
          num_Products = fread(Products, sizeof(product), MAX_PRODUCTS, file);
          fclose(file);
     }
     else
     {
          printf("\nNo previous data found. Starting with an empty product list. ");
     }
}

void order_UI()
{
     system("cls");
     list_only();

     float grand_total = 0;

     char ord_chc;
     do
     {
          int product_Index, quantity;

          printf("\nEnter the product index [#] of the product you want to order: ");
          scanf("%i", &product_Index);

          if (product_Index > 0 && product_Index <= num_Products)
          {
               printf("\nEnter the quantity: ");
               scanf("%i", &quantity);
               if (quantity > 0 && quantity <= Products[product_Index - 1].stock)
               {
                    Products[product_Index - 1].stock -= quantity;
                    float total_cost = quantity * Products[product_Index - 1].price;

                    grand_total += total_cost;

                    ordered_Products[numOrdered_Products].index = product_Index;
                    ordered_Products[numOrdered_Products].quantity = quantity;
                    numOrdered_Products++;

                    printf("\nYou have ordered!\n\nProduct: %10s \t Quantity:  %5i \t SubTotal:  %5.2f\n", Products[product_Index - 1].name, quantity, total_cost);
               }
               else
               {
                    printf("\nInvalid quantity or insufficient stock.");
               }
          }
          else
          {
               printf("\nInvalid product index. ");
          }

          getchar();
          printf("\nDo you want to add more products? (y/n) ");
          scanf("%c", &ord_chc);

          if (tolower(ord_chc) == 'y')
          {
               system("cls");
               list_only();
          }

     } while (tolower(ord_chc) == 'y');

     display_detailed_receipt(ordered_Products, numOrdered_Products, grand_total);

     float amount_received;
     printf("\n\t\t  Enter the amount received: ");
     scanf("%f", &amount_received);

     update_receipt(amount_received, grand_total);
     save_detailed_receipt(ordered_Products, numOrdered_Products, grand_total);

     getchar();
     press_any_key();
     exitp();
}

void display_detailed_receipt(Ord_prd ordered_Products[], int numOrdered_Products, float grand_total)
{
     system("cls");
     printf("\n\t\t - - - -  Receipt - - - - \n");

     if (grand_total > 0)
     {
          printf("\n%-20s %-10s   %6s \t%4s\n", "Product", "Quantity", "Price", "Subtotal");
          for (int i = 0; i < numOrdered_Products; i++)
          {
               int index = ordered_Products[i].index;
               int quantity = ordered_Products[i].quantity;
               float price = Products[index - 1].price;
               float Subtotal = price * quantity;

               printf("%-20s \t%-10d %-10.2f    %-10.2f\n", Products[index - 1].name, quantity, price, Subtotal);
          }
          printf("\n\t\t\t\tGrand total: %.2f", grand_total);
     }
}

void update_receipt(float amount_received, float grand_total)
{
     system("cls");
     printf("\n\t\t - - - -  Receipt - - - - \n");

     if (grand_total > 0)
     {
          printf("\n%-20s %-10s   %6s \t%4s\n", "Product", "Quantity", "Price", "Subtotal");

          for (int i = 0; i < numOrdered_Products; i++)
          {
               int index = ordered_Products[i].index;
               int quantity = ordered_Products[i].quantity;
               float price = Products[index - 1].price;
               float Subtotal = price * quantity;

               printf("%-20s \t%-10d %-10.2f    %-10.2f\n", Products[index - 1].name, quantity, price, Subtotal);
          }

          printf("\n\t\t\t\tGrand total: %.2f\n", grand_total);

          if (amount_received >= grand_total)
          {
               float change = amount_received - grand_total;
               printf("\nAmount Received: %.2f\nChange: %.2f\n", amount_received, change);
               printf("\nThanks for shopping!");
          }
          else
          {
               printf("\nInsufficient amount received. Please provide the correct amount.\n");
          }
     }
}

void save_detailed_receipt(Ord_prd ordered_Products[], int numOrdered_Products, float grand_total)
{
     FILE *r_file = fopen("receipt.txt", "w");

     if (r_file != NULL)
     {
          fprintf(r_file, "\n\t\t\t\t- - - -  Receipt - - - - \n");
          fprintf(r_file, "\n%-20s %-10s   %6s \t\t%4s\n", "Product", "Quantity", "Price", "Subtotal");

          for (int i = 0; i < numOrdered_Products; i++)
          {
               int index = ordered_Products[i].index;
               int quantity = ordered_Products[i].quantity;
               float price = Products[index - 1].price;
               float Subtotal = price * quantity;

               fprintf(r_file, "%-20s \t%-10d%-10.2f    %-10.2f\n", Products[index - 1].name, quantity, price, Subtotal);
          }

          fprintf(r_file, "\n\t\t\t\t\t\t\tGrand total: %.2f\n", grand_total);
          fclose(r_file);
          printf("\nReceipt has been saved to 'receipt.txt'.");
     }
}
