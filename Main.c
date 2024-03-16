#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for storing book details
typedef struct {
    char title[100];
    char author[100];
    char genre[50];
    float price;
    int quantity;
} Book;

// Function prototypes
void displayMenu();
void addBook(Book books[], int *count);
void searchBook(Book books[], int count, char searchTitle[]);
void displayBooks(Book books[], int count);
void saveBooksToFile(Book books[], int count, const char *filename);
void loadBooksFromFile(Book books[], int *count, const char *filename);

int main() {
    Book books[100]; // Array to store books
    int count = 0;   // Current number of books in inventory

    // Load book data from file at the beginning
    loadBooksFromFile(books, &count, "books.txt");

    int choice;
    char searchTitle[100];

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &count);
                break;
            case 2:
                printf("Enter the title to search: ");
                scanf(" %[^\n]", searchTitle);
                searchBook(books, count, searchTitle);
                break;
            case 3:
                displayBooks(books, count);
                break;
            case 4:
                printf("Exiting the program.\n");
                // Save book data to file before exiting
                saveBooksToFile(books, count, "books.txt");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (1);

    return 0;
}

// Function to display menu options
void displayMenu() {
    printf("\n===== Online Bookstore Management System =====\n");
    printf("1. Add a book\n");
    printf("2. Search for a book\n");
    printf("3. Display all books\n");
    printf("4. Exit\n");
}

// Function to add a new book
void addBook(Book books[], int *count) {
    if (*count >= 100) {
        printf("Cannot add more books. Inventory full.\n");
        return;
    }

    printf("Enter book details:\n");
    printf("Title: ");
    scanf(" %[^\n]", books[*count].title);
    printf("Author: ");
    scanf(" %[^\n]", books[*count].author);
    printf("Genre: ");
    scanf(" %[^\n]", books[*count].genre);
    printf("Price: ");
    scanf("%f", &books[*count].price);
    printf("Quantity: ");
    scanf("%d", &books[*count].quantity);

    (*count)++;
    printf("Book added successfully.\n");
}

// Function to search for a book by title
void searchBook(Book books[], int count, char searchTitle[]) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].title, searchTitle) == 0) {
            printf("Book found:\n");
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Genre: %s\n", books[i].genre);
            printf("Price: %.2f\n", books[i].price);
            printf("Quantity: %d\n", books[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Book not found.\n");
}

// Function to display all books
void displayBooks(Book books[], int count) {
    if (count == 0) {
        printf("No books in inventory.\n");
        return;
    }

    printf("List of all books:\n");
    for (int i = 0; i < count; i++) {
        printf("Title: %s, Author: %s, Genre: %s, Price: %.2f, Quantity: %d\n",
               books[i].title, books[i].author, books[i].genre,
               books[i].price, books[i].quantity);
    }
}

// Function to save book data to a file
void saveBooksToFile(Book books[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s|%s|%s|%.2f|%d\n", books[i].title, books[i].author,
                books[i].genre, books[i].price, books[i].quantity);
    }

    fclose(file);
}

// Function to load book data from a file
void loadBooksFromFile(Book books[], int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    while (fscanf(file, " %[^\n]", books[*count].title) == 1) {
        fscanf(file, " %[^\n]", books[*count].author);
        fscanf(file, " %[^\n]", books[*count].genre);
        fscanf(file, "%f", &books[*count].price);
        fscanf(file, "%d", &books[*count].quantity);
        (*count)++;
    }

    fclose(file);
}
