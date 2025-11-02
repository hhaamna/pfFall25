#include <stdio.h>
#include <stdlib.h>

// making function to add books
void addBook(int isbns[100], char titles[100][50], float prices[100], int quantities[100], int *book_countptr)
{
    int newISBN;
    // checking if we have the max amount
    if (*book_countptr >= 100)
    {
        printf("Inventory full! Cannot add more books (limit = 100).\n");
        return;
    }
    else
    {
        printf("Enter ISBN for new book: "); // input for new isbn
        scanf("%d", &newISBN);
        // checking for repeats
        for (int i = 0; i < *book_countptr; i++)
        {
            if (isbns[i] == newISBN)
            {
                printf("This book already exists in the inventory!\n");
                return;
            }
        }
        // if there are no duplicates
        isbns[*book_countptr] = newISBN;

        printf("Enter Book Title: ");
        scanf(" %[^\n]", titles[*book_countptr]);

        printf("Enter Quantity: ");
        scanf("%d", &quantities[*book_countptr]);

        printf("Add Book Price: $");
        scanf("%f", &prices[*book_countptr]);

        // book count is increased
        (*book_countptr)++;

        printf("Book succeessfully added to inventory!\n");

    }
}

// making function to process sales
void processSale(int isbns[100], int *book_countptr, int quantities[100], char titles[100][50])
{
    int copies_sold, ISBN, found = 0;

    printf("Enter ISBN for book to sell: ");
    scanf("%d", &ISBN);

    for(int i = 0; i < *book_countptr; i++)
    {
        if(ISBN == isbns[i])
        {
            found = i;
        }
    }

    //giving book data
    printf("--BOOK DATA--\nBook Title: %s\nAvailable Quantity: %d\n", titles[found], quantities[found]);

    printf("Enter number of copies to sell: ");
    scanf("%d", &copies_sold);

    if(copies_sold > quantities[found])
    {
        printf("Book is Out of Stock!\n");
    }
    else
    {
        quantities[found] -= copies_sold;
        printf("Book(s) sold successfully!\nRemaining Quantity: %d\n", quantities[found]);
    }

}

// making function to generate low stock report
void lowStock(int isbns[100], char titles[100][50], int quantities[100], float prices[100], int *book_countptr)
{
    int low[100];
    int found;

    printf("--Low Stock Report--\n");

    for(int i = 0; i < *book_countptr; i++)
    {
        if(quantities[i] < 5)
        {
            found = 1;
            low[i] = quantities[i];
            printf("Book ISBN: %d\nBook Title: %s\nBook Price: $%.2f\nAvailable Quantity: %d\n\n", isbns[i], titles[i], prices[i], quantities[i]);
        }
    }
    
    if(found != 1)
    {
        printf("No books have quantity below 5!\n");
    }
}

// making function to exit
void exitfn()
{
    printf("Exited Menu!\n");
    exit(0);
}

int main()
{
    int isbns[100];
    char titles[100][50];
    float prices[100];
    int quantities[100];

    int book_count = 0;
    int *book_countptr = &book_count;

    int choice;
    do
    {
        printf("==MAIN MENU==\n");
        printf("1- Add New Book\n2- Process a Sale\n3- Generate Low-Stock Report\n4- Exit\n");
        printf("Select Option(1-4): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook(isbns, titles, prices, quantities, book_countptr);
            break;
        case 2:
            processSale(isbns, book_countptr, quantities, titles);
            break;
        case 3:
            lowStock(isbns, titles, quantities, prices, book_countptr);
            break;
        case 4:
            exitfn();
            break;
        default:
            printf("Invalid option selected!\n");
            break;
        }
    } while (choice != 4); // loop goes on until user exits

    return 0;
}