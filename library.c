#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//some global variable's
#define MAX_BOOKS 100
#define MAX_STUDENTS 50
#define STUDENT_ID_LENGTH 14 // this is used also for the book ID 
#define TITLE_LENGTH 200
#define AUTHOR_LENGTH 20
#define NAME_LENGTH 50
#define DESCRIPTION_LENGTH 200
#define FACULTY_LENGTH 100
#define FILENAME_BOOKS "books.txt"
#define FILENAME_STUDENTS "students.txt"

// Structure of book's
struct Book {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    char description[DESCRIPTION_LENGTH];
    char id[STUDENT_ID_LENGTH];
    int available;
    int times_borrowed;
};

// Structure of student's
struct Student {
    char name[NAME_LENGTH];
    char mbiemri[NAME_LENGTH];
    char id[STUDENT_ID_LENGTH];
    int numBooksBorrowed;
    char bookIds[MAX_BOOKS][STUDENT_ID_LENGTH]; //matrix that saves book's with id
    char faculty[FACULTY_LENGTH];
};
//structure of borrowed book's
struct BorrowedBook {
    char bookId[STUDENT_ID_LENGTH];
    char studentId[STUDENT_ID_LENGTH];
    int date;
    int month;
    int year;
};

// All the function's
void addBook(struct Book books[], int *numBooks);
void saveBooks(struct Book books[], int numBooks);
void loadBooks(struct Book books[], int *numBooks);
void removeBook(struct Book books[], int *numBooks);
void displayBooks(struct Book books[], int numBooks);
void searchBookByID(struct Book books[], int numBooks);
void borrowBook(struct Book books[], int numBooks, struct Student students[], int *numStudents, struct BorrowedBook borrowedBooks[], int *numBorrowedBooks);
void returnBook(struct Book books[], int numBooks, struct Student students[], int numStudents, struct BorrowedBook borrowedBooks[], int numBorrowedBooks);
void mostReadBooks(struct Book books[], int numBooks);
void mostReadStudents(struct Student students[], int numStudents);
void saveStudents(struct Student students[], int numStudents);
void loadStudents(struct Student students[], int *numStudents);
void registerStudent(struct Student students[], int *numStudents);
void displayStudents(struct Student students[], int numStudents);
void displayBookDescription(struct Book books[], int numBooks);

// main function
int main() {
    struct Book books[MAX_BOOKS];
    int numBooks = 0;
    struct Student students[MAX_STUDENTS];
    int numStudents = 0;
     struct BorrowedBook borrowedBooks[MAX_BOOKS];
    int numBorrowedBooks = 0;
    int choice;

    loadBooks(books, &numBooks);
    loadStudents(students, &numStudents);
//"the menu"
    do {
        printf("\nWelcome to the library\n");
        printf("1.Add a book\n");
        printf("2.Remove a book\n");
        printf("3.All the books \n");
        printf("4.Search a book with its ID\n");
        printf("5.Borrow a book\n");
        printf("6.Return a book\n");
        printf("7.Most read books\n");
        printf("8.Students who read the most\n");
        printf("9.Add a student\n");
        printf("10.All the student's\n");
        printf("11.Search the book description\n");
        printf("12.Exit\n");
        printf("Press one of the above numbers:");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addBook(books, &numBooks);
                break;
            case 2:
                removeBook(books, &numBooks);
                break;
            case 3:
                displayBooks(books, numBooks);
                break;
            case 4:
                searchBookByID(books, numBooks);
                break;
            case 5:
                borrowBook(books, numBooks, students, &numStudents, borrowedBooks, &numBorrowedBooks);
                break;
            case 6:
                  returnBook(books, numBooks, students, numStudents, borrowedBooks, numBorrowedBooks);
                break;
            case 7:
                mostReadBooks(books, numBooks);
                break;
            case 8:
                mostReadStudents(students, numStudents);
                break;
            case 9:
                registerStudent(students, &numStudents);
                break;
            case 10:
                displayStudents(students, numStudents);
                break;
            case 11:
                displayBookDescription(books, numBooks);
                break;
            case 12:
                printf("Exiting...\n");
                break;
            default:
                printf("Wrong choice, only a number from 1-12!\n");
        }
    } while(choice != 12);

    saveBooks(books, numBooks);
    saveStudents(students, numStudents);

    return 0;
}

