#include "management.h"
#include "../Ultils/ultils.h"
#include "../Book/book.h"
#include "../User/user.h"
#include "../Ultils/ultils.c"
#include "../Book/book.c"
#include "../User/user.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*==================== Static Data ====================*/
static Book_t s_books[MAX_BOOKS];
static int s_booksCount = 0;
static User_t s_users[MAX_USERS];
static int s_usersCount = 0;
static char s_choice[10];
static int s_retCode;

/*==================== HelperFunctions ====================*/
static bool isMenuInputValid(const char *input)
{
    int len = strlen(input);
    return (len == 2 && input[1] == '\n') ||
           (len == 3 && input[1] == '\r' && input[2] == '\n');
}

/**
 * @brief   Reads and validates user input.
 * @param   menuType Menu type to redisplay on error.
 * @return  True if the input is valid, false otherwise.
 */
static bool readMenuChoice(MenuType_t menuType)
{
    memset(s_choice, 0, sizeof(s_choice));
    printf("\n\n");
    printf("Please enter your choice: ");
    fflush(stdout);
    if (fgets(s_choice, sizeof(s_choice), stdin) == NULL) {
        displayMenu(menuType);
        return false;
    }

    if (!isMenuInputValid(s_choice)) {
        displayMenu(menuType);
        return false;
    }

    return true;
}

/**
 * @brief   Generic function to handle user input and loop.
 * @param   menuType Menu type to display.
 * @param   exitKey  Key to exit the loop.
 * @param   handler  Callback function to handle user input.
 */
static void runMenu(MenuType_t menuType, char exitKey, void (*handler)(char))
{
    system("clear");
    displayMenu(menuType);
    do
    {
        if (!readMenuChoice(menuType)) 
        {
            continue;
        }

        if (s_choice[0] == exitKey) {
            break;
        }

        handler(s_choice[0]);
    } while (true);
    system("clear");
    displayMenu(MENU_MAIN);
}

/*==================== Menu Handlers ====================*/
static void handleBookChoice(char choice)
{
    switch (choice) 
    {
        case 'A':
        case 'a':
            s_retCode = addBook(s_books, &s_booksCount);
            bookRetCodeToString((BookRetCode_t)s_retCode);
            break;
        case 'E':
        case 'e':
            s_retCode = editBook(s_books, s_booksCount);
            bookRetCodeToString((BookRetCode_t)s_retCode);
            break;
        case 'D':
        case 'd':
            s_retCode = deleteBook(s_books, &s_booksCount);
            bookRetCodeToString((BookRetCode_t)s_retCode);
            break;
        case 'S':
        case 's':
            showBooks(s_books, s_booksCount);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}
static void handleUserChoice(char choice)
{
    switch (choice) 
    {
        case 'A':
        case 'a':
            s_retCode = addUser(s_users, &s_usersCount);
            userRetCodeToString((UserRetCode_t)s_retCode);
            break;
        case 'E':
        case 'e':
            s_retCode = editUser(s_users, &s_usersCount);
            userRetCodeToString((UserRetCode_t)s_retCode);
            break;
        case 'D':
        case 'd':
            s_retCode = deleteUser(s_users, &s_usersCount);
            userRetCodeToString((UserRetCode_t)s_retCode);
            break;
        case 'S':
        case 's':
            showUsers(s_users, s_usersCount);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

static void handleBorrowChoice(char choice)
{
    switch (choice) 
    {
        case 'B':
        case 'b':
            s_retCode = borrowOrReturnBook(s_books, s_booksCount,
                                           s_users, s_usersCount,
                                           BORROWED_BOOK);
            bookRetCodeToString((BookRetCode_t)s_retCode);
            break;
        case 'R':
        case 'r':
            s_retCode = borrowOrReturnBook(s_books, s_booksCount,
                                           s_users, s_usersCount,
                                           RETURN_BOOK);
            bookRetCodeToString((BookRetCode_t)s_retCode);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

static void handleSearchChoice(char choice)
{
    switch (choice) 
    {
        case '1':
            s_retCode = searchBook(s_books, s_booksCount);
            bookRetCodeToString((BookRetCode_t)s_retCode);
            break;
        case '2':
            s_retCode = displayBorrowingBooks(s_books, s_booksCount);
            bookRetCodeToString((BookRetCode_t)s_retCode);
            break;
        case '3':
            s_retCode = searchUser(s_users, s_usersCount);
            userRetCodeToString((UserRetCode_t)s_retCode);
            break;
        case '4':
            s_retCode = displayBorrowingUsers(s_users, s_usersCount);
            userRetCodeToString((UserRetCode_t)s_retCode);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

/*==================== Main Menu ====================*/
void manageLibrary()
{
    displayMenu(MENU_MAIN);
    do
    {
        if (!readMenuChoice(MENU_MAIN)) 
        {
            continue;
        }

        switch (s_choice[0]) 
        {
            case 'B':
            case 'b':
                runMenu(MENU_BOOK, 'M', handleBookChoice);
                break;
            case 'U':
            case 'u':
                runMenu(MENU_USER, 'M', handleUserChoice);
                break;
            case 'P':
            case 'p':
                runMenu(MENU_BORROW, 'M', handleBorrowChoice);
                break;
            case 'S':
            case 's':
                runMenu(MENU_SEARCH, 'M', handleSearchChoice);
                break;
            case 'E':
            case 'e':
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }while (true);
}