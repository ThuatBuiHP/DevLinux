#ifndef USER_H
#define USER_H

#define MAX_USERS 50
#define NAME_LENGTH 100
#define MAX_BORROWED_BOOKS 10
#define USER_ERROR_LIST(X) \
    X(USER_SUCCESS_ADD, "User added successfully.") \
    X(USER_ADD_FAILED_FULL, "ERROR: Cannot add new user - library user list is full.") \
    X(USER_EDIT_GAILED_NOT_FOUND, "ERROR: Cannot edit user - user not found in library.") \
    X(USER_SUCCESS_EDIT, "User edited successfully.") \
    X(USER_DELETE_FAILED_NOT_FOUND, "ERROR: Cannot delete user - user not found in library.") \
    X(USER_DELETE_FAILED_BORROWING, "ERROR: Cannot delete user - user is currently borrowing a book.") \
    X(USER_SUCCESS_DELETE, "User deleted successfully.") \
    X(USER_SEARCH_NOT_FOUND, "ERROR: Cannot find user - user not found in library.") \
    X(USER_SEARCH_SUCCESS, "User found successfully.") \
    X(USER_BORROWING_NOT_FOUND, "ERROR: There is no user borrowing book.") \
    X(USER_BORROWING_SHOW_OK, "")

typedef enum {
#define X(code, msg) code,
    USER_ERROR_LIST(X)
#undef X
    USER_ERROR_COUNT
} UserRetCode_t;

typedef struct {
    int id;
    char name[NAME_LENGTH];
    int borrowedBooks[MAX_BORROWED_BOOKS];
    int borrowedBooksCount;
} User_t;

/**
 * @brief   Add a new user to the library.
 * @param   users   Array of User_t structs representing the user database.
 * @param   count   Pointer to the current number of users (incremented after successful addition).
 * @return  int    Error code defined in UserRetCode_t (e.g., USER_SUCCESS_ADD).
 */
UserRetCode_t addUser(User_t users[], int *count);

/**
  * @brief   Edit the information of an existing user.
  * @param   users  Array of User_t structs representing the user database.
  * @param   count  Pointer to the current number of users.
  * @return  int    Error code defined in UserRetCode_t (e.g., USER_SUCCESS_EDIT).
  */
UserRetCode_t editUser(User_t users[], int *count);

/**
 * @brief   Delete an existing user from the library.
 * @param   users   Array of User_t structs representing the user database.
 * @param   count   Pointer to the current number of users (decremented after successful deletion).
 * @return  int     Error code defined in UserRetCode_t (e.g., USER_SUCCESS_DELETE).
 */
UserRetCode_t deleteUser(User_t users[], int *count);

/**
 * @brief   Return a descriptive error message for a given user-related error code.
 * @param   code    Error code defined in UserRetCode_t (e.g., USER_SUCCESS_ADD).
 * @return  void.
 */
void userRetCodeToString(UserRetCode_t code);

#endif