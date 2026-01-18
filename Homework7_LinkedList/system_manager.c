#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 1. TASK QUEUE (Singly Linked List - SLL) ---
typedef struct TaskNode {
    char task_description[50];
    struct TaskNode* next;
} TaskNode_t;

static TaskNode_t *queue_head = NULL;
static TaskNode_t *queue_tail = NULL; // Dùng tail để thêm vào cuối O(1)

void queue_add_task(const char* description) {
    TaskNode_t* newNode = (TaskNode_t*)malloc(sizeof(TaskNode_t));
    if (!newNode) return;

    strncpy(newNode->task_description, description, 49);
    newNode->next = NULL;

    if (queue_tail == NULL) {
        queue_head = queue_tail = newNode;
    } else {
        queue_tail->next = newNode;
        queue_tail = newNode;
    }
    printf("[Queue] Added task: %s\n", description);
}

TaskNode_t* queue_get_next_task(void) {
    if (queue_head == NULL) return NULL;

    TaskNode_t* temp = queue_head;
    queue_head = queue_head->next;
    
    if (queue_head == NULL) queue_tail = NULL;
    
    return temp;
}

void print_task_queue(void) {
    printf("\n--- Current Task Queue ---\n");
    TaskNode_t* curr = queue_head;
    if (!curr) printf("Queue is empty.\n");
    while (curr) {
        printf("- %s\n", curr->task_description);
        curr = curr->next;
    }
    printf("--------------------------\n");
}

// --- 2. ACTIVITY LOG (Doubly Linked List - DLL) ---
typedef struct HistoryNode {
    char log_entry[50];
    struct HistoryNode* next;
    struct HistoryNode* prev;
} HistoryNode_t;

static HistoryNode_t* history_head = NULL;

void history_log_activity(const char* entry) {
    HistoryNode_t* newNode = (HistoryNode_t*)malloc(sizeof(HistoryNode_t));
    if (!newNode) return;

    strncpy(newNode->log_entry, entry, 49);
    newNode->next = history_head;
    newNode->prev = NULL;

    if (history_head != NULL) {
        history_head->prev = newNode;
    }
    history_head = newNode;
}

void history_navigate(void) {
    if (history_head == NULL) {
        printf("No history available.\n");
        return;
    }

    HistoryNode_t* current = history_head;
    char choice;
    
    printf("\n--- History Navigation (n: next, p: prev, q: quit) ---\n");
    while (1) {
        printf("LOG: [%s]\n", current->log_entry);
        printf("Command: ");
        scanf(" %c", &choice);

        if (choice == 'q') break;
        if (choice == 'n') {
            if (current->next) current = current->next;
            else printf(">> Reached oldest log.\n");
        } else if (choice == 'p') {
            if (current->prev) current = current->prev;
            else printf(">> Reached latest log.\n");
        }
    }
}

// --- 3. MAIN INTERFACE ---
int main() {
    char command[100];
    char desc[50];

    printf("System Controller Simulation\n");
    printf("Commands: add <desc>, run, list, history, exit\n");

    while (1) {
        printf("\n> ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf(" %[^\n]", desc);
            queue_add_task(desc);
        } 
        else if (strcmp(command, "run") == 0) {
            TaskNode_t* task = queue_get_next_task();
            if (task) {
                printf("Executing: %s\n", task->task_description);
                history_log_activity(task->task_description);
                free(task); // Giải phóng bộ nhớ sau khi xử lý
            } else {
                printf("No tasks to run.\n");
            }
        } 
        else if (strcmp(command, "list") == 0) {
            print_task_queue();
        } 
        else if (strcmp(command, "history") == 0) {
            history_navigate();
        } 
        else if (strcmp(command, "exit") == 0) {
            break;
        }
    }

    // Clean up memory before exit (Optional but good practice)
    return 0;
}