#ifndef BOOK_H
#define BOOK_H

#include "../User/user.h"

#define MAX_BOOKS 100
#define MAX_LENGTH_TITLE MAX_BOOKS
#define AUTHOR_NAME_LENGTH MAX_BOOKS
#define BORROWED_BOOK 1
#define RETURN_BOOK 2
#define BOOK_ERROR_LIST(X) \
    X(BOOK_SUCCESS_ADD, "Book added successfully.") \
    X(BOOK_ADD_FAILED_FULL, "ERROR: Cannot add new book - library book list is full.") \
    X(BOOK_EDIT_FAILED_NOT_FOUND, "ERROR: Cannot edit book - book not found in library.") \
    X(BOOK_SUCCESS_EDIT, "Book edited successfully.") \
    X(BOOK_DELETE_FAILED_NOT_FOUND, "ERROR: Cannot delete book - book not found in library.") \
    X(BOOK_DELETE_FAILED_BORROWING, "ERROR: Cannot delete book - book is currently borrowed.") \
    X(BOOK_SUCCESS_DELETE, "Book deleted successfully.") \
    X(BOOK_BORROW_RETURN_FAILED_USER_NOT_FOUND, "ERROR: Cannot borrow or return book - user not found in library.") \
    X(BOOK_BORROW_RETURN_FAILED_BOOK_NOT_FOUND, "ERROR: Cannot borrow or return book - book not found in library.") \
    X(BOOK_BORROW_RETURN_FAILED_BOOK_HAS_BEEN_BORROWED, "ERROR: Cannot borrow or return book - book is not currently borrowed.") \
    X(BOOK_BORROW_FAILED_LIMITED, "ERROR: Cannot borrow book - Borrowed books limit reached.") \
    X(BOOK_BORROW_OK, "Borrow book successfully.") \
    X(BOOK_BORROW_RETURN_FAILED_UNKNOWN, "ERROR: Cannot borrow or return book - unknown error.") \
    X(BOOK_RETURN_OK, "Return book successfully.") \
    X(BOOK_SEARCH_NOT_FOUND, "ERROR: Cannot find book - book not found in library.") \
    X(BOOK_SEARCH_SUCCESS, "Book found successfully.") \
    X(BOOK_BORROWING_NOT_FOUND, "ERROR: There is no book borrowed.") \
    X(BOOK_BORROWING_SHOW_OK, "")

typedef enum {
#define X(code, msg) code,
    BOOK_ERROR_LIST(X)
#undef X
    BOOK_ERROR_COUNT
} BookRetCode_t;

typedef struct {
    int id;
    char title[MAX_LENGTH_TITLE];
    char author[AUTHOR_NAME_LENGTH];
    int isBorrowed;
} Book_t;

/**
 * @brief   Add a new book to the library.
 * @param   books   Array of Book_t structs representing the book database.
 * @param   count   Pointer to the current number of books (incremented after successful addition).
 * @return  BookRetCode_t  Error code defined in BookRetCode_t (e.g., BOOK_SUCCESS_ADD).
 *
 * @details This function is used to add a new book to the library.
 *          Return BOOK_SUCCESS_ADD on success, or BOOK_ADD_FAILED_FULL if the library is full.
 */
BookRetCode_t addBook(Book_t books[], int *count);

/**
 * @brief   Edit the information of an existing book.
 * @param   books  Array of Book_t structs representing the book database.
 * @param   count  The current number of books (incremented after successful addition).
 * @return  BookRetCode_t  Error code defined in BookRetCode_t (e.g., BOOK_SUCCESS_EDIT).
 *
 * @details This function modifies the information of an existing book.
 *          Return BOOK_SUCCESS_EDIT on success, or BOOK_EDIT_FAILED_NOT_FOUND if the book is not found.
 */
BookRetCode_t editBook(Book_t books[], int count);

/**
 * @brief   Delete an existing book from the library.
 * @param   books   Array of Book_t structs representing the book database.
 * @param   count   Pointer to the current number of books (decremented after successful deletion).
 * @return  BookRetCode_t  Error code defined in BookRetCode_t (e.g., BOOK_SUCCESS_DELETE).
 *
 * @details This function deletes an existing book from the library.
 *          Return BOOK_SUCCESS_DELETE on success, 
 *          or BOOK_DELETE_FAILED_NOT_FOUND if the book is not found,
 *          or BOOK_DELETE_FAILED_BORROWING if the book is currently borrowed.
 */
BookRetCode_t deleteBook(Book_t books[], int *count);

/**
  * @brief   Handle borrowing and returning of a book.
  * @param   books  Array of Book_t structs representing the book database.
  * @param   countBook  The current number of books.
  * @param   users  Array of User_t structs representing the user database.
  * @param   countUser  The current number of users.
  * @param   isBorrowed  1 for borrow, 0 for return.
  * @return  BookRetCode_t  Error code defined in BookRetCode_t (e.g., BOOK_SUCCESS_ADD).
  *
  * @details This function is used to borrow or return a book.
  *          Return BOOK_BORROW_OK on success, 
  *          or BOOK_BORROW_RETURN_FAILED_UNKNOWN if the book is not found,
  *          or BOOK_BORROW_RETURN_FAILED_BOOK_HAS_BEEN_BORROWED if the book is currently borrowed,
  *          or BOOK_BORROW_FAILED_LIMITED if the borrowed books limit is reached.
  */
BookRetCode_t borrowOrReturnBook(Book_t books[], int countBook,
                                   User_t users[], int countUser,
                                   int isBorrowed);

/**
 * @brief   Return a descriptive error message for a given book-related error code.
 * @param   code    Error code defined in BookRetCode_t (e.g., BOOK_SUCCESS_ADD).
 * @return  void.
 *
 * @details This function is used to return a descriptive error message for a given book-related error code.
 */
void bookRetCodeToString(BookRetCode_t code);

#endif
