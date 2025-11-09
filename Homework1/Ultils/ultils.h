#ifndef ULTILS_H
#define ULTILS_H

#include "../Book/book.h"
#include "../User/user.h"

#define MENU_LIST(X) \
    X(MENU_MAIN, "PROGRAM MANAGING THE LIBRARY",mainMenuItems) \
    X(MENU_BOOK, "BOOK MANAGEMENT MENU",bookMenuItems) \
    X(MENU_USER, "USER MANAGEMENT MENU",userMenuItems) \
    X(MENU_BORROW, "BORROW / RETURN MANAGEMENT MENU",borrowMenuItems) \
    X(MENU_SEARCH, "SEARCH & DISPLAYT MENU",searchMenuItems) \

typedef enum {
    #define DEFINE_ENUM(name, title, items) name,
    MENU_LIST(DEFINE_ENUM)
    MENU_LAST
    #undef DEFINE_ENUM
} MenuType_t;

/**
* @brief   Display all books in the library.
* @param   books  Array of Book_t structs representing the book database.
* @param   count  The current number of books.
* @return  void
*
* @details This function is used to display all books in the library.
*/
void displayBooks(Book_t books[], int count);

/**
 * @brief   Display all users in the library.
 * @param   users  Array of User_t structs representing the user database.
 * @param   count  The current number of users.
 * @return  void
 *
 * @details This function is used to display all users in the library.
 */
void displayUsers(User_t users[], int count);

/**
 * @brief   Display all borrowing books in the library.
 * @param   books  Array of Book_t structs representing the book database.
 * @param   count  The current number of books.
 * @return  BookRetCode_t  Error code defined in BookRetCode_t (e.g., BOOK_SUCCESS_ADD).
 *
 * @details This function is used to display all borrowing books in the library.
 */
BookRetCode_t displayBorrowingBooks(Book_t books[], int count);

/**
 * @brief   Display all users borrowing books.
 * @param   users  Array of User_t structs representing the user database.
 * @param   count  The current number of users.
 * @return  UserRetCode_t  Error code defined in UserRetCode_t (e.g., USER_SUCCESS_ADD).
 *
 * @details This function is used to display all users borrowing books.
 */
UserRetCode_t displayBorrowingUsers(User_t users[], int count);

/**
 * @brief   Search for a book in the library.
 * @param   books  Array of Book_t structs representing the book database.
 * @param   count  The current number of books.
 * @return  BookRetCode_t  Error code defined in BookRetCode_t (e.g., BOOK_SUCCESS_ADD).
 *
 * @details This function is used to search and display matching books in the library.
 */
BookRetCode_t searchBook(Book_t books[], int count);

/**
 * @brief   Search for a user in the library.
 * @param   users  Array of User_t structs representing the user database.
 * @param   count  The current number of users.
 * @return  UserRetCode_t  Error code defined in UserRetCode_t (e.g., USER_SUCCESS_ADD).
 *
 * @details This function is used to search and display matching users in the library.
 */
UserRetCode_t searchUser(User_t users[], int count);

/**
 * @brief   Display the menu based on the given menu type.
 * @param   type  Enum value defining which menu to display.
 * @return  void
 *
 * @details This function is used to display the menu based on the given menu type.
 */
void displayMenu(MenuType_t type);

#endif