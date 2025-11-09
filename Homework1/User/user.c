/*
 * User management implementation
 */
#include <stdio.h>
#include <string.h>
#include "user.h"

static const char* const USER_ERROR_MESSAGES[] = {
#define X(code, msg) msg,
	USER_ERROR_LIST(X)
#undef X
};

UserRetCode_t addUser(User_t users[], int *count)
{
	if (*count >= MAX_USERS) {
		return USER_ADD_FAILED_FULL;
	}

	printf("Enter user name: ");
	// read line
	if (fgets(users[*count].name, NAME_LENGTH, stdin) == NULL) {
		return USER_ADD_FAILED_FULL; // treat as failure
	}
	// Remove newline character from the end of the string
	users[*count].name[strcspn(users[*count].name, "\n")] = '\0';

	users[*count].id = *count + 1;
	users[*count].borrowedBooksCount = 0;
	// initialize borrowed books list
	for (int i = 0; i < MAX_BORROWED_BOOKS; i++) {
		users[*count].borrowedBooks[i] = 0;
	}

	(*count)++;
	return USER_SUCCESS_ADD;
}

UserRetCode_t editUser(User_t users[], int *count)
{
	int id;
	printf("Enter user ID to edit: ");
	if (scanf("%d", &id) != 1) {
		// consume rest of line
		int c; while ((c = getchar()) != '\n' && c != EOF);
		return USER_EDIT_GAILED_NOT_FOUND;
	}
	// consume newline
	int c; while ((c = getchar()) != '\n' && c != EOF);

	for (int i = 0; i < *count; i++) {
		if (users[i].id == id) {
			printf("Enter new name (or press Enter to keep current): ");
			char buf[NAME_LENGTH];
			if (fgets(buf, NAME_LENGTH, stdin) != NULL) {
				if (buf[0] != '\n') {
                    // Remove newline character from the end of the string
					buf[strcspn(buf, "\n")] = '\0';
                    // Copy the string to the user struct
					strncpy(users[i].name, buf, NAME_LENGTH - 1);
				}
			}
			return USER_SUCCESS_EDIT;
		}
	}

	return USER_EDIT_GAILED_NOT_FOUND;
}

UserRetCode_t deleteUser(User_t users[], int *count)
{
	int id;
	printf("Enter user ID to delete: ");
	if (scanf("%d", &id) != 1) {
		int c; while ((c = getchar()) != '\n' && c != EOF);
		return USER_DELETE_FAILED_NOT_FOUND;
	}
	int c; while ((c = getchar()) != '\n' && c != EOF);

	for (int i = 0; i < *count; i++) {
		if (users[i].id == id) {
			if (users[i].borrowedBooksCount > 0) {
				return USER_DELETE_FAILED_BORROWING;
			}
			// shift left
			for (int j = i; j < *count - 1; j++) {
				users[j] = users[j + 1];
			}
			(*count)--;
			return USER_SUCCESS_DELETE;
		}
	}

	return USER_DELETE_FAILED_NOT_FOUND;
}

void userRetCodeToString(UserRetCode_t code)
{
	if (code >= 0 && code < USER_ERROR_COUNT) {
		printf("%s\n", USER_ERROR_MESSAGES[code]);
	} else {
		printf("Unknown user error code\n");
	}
}