// add book function
void addBook(struct Book books[], int *numBooks) {
    if (*numBooks <= MAX_BOOKS) {
        printf("Put the book title: ");
        scanf("%s", books[*numBooks].title);
        printf("Author of the book: ");
        scanf("%s", books[*numBooks].author);
        printf("Book description: ");
        scanf(" %[^\n]s", books[*numBooks].description); // [^] read  space in the words

        //first enter the ID, we check is it has 13 character's than we see if it's unique
        int idExists;
        do {
            printf("Enter the book ID (13 char): ");
            scanf("%s", books[*numBooks].id);
            idExists = 0;
            if (strlen(books[*numBooks].id) != STUDENT_ID_LENGTH - 1) {
                printf("ID must be 13 char.Put the correct ID!\n");
                idExists = 1; 
            } 
            else {
                for (int i = 0; i < *numBooks; i++) {
                    if (strcmp(books[i].id, books[*numBooks].id) == 0) {
                        idExists = 1;
                        printf("This ID exist.Pleas put another ID!\n");
                        break;
                    }
                }
            }
        } while (idExists);
// Increment book count and set times_borrowed to 0 since the book is new

        books[*numBooks].available = 1;
        books[*numBooks].times_borrowed = 0;
        (*numBooks)++;
        printf("Book add successfully!\n");
    //check if the library is full
    } else {
        printf("Library is full.You cant add more books!\n");
    }
}
//we save the books in the books file
void saveBooks(struct Book books[], int numBooks) {
    FILE *file = fopen(FILENAME_BOOKS, "w");
    if (file == NULL) {
        printf("Error in the proces of opening the folder of the books.\n");
        return;
    }
    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%s, %s, %s, %s, %d, %d\n", books[i].title, books[i].author, books[i].description, books[i].id, books[i].available, books[i].times_borrowed);
    }
    fclose(file);
}
// we load books from the books file and if it does not exist we create one in the same directory as our main programm
void loadBooks(struct Book books[], int *numBooks) {
    FILE *file = fopen(FILENAME_BOOKS, "r");
    if (file == NULL) {
        printf("Book file does not exist.Creating a new file...\n");
        file = fopen(FILENAME_BOOKS, "w");
        if (file == NULL) {
            printf("Error in creating a file for books!\n");
            return;
        }
        fclose(file);
        *numBooks = 0; 
        return;
    }
    *numBooks = 0;
    while (*numBooks <= MAX_BOOKS && fscanf(file, " %49[^,], %49[^,], %199[^,], %13s, %d, %d", books[*numBooks].title, books[*numBooks].author, books[*numBooks].description, books[*numBooks].id, &books[*numBooks].available, &books[*numBooks].times_borrowed) == 6) {
        (*numBooks)++;
    }
    fclose(file);
}
//remove a book function
void removeBook(struct Book books[], int *numBooks) {
    char bookId[STUDENT_ID_LENGTH];
    printf("Enter the ID of the book you want to delete: ");
    scanf("%s", bookId);
    int found = 0;
    for (int i = 0; i < *numBooks; i++) {
        if (strcmp(books[i].id, bookId) == 0) {
            for (int j = i; j < *numBooks - 1; j++) {
                books[j] = books[j + 1]; 
            }
            (*numBooks)--;
            found = 1;
            printf("Book deleted successfully..\n");
            break;
        }
    }
    if (!found) {
        printf("Book not found!\n");
    }
}
//display all the books that are in the library
void displayBooks(struct Book books[], int numBooks) {
    //check if the numBooks variable is grater then 0
    if (numBooks>0){
    printf("\nBooks in the library:\n");
    for (int i = 0; i < numBooks; i++) {
            printf("ID: %s, Title: %s, Author: %s, Available: %s, Is read: %d\n",books[i].id, books[i].title, books[i].author, books[i].available ? "Yes" : "No", books[i].times_borrowed);
    }}
    // if numBooks is 0 or less(not possiblem but its nice to include it)
    else  {
        printf("No books in the library!\n");}
    
}
// search book by id
void searchBookByID(struct Book books[], int numBooks) {
    char id[STUDENT_ID_LENGTH];
    printf("Enter the ID of book you are searching: ");
    scanf("%s", id);
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].id, id) == 0) {
            printf("Book found:\n");
            printf("Title: %s, Author: %s, Availabel: %s, Is read: %d\n",
                books[i].title, books[i].author, books[i].available ? "Yes" : "No", books[i].times_borrowed);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
}
// borrow a book function
void borrowBook(struct Book books[], int numBooks, struct Student students[], int *numStudents, struct BorrowedBook borrowedBooks[], int *numBorrowedBooks) {  
// check the studen first
    char studentId[STUDENT_ID_LENGTH];
    printf("Enter your ID: ");
    scanf("%s", studentId);

    int studentIndex = -1;
    for (int i = 0; i < *numStudents; i++) {
        if (strcmp(students[i].id, studentId) == 0) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex == -1) {
        printf("ID of student not found.\n");
        return;
    }
// info of the book
    char bookId[STUDENT_ID_LENGTH];
    printf("Enter the ID of book you want: ");
    scanf("%s", bookId);
    int date, month,year ;
    printf("Enter the date(DD.MM.YYYY): "); // here we should do some function to check if the date we input is valid but i have not done this sorry -_-
    scanf("%d.%d.%d", &date, &month, &year);

    int bookIndex = -1;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].id, bookId) == 0 && books[i].available == 1) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex != -1) {
        books[bookIndex].available = 0;
        strcpy(students[studentIndex].bookIds[students[studentIndex].numBooksBorrowed++], bookId);
        printf("Book  '%s' was successfully taken by  %s.\n", books[bookIndex].title, students[studentIndex].name);
        books[bookIndex].times_borrowed++;
    } else {
        printf("ID of book not found, or book not available!\n");
    }
}

