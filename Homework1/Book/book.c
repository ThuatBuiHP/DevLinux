#include <stdio.h>
#include <string.h>
#include "book.h"
#include "../User/user.h"

// Error messages array
static const char* const BOOK_ERROR_MESSAGES[] = {
#define X(code, msg) msg,
    BOOK_ERROR_LIST(X)
#undef X
};

BookRetCode_t addBook(Book_t books[], int *count) {
    if (*count >= MAX_BOOKS) {
        return BOOK_ADD_FAILED_FULL;
    }

    // Get book details from user
    printf("Enter book title: ");
    scanf(" %[^\n]s", books[*count].title);
    
    printf("Enter author name: ");
    scanf(" %[^\n]s", books[*count].author);
    
    // Set initial values
    books[*count].id = *count + 1;  // IDs start from 1
    books[*count].isBorrowed = 0;   // Not borrowed initially
    
    (*count)++;
    return BOOK_SUCCESS_ADD;
}

BookRetCode_t editBook(Book_t books[], int count) {
    int bookId;
    printf("Enter book ID to edit: ");
    scanf("%d", &bookId);

    // Find the book with the given ID
    for (int i = 0; i < count; i++) {
        if (books[i].id == bookId) {
            printf("Enter new title (or press enter to keep current): ");
            char newTitle[MAX_LENGTH_TITLE];
            getchar(); // Clear newline
            if (fgets(newTitle, MAX_LENGTH_TITLE, stdin) != NULL && newTitle[0] != '\n') {
                newTitle[strcspn(newTitle, "\n")] = 0; // Remove trailing newline
                strcpy(books[i].title, newTitle);
            }

            printf("Enter new author (or press enter to keep current): ");
            char newAuthor[AUTHOR_NAME_LENGTH];
            if (fgets(newAuthor, AUTHOR_NAME_LENGTH, stdin) != NULL && newAuthor[0] != '\n') {
                newAuthor[strcspn(newAuthor, "\n")] = 0; // Remove trailing newline
                strcpy(books[i].author, newAuthor);
            }

            return BOOK_SUCCESS_EDIT;
        }
    }

    return BOOK_EDIT_FAILED_NOT_FOUND;
}

BookRetCode_t deleteBook(Book_t books[], int *count) {
    int bookId;
    printf("Enter book ID to delete: ");
    scanf("%d", &bookId);

    for (int i = 0; i < *count; i++) {
        if (books[i].id == bookId) {
            // Check if book is currently borrowed
            if (books[i].isBorrowed) {
                return BOOK_DELETE_FAILED_BORROWING;
            }

            // Shift remaining books to fill the gap
            for (int j = i; j < *count - 1; j++) {
                books[j] = books[j + 1];
            }
            
            (*count)--;
            return BOOK_SUCCESS_DELETE;
        }
    }

    return BOOK_DELETE_FAILED_NOT_FOUND;
}

BookRetCode_t borrowOrReturnBook(Book_t books[], int countBook,
                                User_t users[], int countUser,
                                int isBorrowed) {
    int userId, bookId;
    
    printf("Enter user ID: ");
    scanf("%d", &userId);
    
    // Find user
    int userIndex = -1;
    for (int i = 0; i < countUser; i++) {
        if (users[i].id == userId) {
            userIndex = i;
            break;
        }
    }
    
    if (userIndex == -1) {
        return BOOK_BORROW_RETURN_FAILED_USER_NOT_FOUND;
    }

    printf("Enter book ID: ");
    scanf("%d", &bookId);

    // Find book
    int bookIndex = -1;
    for (int i = 0; i < countBook; i++) {
        if (books[i].id == bookId) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
        return BOOK_BORROW_RETURN_FAILED_BOOK_NOT_FOUND;
    }

    if (isBorrowed == BORROWED_BOOK) {
        // Check if book is already borrowed
        if (books[bookIndex].isBorrowed) {
            return BOOK_BORROW_RETURN_FAILED_BOOK_HAS_BEEN_BORROWED;
        }
        
        // Check if user has reached borrowing limit
        int borrowedCount = 0;
        for (int i = 0; i < countBook; i++) {
            if (books[i].isBorrowed && books[i].isBorrowed == userId) {
                borrowedCount++;
            }
        }
        
        if (borrowedCount >= MAX_BORROWED_BOOKS) {
            return BOOK_BORROW_FAILED_LIMITED;
        }

        // Borrow the book
        books[bookIndex].isBorrowed = userId;  // Store user ID in isBorrowed
        return BOOK_BORROW_OK;
    } 
    else if (isBorrowed == RETURN_BOOK) {
        // Check if book is borrowed by this user
        if (books[bookIndex].isBorrowed != userId) {
            return BOOK_BORROW_RETURN_FAILED_BOOK_HAS_BEEN_BORROWED;
        }

        // Return the book
        books[bookIndex].isBorrowed = 0;
        return BOOK_RETURN_OK;
    }

    return BOOK_BORROW_RETURN_FAILED_UNKNOWN;
}

void bookRetCodeToString(BookRetCode_t code) {
    if (code >= 0 && code < BOOK_ERROR_COUNT) {
        printf("%s\n", BOOK_ERROR_MESSAGES[code]);
    } else {
        printf("Unknown error code\n");
    }
}
