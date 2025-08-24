#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int studentID;
    int bookID;
    char title[50];
    char issueDate[15];
    struct Book *next;
} Book;

Book *head = NULL;

Book* createNode(int sid, int bid, char *title, char *date) {
    Book newNode = (Book) malloc(sizeof(Book));
    newNode->studentID = sid;
    newNode->bookID = bid;
    strcpy(newNode->title, title);
    strcpy(newNode->issueDate, date);
    newNode->next = NULL;
    return newNode;
}

void issueBook(int sid, int bid, char *title, char *date) {
    Book *newNode = createNode(sid, bid, title, date);
    if (head == NULL) {
        head = newNode;
    } else {
        Book *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    printf("Book issued successfully.\n");
}

void returnBook(int sid, int bid) {
    if (head == NULL) {
        printf("No records available.\n");
        return;
    }
    Book *temp = head, *prev = NULL;
    while (temp != NULL) {
        if (temp->studentID == sid && temp->bookID == bid) {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;
            free(temp);
            printf("Book returned successfully.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Book record not found.\n");
}

void searchByStudent(int sid) {
    Book *temp = head;
    int found = 0;
    while (temp != NULL) {
        if (temp->studentID == sid) {
            printf("\nStudent ID: %d | Book ID: %d | Title: %s | Date: %s\n",
                   temp->studentID, temp->bookID, temp->title, temp->issueDate);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("No books borrowed by Student ID %d.\n", sid);
}

void displayAll() {
    if (head == NULL) {
        printf("No borrowing records available.\n");
        return;
    }
    Book *temp = head;
    printf("\n===== Borrowing Records =====\n");
    while (temp != NULL) {
        printf("Student ID: %d | Book ID: %d | Title: %s | Date: %s\n",
               temp->studentID, temp->bookID, temp->title, temp->issueDate);
        temp = temp->next;
    }
    printf("=============================\n");
}

void countBooks() {
    int count = 0;
    Book *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Total borrowed books: %d\n", count);
}

int main() {
    int choice, sid, bid;
    char title[50], date[15];

    while (1) {
        printf("\n--- Library Book Borrowing System ---\n");
        printf("1. Issue Book\n");
        printf("2. Return Book\n");
        printf("3. Search by Student ID\n");
        printf("4. Display All Records\n");
        printf("5. Count Borrowed Books\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &sid);
                printf("Enter Book ID: ");
                scanf("%d", &bid);
                getchar();
                printf("Enter Book Title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Enter Issue Date (dd-mm-yyyy): ");
                scanf("%s", date);
                issueBook(sid, bid, title, date);
                break;
            case 2:
                printf("Enter Student ID: ");
                scanf("%d", &sid);
                printf("Enter Book ID: ");
                scanf("%d", &bid);
                returnBook(sid, bid);
                break;
            case 3:
                printf("Enter Student ID: ");
                scanf("%d", &sid);
                searchByStudent(sid);
                break;
            case 4:
                displayAll();
                break;
            case 5:
                countBooks();
                break;
            case 6:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
