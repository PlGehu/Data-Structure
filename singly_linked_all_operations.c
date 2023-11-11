#include <stdio.h>
#include <stdlib.h>

// Define a structure for the linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

// Function to insert a node at the end of the list
struct Node* insertAtEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// Function to insert a node at a specific position in the list
struct Node* insertAtPosition(struct Node* head, int data, int position) {
    struct Node* newNode = createNode(data);
    if (position == 1) {
        newNode->next = head;
        return newNode;
    }
    struct Node* current = head;
    for (int i = 1; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Invalid position\n");
        return head;
    }
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Function to delete a node by value
struct Node* deleteByValue(struct Node* head, int value) {
    if (head == NULL) {
        return head;
    }
    if (head->data == value) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    struct Node* current = head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }
    if (current->next == NULL) {
        printf("Value not found in the list\n");
        return head;
    }
    struct Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    return head;
}

// Function to delete the first element
struct Node* deleteFirstElement(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return head;
    }
    struct Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

// Function to delete the last element
struct Node* deleteLastElement(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return head;
    }
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    struct Node* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    return head;
}

// Function to delete the middle element
struct Node* deleteMiddleElement(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        printf("List has too few elements to delete a middle element\n");
        return head;
    }

    struct Node* slow_ptr = head;
    struct Node* fast_ptr = head;
    struct Node* prev = NULL;

    while (fast_ptr != NULL && fast_ptr->next != NULL) {
        fast_ptr = fast_ptr->next->next;
        prev = slow_ptr;
        slow_ptr = slow_ptr->next;
    }

    if (prev != NULL) {
        prev->next = slow_ptr->next;
    } else {
        head = slow_ptr->next;
    }

    free(slow_ptr);
    return head;
}

// Function to search for a node by value
int search(struct Node* head, int value) {
    int position = 1;
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1; // Value not found
}

// Function to print the linked list
void display(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int choice, data, position, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at the beginning\n");
        printf("2. Insert at the end\n");
        printf("3. Insert at a specific position\n");
        printf("4. Delete by value\n");
        printf("5. Delete the first element\n");
        printf("6. Delete the last element\n");
        printf("7. Delete the middle element\n");
        printf("8. Search for a value\n");
        printf("9. Sort the list (not implemented)\n");
        printf("10. Display the list\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                head = insertAtBeginning(head, data);
                break;
            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                head = insertAtEnd(head, data);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &position);
                head = insertAtPosition(head, data, position);
                break;
            case 4:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                head = deleteByValue(head, value);
                break;
            case 5:
                head = deleteFirstElement(head);
                break;
            case 6:
                head = deleteLastElement(head);
                break;
            case 7:
                head = deleteMiddleElement(head);
                break;
            case 8:
                printf("Enter the value to search for: ");
                scanf("%d", &value);
                position = search(head, value);
                if (position == -1) {
                    printf("Value not found in the list\n");
                } else {
                    printf("Value found at position %d\n", position);
                }
                break;
            case 9:
                // Sorting the list (not implemented in this example)
                printf("Sorting the list (not implemented in this example)\n");
                break;
            case 10:
                printf("Linked List: ");
                display(head);
                break;
            case 11:
                printf("Exiting the program\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