//fuction to return the book, same idea as the borrow book but just the opostite(+/-)
void returnBook(struct Book books[], int numBooks, struct Student students[], int numStudents, struct BorrowedBook borrowedBooks[], int numBorrowedBooks) {
    char studentId[STUDENT_ID_LENGTH];
    int studentIndex;

    do {
        printf("Enter your ID: ");
        scanf("%s", studentId);

        studentIndex = -1;
        for (int i = 0; i < numStudents; i++) {
            if (strcmp(students[i].id, studentId) == 0) {
                studentIndex = i;
                break;
            }
        }

        if (studentIndex == -1) {
            printf("Student not found.Enter the correct ID!\n");
        }
    } while (studentIndex == -1);

    char bookId[STUDENT_ID_LENGTH];
    printf("Enter the book you want to return: ");
    scanf("%s", bookId);
    int date, month,year ;
    printf("Enter the return date(DD.MM.YYYY): ");// here we should do some function to check if the date we input is valid but i have not done this sorry -_-
    scanf("%d.%d.%d", &date, &month, &year);

    int bookIndex = -1;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].id, bookId) == 0 && books[i].available == 0) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex != -1) {
        books[bookIndex].available = 1;
        int bookIndexInStudent = -1;
        for (int i = 0; i < students[studentIndex].numBooksBorrowed; i++) {
            if (strcmp(students[studentIndex].bookIds[i], bookId) == 0) {
                bookIndexInStudent = i;
                break;
            }
        }

        if (bookIndexInStudent != -1) {
            for (int j = bookIndexInStudent; j < students[studentIndex].numBooksBorrowed - 1; j++) {
                strcpy(students[studentIndex].bookIds[j], students[studentIndex].bookIds[j + 1]);
            }
            students[studentIndex].numBooksBorrowed;
            printf("Book '%s' successfully returned by %s.\n", books[bookIndex].title, students[studentIndex].name);
        } else {
            printf("Book was not found in youre borrowing list!\n");
        }
    } else {
        printf("Book 404!\n");
    }
}
// display the most read books in the library(top 10)
void mostReadBooks(struct Book books[], int numBooks) {
    if (numBooks == 0) {
        printf("No book in the library..\n");
        return;
    }

    for (int i = 0; i < numBooks - 1; i++) {
        for (int j = 0; j < numBooks - i - 1; j++) {
            if (books[j].times_borrowed < books[j + 1].times_borrowed) {
                struct Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }

    printf("Top 10 most read book's:\n");
    int count = 0;
    for (int i = 0; i < numBooks && count < 10; i++) {
        if (books[i].times_borrowed > 0) {
            printf("Title: %s, Author: %s, is read: %d\n", books[i].title, books[i].author, books[i].times_borrowed);
            count++;
        }
    }
}
// display top 20 studen who read the most books
void mostReadStudents(struct Student students[], int numStudents) {
    if (numStudents == 0) {
        printf("No student in the library!\n");
        return;
    }

    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].numBooksBorrowed < students[j + 1].numBooksBorrowed) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("The students who read the most:\n");
    int count = 0;
    for (int i = 0; i < numStudents && count < 20; i++) {
        if (students[i].numBooksBorrowed > 0) {
            printf("Name: %s, ID: %s, Has read: %d\n", students[i].name, students[i].id, students[i].numBooksBorrowed);
            count++;
        }
    }
}

