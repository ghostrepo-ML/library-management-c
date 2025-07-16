📚 Library Management System

A simple Library Management System written in C that manages books and students in a small academic library. It allows for adding/removing books, registering students, borrowing and returning books, and tracking the most active users and most-read books. Data is stored persistently in text files.
 I advise to have the code file in a folder, because the program will create 3 new file, one to run the program and two other's to save student's and the book's!


🔧 How It Works

The program is structured around three main entities:

    Books: Each with a title, author, description, ID, availability status, and how many times it has been borrowed.

    Students: Each with a name, ID, faculty, and a list of borrowed books.

    Borrowed Books: Tracks which student borrowed which book and on what date (not fully implemented yet for file tracking).

Upon launching, the system loads books and student data from books.txt and students.txt. It provides a menu-driven interface where the user can perform various operations.

All actions (adding books/students, borrowing/returning books, etc.) update the in-memory structures and are saved back to disk upon exit.

📌 Features

    Add / remove books and students

    Display all books or students

    Search for books by ID or display their descriptions

    Borrow and return books

    Show most borrowed books (top 10)

    Show most active students (top 20)

    Persistent storage using files



📂 File Storage

    books.txt – Stores book data: title, author, description, ID, availability, times borrowed.

    students.txt – Stores student data: name, ID, number of books borrowed, list of book IDs.

Function  Explanation


✅ void addBook(struct Book books[], int *numBooks)

Purpose: To add a new book to the library.

How it works:

    First, I check if there’s room to add another book by comparing *numBooks with MAX_BOOKS.

    If there's room, I ask the user to enter the title, author, and description of the book.

    Then, I ask for the book's ID, which must be exactly 13 characters.

    I validate:

        The length of the ID.

        That the ID is unique (not already in use by another book).

    Once validated, I mark the book as available (available = 1) and set its times_borrowed = 0.

    Finally, I increment *numBooks and confirm the book was added.

✅ void saveBooks(struct Book books[], int numBooks)

Purpose: To save all book information into a file.

Logic:

    I open books.txt in write mode.

    Looping through the books[] array, I use fprintf to write all the book fields to the file in a consistent format.

    Each line in the file represents one book.

    At the end, I close the file.

Why: This makes sure the book data is saved permanently and can be reloaded next time.
✅ void loadBooks(struct Book books[], int *numBooks)

Purpose: To load books from the file when the program starts.

Logic:

    I try opening books.txt in read mode.

    If the file doesn't exist, I create a new empty file.

    I use fscanf in a loop to read each line, extracting the values into the books[] array.

    I increase *numBooks for every successful load.

Why: So that data from previous sessions is restored when the program runs again.
✅ void removeBook(struct Book books[], int *numBooks)

Purpose: To delete a book using its ID.

Logic:

    Ask the user for the book ID.

    Loop through the books[] array to find it.

    Once found, I shift all books after it one position to the left.

    Then I decrease *numBooks by 1.

    If the book isn't found, I show an error.

✅ void displayBooks(struct Book books[], int numBooks)

Purpose: To list all books in the library.

Logic:

    I first check if numBooks is greater than 0.

    If it is, I loop through all the books and print their title, author, ID, availability, and times borrowed.

    If there are no books, I notify the user.

✅ void searchBookByID(struct Book books[], int numBooks)

Purpose: To find a book using its unique ID.

Logic:

    I ask the user to enter the book ID.

    I loop through the books to find a match.

    If found, I print its details (title, author, availability, times read).

    Otherwise, I show "Book not found."

✅ void borrowBook(...)

Purpose: To let a student borrow a book.

Logic:

    First, I ask for the student’s ID and look it up in the students[] array.

    If the student exists, I ask for the book ID.

    I also ask for the date of borrowing (stored but not used further).

    I check if the book is available.

    If yes:

        I mark it as not available.

        I store the book ID in the student's bookIds list.

        I increment the student's book count and the book’s borrow count.

    If not found or unavailable, I notify the user.

✅ void returnBook(...)

Purpose: To let a student return a book.

Logic:

    Ask for the student’s ID and find the student.

    Ask for the book ID and the return date.

    Check if the book exists and is currently marked as borrowed.

    If yes:

        Mark the book as available.

        Search the student's bookIds list for this book and remove it by shifting the list left.

    I confirm the return or show an error if the book wasn't borrowed by this student.

✅ void mostReadBooks(struct Book books[], int numBooks)

Purpose: To show the top 10 most borrowed books.

Logic:

    I sort the books array in descending order by times_borrowed using bubble sort.

    Then I loop through the top 10 books and print their titles, authors, and borrow counts.

✅ void mostReadStudents(struct Student students[], int numStudents)

Purpose: To list top 20 students who borrowed the most books.

Logic:

    Similar to books, I sort the students by numBooksBorrowed in descending order.

    I print the top 20 students' names, IDs, and how many books they've borrowed.

✅ void saveStudents(...)

Purpose: To save student data to a file.

Logic:

    I open students.txt in write mode.

    For each student:

        I write their name, ID, number of borrowed books, and the list of book IDs.

    I use spaces to separate fields and then add a newline per student.

✅ void loadStudents(...)

Purpose: To load student data from the file on startup.

Logic:

    Open students.txt in read mode.

    For each line, I read the student's name, ID, number of books, and their book IDs.

    Each student is added to the array and *numStudents is increased.

✅ void registerStudent(...)

Purpose: To register a new student.

Logic:

    Ask for student name, surname, and faculty.

    Combine the name and surname into a full name.

    Ask for a unique 13-character ID.

    Check for duplicates.

    If valid, save the data to the student array and initialize their borrow count to 0.

    Confirm registration.

✅ void displayStudents(...)

Purpose: To list all registered students.

Logic:

    Loop through the students[] array.

    Print each student's name, ID, and number of books they've borrowed.

✅ void displayBookDescription(...)

Purpose: To display a book’s full description.

Logic:

    Ask the user for the book ID.

    Search through the books for a match.

    If found, print the title and description.

    Otherwise, notify the user that the book wasn't found.

✅ Summary of Core Logic

    I use arrays of structs to store books and students.

    Files are used to persist data between sessions.

    Validation is done for IDs and limits (like max number of books/students).

    I track borrowing behavior and use sorting to show rankings.

    Most features are interactive via a menu, giving the user full control.

🚀 Running the Program
Requirements

    C compiler (e.g., gcc)

Compile

gcc library.c -o library

