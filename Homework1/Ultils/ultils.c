#include <stdio.h>
#include <string.h>
#include "ultils.h"

// Define menu items for each menu type
static const char* mainMenuItems[] = {
    "B Book Management",
    "U User Management",
    "P Borrow/Return Management",
    "S Search & Display",
    "E Exit",
    NULL
};

static const char* bookMenuItems[] = {
    "A Add Book",
    "E Edit Book",
    "D Delete Book",
    "S Display All Books",
    NULL
};

static const char* userMenuItems[] = {
    "A Add User",
    "E Edit User",
    "D Delete User",
    "S Display All Users",
    NULL
};

static const char* borrowMenuItems[] = {
    "B Borrow Book",
    "R Return Book",
    NULL
};

static const char* searchMenuItems[] = {
    "1. Search Book",
    "2. Display borrowing books",
    "3. Search User",
    "4. Display borrowing users",
    NULL
};

// Menu titles array
static const char* const MENU_TITLES[] = {
#define X(name, title, items) title,
    MENU_LIST(X)
#undef X
};

// Menu items array
static const char* const* MENU_ITEMS[] = {
    mainMenuItems,
    bookMenuItems,
    userMenuItems,
    borrowMenuItems,
    searchMenuItems
};

void displayBooks(Book_t books[], int count) {
    if (count == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\n%-5s %-30s %-30s %-15s\n", "ID", "Title", "Author", "Status");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-30s %-30s %-15s\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].isBorrowed ? "Borrowed" : "Available");
    }
    printf("\n");
}

void displayUsers(User_t users[], int count) {
    if (count == 0) {
        printf("No users registered in the library.\n");
        return;
    }

    printf("\n%-5s %-30s %-20s\n", "ID", "Name", "Books Borrowed");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-30s %-20d\n",
               users[i].id,
               users[i].name,
               users[i].borrowedBooksCount);
    }
    printf("\n");
}

BookRetCode_t displayBorrowingBooks(Book_t books[], int count) {
    int foundBorrowed = 0;
    
    printf("\n%-5s %-30s %-30s %-15s\n", "ID", "Title", "Author", "Borrowed By");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        if (books[i].isBorrowed) {
            printf("%-5d %-30s %-30s User ID: %-5d\n",
                   books[i].id,
                   books[i].title,
                   books[i].author,
                   books[i].isBorrowed);
            foundBorrowed = 1;
        }
    }
    
    if (!foundBorrowed) {
        return BOOK_BORROWING_NOT_FOUND;
    }
    
    return BOOK_BORROWING_SHOW_OK;
}

UserRetCode_t displayBorrowingUsers(User_t users[], int count) {
    int foundBorrowing = 0;
    
    printf("\n%-5s %-30s %-20s\n", "ID", "Name", "Borrowed Books");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        if (users[i].borrowedBooksCount > 0) {
            printf("%-5d %-30s %d\n",
                   users[i].id,
                   users[i].name,
                   users[i].borrowedBooksCount);
            
            printf("    Borrowed Book IDs: ");
            for (int j = 0; j < users[i].borrowedBooksCount; j++) {
                printf("%d ", users[i].borrowedBooks[j]);
            }
            printf("\n");
            foundBorrowing = 1;
        }
    }
    
    if (!foundBorrowing) {
        return USER_BORROWING_NOT_FOUND;
    }
    
    return USER_BORROWING_SHOW_OK;
}

BookRetCode_t searchBook(Book_t books[], int count) {
    char searchTerm[MAX_LENGTH_TITLE];
    int found = 0;
    
    printf("Enter book title or author to search: ");
    scanf(" %[^\n]", searchTerm);
    
    printf("\n%-5s %-30s %-30s %-15s\n", "ID", "Title", "Author", "Status");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        if (strstr(books[i].title, searchTerm) != NULL || 
            strstr(books[i].author, searchTerm) != NULL) {
            printf("%-5d %-30s %-30s %-15s\n",
                   books[i].id,
                   books[i].title,
                   books[i].author,
                   books[i].isBorrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }
    
    if (!found) {
        return BOOK_SEARCH_NOT_FOUND;
    }
    
    return BOOK_SEARCH_SUCCESS;
}

UserRetCode_t searchUser(User_t users[], int count) {
    char searchTerm[NAME_LENGTH];
    int found = 0;
    
    printf("Enter user name to search: ");
    scanf(" %[^\n]", searchTerm);
    
    printf("\n%-5s %-30s %-20s\n", "ID", "Name", "Books Borrowed");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        if (strstr(users[i].name, searchTerm) != NULL) {
            printf("%-5d %-30s %-20d\n",
                   users[i].id,
                   users[i].name,
                   users[i].borrowedBooksCount);
                   
            if (users[i].borrowedBooksCount > 0) {
                printf("    Borrowed Book IDs: ");
                for (int j = 0; j < users[i].borrowedBooksCount; j++) {
                    printf("%d ", users[i].borrowedBooks[j]);
                }
                printf("\n");
            }
            found = 1;
        }
    }
    
    if (!found) {
        return USER_SEARCH_NOT_FOUND;
    }
    
    return USER_SEARCH_SUCCESS;
}

void displayMenu(MenuType_t type) {
    if (type >= MENU_LAST) {
        printf("Invalid menu type\n");
        return;
    }
    
    // Display menu title
    printf("\n=== %s ===\n", MENU_TITLES[type]);
    
    // Display menu items
    const char* const* items = MENU_ITEMS[type];
    for (int i = 0; items[i] != NULL; i++) {
        printf("%s\n", items[i]);
    }
    
    
}

/*
 * The management module expects functions named showBooks/showUsers/
 * showBorrowingBooks/showBorrowingUsers. Provide thin wrappers that
 * call the display* implementations declared in ultils.h so existing
 * management.c can link correctly.
 */
void showBooks(Book_t books[], int count)
{
    displayBooks(books, count);
}

void showUsers(User_t users[], int count)
{
    displayUsers(users, count);
}

BookRetCode_t showBorrowingBooks(Book_t books[], int count)
{
    return displayBorrowingBooks(books, count);
}

UserRetCode_t showBorrowingUsers(User_t users[], int count)
{
    return displayBorrowingUsers(users, count);
}