//save the studen in the studen's file(same idea as for the books)
void saveStudents(struct Student students[], int numStudents) {
    FILE *file = fopen(FILENAME_STUDENTS, "w");
    if (file == NULL) {
        printf("Error in opening the student file.\n");
        return;
    }
    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%s %s %d", students[i].name, students[i].id, students[i].numBooksBorrowed);
        for (int j = 0; j < students[i].numBooksBorrowed; j++) {
            fprintf(file, " %s", students[i].bookIds[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// load form the studen's file, if it does not exist we creat one (same idea as the books)
void loadStudents(struct Student students[], int *numStudents) {
    FILE *file = fopen(FILENAME_STUDENTS, "r");
    if (file == NULL) {
        printf("Student file does not exist.Creating a new one...\n");
        file = fopen(FILENAME_STUDENTS, "w");
        if (file == NULL) {
            printf("Error in creating a new file.\n");
            return;
        }
        fclose(file);
        *numStudents = 0;
        return;
    }
    while (*numStudents < MAX_STUDENTS && fscanf(file, "%s %s %d", students[*numStudents].name, students[*numStudents].id, &students[*numStudents].numBooksBorrowed) == 3) {
        for (int i = 0; i < students[*numStudents].numBooksBorrowed; i++) {
            fscanf(file, " %s", students[*numStudents].bookIds[i]);
        }
        (*numStudents)++;
    }
    fclose(file);
}

// register a studen function
void registerStudent(struct Student students[], int *numStudents) {
    if (*numStudents >= MAX_STUDENTS) {
        printf("The maximum number of students has been reached, can't add more!\n");
        return;
    }

    char studentName[NAME_LENGTH];
    printf("Enter your name: ");
    scanf("%s", studentName);
    char mbiemri[NAME_LENGTH];
    printf("Enter your surname:");
    scanf("%s",&mbiemri);

     
   char fakuteti[100]; 
    printf("Your faculty: ");
     scanf(" %[^\n]s", fakuteti); 
    

    
    int idExists;
    do {
        printf("Enter youre ID (13 char): ");
        scanf("%s", students[*numStudents].id);
        idExists = 0;
        if (strlen(students[*numStudents].id) != STUDENT_ID_LENGTH - 1) {
            printf("The ID must be the right length!\n");
            idExists = 1; 
        } else {
            for (int i = 0; i < *numStudents; i++) {
                if (strcmp(students[i].id, students[*numStudents].id) == 0) {
                    idExists = 1;
                    printf("This ID exist.Pls enter another ID!\n");
                    break;
                }
            }
        }
    } while (idExists);

     strcpy(students[*numStudents].name, studentName);
    strcat(students[*numStudents].name, " ");
    strcat(students[*numStudents].name, mbiemri);
    strcpy(students[*numStudents].faculty, fakuteti);
    students[*numStudents].numBooksBorrowed = 0; 
    (*numStudents)++;
    printf("Student  successfully registered.\n");
}
// display the student's in the library
void displayStudents(struct Student students[], int numStudents) {
    printf("\nStudents in the library:\n");
    if (numStudents == 0) {
        printf("No student in the library.\n");
        return;
    }
    for (int i = 0; i < numStudents; i++) {
        printf("ID: %s, Name: %s, Has read: %d\n", students[i].id, students[i].name, students[i].numBooksBorrowed);
    }
}

// function to display the discription of a book 
void displayBookDescription(struct Book books[], int numBooks) {
    char bookId[STUDENT_ID_LENGTH];
    printf("Enter the book ID to get the description: ");
    scanf("%s", bookId);
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].id, bookId) == 0) {
            printf("Book description  '%s': %s\n", books[i].title, books[i].description);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
}
