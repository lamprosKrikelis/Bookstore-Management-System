/* 	Krikelis Lampros 
	Pliroforikis me efarmoges sti bioiatriki 
	Prox Programmatismos 2022
	
	Book Store managment with dynamic arrays
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_LEN 256

// define the structures for books, authors, and writes
typedef struct book
{
    char *title;
    int release_date;
    float price;
} book;

typedef struct author
{
    int writer_id;
    char *surname;
    char *name;
    int num_of_books;
} author;

typedef struct writes
{
    char *title;
    int writer_id;
} writes;

// global variables for the dynamic arrays of books, authors, and writes
book *books_arr = NULL;
author *author_arr = NULL;
writes *writes_arr = NULL;

// global variables for the number of books, authors, and writes
int num_books = 0;
int num_authors = 0;
int num_writes = 0;

// Function prototypes
void load_data();
void load_data();
void save_data();
void add_author();
void add_book();
void search_author_by_name();
void search_book_by_title();
void delete_author_by_id();
void delete_book_by_title();
void display_books();
void display_authors();
void display_writes();

int main()
{
    int option;
    book *book_arr = (book *)malloc(sizeof(book));
    author *author_arr = (author *)malloc(sizeof(author));
    writes *writes_arr = (writes *)malloc(sizeof(writes));

    load_data();
    
    // get the data from file displayed in terminal 
    display_books();
    display_writes();
    display_authors();

    while (1)
    {
        printf("Menu:\n");
        printf("1. Add author\n");
        printf("2. Add book\n");
        printf("3. Search author by name\n");
        printf("4. Search book by title\n");
        printf("5. Delete author by id\n");
        printf("6. Delete book by title\n");
        printf("7. Exit\n");

        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            add_author();
            break;
        case 2:
            add_book();
            break;
        case 3:
            search_author_by_name();
            break;
        case 4:
            search_book_by_title();
            break;
        case 5:
            delete_author_by_id();
            break;
        case 6:
            delete_book_by_title();
            break;
        case 7:
            save_data();
            exit(0);
            break;
        default:
            printf("Invalid choice of option choose again!");
        }
    }
}

void load_data()
{
    // open the files in read mode
    FILE *books_file = fopen("Books.txt", "r");
    FILE *authors_file = fopen("Author.txt", "r");
    FILE *writes_file = fopen("Writes.txt", "r");

    // check if the files were successfully opened
    if (books_file == NULL || authors_file == NULL || writes_file == NULL)
    {
        printf("Error: unable to open one or more of the input files.\n");
        return;
    }

    // read the data from the books file
    char title[MAX_LEN];
    int release_date;
    float price;
    while (fscanf(books_file, "%s %d %f", title, &release_date, &price) == 3)
    {
        // allocate memory for a new book structure
        book *new_book = (book *)malloc(sizeof(book));
        if (new_book == NULL)
        {
            printf("Error: unable to allocate memory for a new book.\n");
            return;
        }

        // store the book data in the new book structure
        new_book->title = strdup(title);
        new_book->release_date = release_date;
        new_book->price = price;

        // increase the number of books
        num_books++;

        // reallocate memory for the books array to make room for the new book
        books_arr = (book *)realloc(books_arr, num_books * sizeof(book));
        if (books_arr == NULL)
        {
            printf("Error: unable to reallocate memory for the books array.\n");
            return;
        }

        // add the new book to the books array
        books_arr[num_books - 1] = *new_book;

        // free the memory allocated for the new book
        free(new_book);
    }

    // read the data from the authors file
    int writer_id;
    char surname[MAX_LEN];
    char name[MAX_LEN];
    int num_of_books;

    while (fscanf(authors_file, "%d %s %s %d", &writer_id, surname, name, &num_of_books) == 4)
    {
        // allocate memory for a new author structure
        author *new_author = (author *)malloc(sizeof(author));
        if (new_author == NULL)
        {
            printf("Error: unable to allocate memory for a new author.\n");
            return;
        }

        // store the author data in the new author structure
        new_author->writer_id = writer_id;
        new_author->surname = strdup(surname);
        new_author->name = strdup(name);
        new_author->num_of_books = num_of_books;

        // increase the number of authors
        num_authors++;

        // reallocate memory for the authors array to make room for the new author
        author_arr = (author *)realloc(author_arr, num_authors * sizeof(author));
        if (author_arr == NULL)
        {
            printf("Error: unable to reallocate memory for the authors array.\n");
            return;
        }

        // add the new author to the authors array
        author_arr[num_authors - 1] = *new_author;

        // free the memory allocated for the new author
        free(new_author);
    }

    // read the data from the writes file
    while (fscanf(writes_file, "%s %d", title, &writer_id) == 2)
    {
        // allocate memory for a new writes structure
        writes *new_writes = (writes *)malloc(sizeof(writes));
        if (new_writes == NULL)
        {
            printf("Error: unable to allocate memory for a new writes.\n");
            return;
        }

        // store the writes data in the new writes structure
        new_writes->title = strdup(title);
        new_writes->writer_id = writer_id;

        // increase the number of writes
        num_writes++;

        // reallocate memory for the writes array to make room for the new writes
        writes_arr = (writes *)realloc(writes_arr, num_writes * sizeof(writes));
        if (writes_arr == NULL)
        {
            printf("Error: unable to reallocate memory for the writes array.\n");
            return;
        }

        // add the new writes to the writes array
        writes_arr[num_writes - 1] = *new_writes;

        // free the memory allocated for the new writes
        free(new_writes);
    }

    // close the files
    fclose(books_file);
    fclose(authors_file);
    fclose(writes_file);
}

int compare_books_by_title(const void *a, const void *b)
{
    book *book1 = (book *)a;
    book *book2 = (book *)b;
    return strcmp(book1->title, book2->title);	 
}

int compare_writes_by_title(const void *a, const void *b)
{
    writes *write1 = (writes *)a;
    writes *write2 = (writes *)b;
    return strcmp(write1->title, write2->title);
}

int compare_authors_by_id(const void *a, const void *b)
{
    const author *author1 = (const author *)a;
    const author *author2 = (const author *)b;
    return (author1->writer_id > author2->writer_id) - (author1->writer_id < author2->writer_id);
}

void add_author()
{
    // increase the size of the author array by 1
    author_arr = (author *)realloc(author_arr, sizeof(author) * (num_authors + 1));
    
	//srand(time(NULL));

    // Generate a random number
    author_arr[num_authors].writer_id = num_authors + 1 ; // + rand() % 256 ;

    // allocate memory for the surname and name pointers
    author_arr[num_authors].surname = (char *)malloc(MAX_LEN * sizeof(char));
    author_arr[num_authors].name = (char *)malloc(MAX_LEN * sizeof(char));

    // get the writer_id, surname, and name of the new author from the user

    printf("Enter the surname of the new author: ");
    scanf("%s", author_arr[num_authors].surname);

    printf("Enter the name of the new author: ");
    scanf("%s", author_arr[num_authors].name);

    // set the initial number of books written by the author to 0
    author_arr[num_authors].num_of_books = 0;

    // increment the number of authors
    num_authors++;
    qsort(author_arr, num_authors, sizeof(author), compare_authors_by_id);
}

void add_book()
{
    // allocate memory for a new book structure
    book *new_book = (book *)malloc(sizeof(book));
    if (new_book == NULL)
    {
        printf("Error: unable to allocate memory for a new book.\n");
        return;
    }
    
    fflush(stdin);
    
    // get the book data from the user
    char title[MAX_LEN];
    int release_date;
    float price;
    
	printf("Enter the book title: ");
    scanf("%s", title);
    printf("Enter the book release date: ");
    scanf("%d", &release_date);
    printf("Enter the book price: ");
    scanf("%f", &price);

    // store the book data in the new book structure
    new_book->title = (char *)malloc(strlen(title) + 1);
    if (new_book->title == NULL)
    {
        printf("Error: unable to allocate memory for the book title.\n");
        free(new_book);
        return;
    }
    strcpy(new_book->title, title);
    new_book->release_date = release_date;
    new_book->price = price;

    // add the new book to the books array
    books_arr = (book *)realloc(books_arr, (num_books + 1) * sizeof(book));
    if (books_arr == NULL)
    {
        printf("Error: unable to reallocate memory for the books array.\n");
        free(new_book->title);
        free(new_book);
        return;
    }
    books_arr[num_books] = *new_book;

    fflush(stdin);
    // get the author id from the user
    int writer_id;
    printf("Enter the author id: ");
    scanf("%d", &writer_id);

    // check if the author id is valid
    int i;
    int found = 0;
    for (i = 0; i < num_authors; i++)
    {
        if (author_arr[i].writer_id == writer_id)
        {
            // increase the number of books written by this author
            author_arr[i].num_of_books++;
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Error: no author with id %d was found. Add authour first\n", writer_id);
        free(new_book->title);
        free(new_book);
        return;
    }

    // add a new entry to the writes array
    writes *new_writes = (writes *)malloc(sizeof(writes));
    if (new_writes == NULL)
    {
        printf("Error: unable to allocate memory for a new writes entry.\n");
        free(new_book->title);
        free(new_book);
        return;
    }
    new_writes->title = (char *)malloc(strlen(title) + 1);

    if (new_writes->title == NULL)
    {
        printf("Error: unable to allocate memory for the writes title.\n");
        free(new_writes);
        free(new_book->title);
        free(new_book);
        return;
    }
    strcpy(new_writes->title, title);
    new_writes->writer_id = writer_id;

    // add the new writes entry to the writes array
    writes_arr = (writes *)realloc(writes_arr, (num_writes + 1) * sizeof(writes));
    if (writes_arr == NULL)
    {
        printf("Error: unable to reallocate memory for the writes array.\n");
        free(new_writes->title);
        free(new_writes);
        free(new_book->title);
        free(new_book);
        return;
    }
    writes_arr[num_writes] = *new_writes;
    num_writes++;

    // free the allocated memory
    free(new_writes->title);
    free(new_writes);
    free(new_book->title);
    free(new_book);
    num_books++;
    qsort(books_arr, num_books, sizeof(book), compare_books_by_title);
    printf("Book added successfully.\n");
}
// Function to search for an author by name
void search_author_by_name()
{
    char name[50];
    fflush(stdin);
    printf("Enter the name of the author to search for: ");
    gets(name);

    // loop through the author array and search for the specified name
    for (int i = 0; i < num_authors; i++)
    {
        if (strcmp(author_arr[i].name, name) == 0)
        {
            printf("Author found!\n");
            printf("Writer ID: %d\n", author_arr[i].writer_id);
            printf("Surname: %s\n", author_arr[i].surname);
            printf("Name: %s\n", author_arr[i].name);
            printf("Number of books written: %d\n\n", author_arr[i].num_of_books);
            return;
        }
    }
    printf("Author not found.\n");
}

void search_book_by_title()
{
    fflush(stdin);
    char title[100];
    printf("Enter the title to search for: ");
    gets(title);
    int i, found = 0;
    for (i = 0; i < num_books; i++)
    {
        if (strcmp(title, books_arr[i].title) == 0)
        {
            found = 1;
            printf("Title: %s\n", books_arr[i].title);
            printf("Release date: %d\n", books_arr[i].release_date);
            printf("Price: %f\n", books_arr[i].price);
            break;
        }
    }
    if (!found)
    {
        printf("Book not found\n");
    }
}

void delete_author_by_id()
{
    int id;
    printf("Enter the ID of the author you want to delete: ");
    scanf("%d", &id);

    // find the index of the author with the given ID in the author_arr array
    int index = -1;
    for (int i = 0; i < num_authors; i++)
    {
        if (author_arr[i].writer_id == id)
        {
            index = i;
            break;
        }
    }

    // if the author was not found, print an error message and return
    if (index == -1)
    {
        printf("Error: unable to find an author with the given ID.\n");
        return;
    }

    // free the memory allocated for the author's name and surname
    free(author_arr[index].name);
    free(author_arr[index].surname);

    // shift the remaining elements in the author_arr array to fill the gap
    for (int i = index; i < num_authors - 1; i++)
    {
        author_arr[i] = author_arr[i + 1];
    }

    // decrement the number of authors
    num_authors--;

    // print a success message
    printf("Successfully deleted the author with ID %d.\n", id);

    // delete the books written by the author with the given ID
    for (int i = 0; i < num_writes; i++)
    {
        if (writes_arr[i].writer_id == id)
        {
            // find the index of the book with the given title in the books_arr array
            int book_index = -1;
            for (int j = 0; j < num_books; j++)
            {
                if (strcmp(writes_arr[i].title, books_arr[j].title) == 0)
                {
                    book_index = j;
                    break;
                }
            }

            // if the book was not found, print an error message and return
            if (book_index == -1)
            {
                printf("Error: unable to find a book with the given title.\n");
                return;
            }

            // free the memory allocated for the book title
            free(books_arr[book_index].title);

            // shift the remaining elements in the books_arr array to fill the gap
            for (int j = book_index; j < num_books - 1; j++)
            {
                books_arr[j] = books_arr[j + 1];
            }

            // decrement the number of books
            num_books--;

            // free the memory allocated for the book title in the writes_arr array
            free(writes_arr[i].title);

            // shift the remaining elements in the writes_arr array to fill the gap
            for (int j = i; j < num_writes - 1; j++)
            {
                writes_arr[j] = writes_arr[j + 1];
            }

            // decrement the number of writes
            num_writes--;
            i--;
        }
    }
}

void delete_book_by_title()
{
    fflush(stdin);
    printf("Enter Book Title you want to delete: ");
    char title[100];
    gets(title);
    // find the index of the book with the specified title
    int index = -1;
    for (int i = 0; i < num_books; i++)
    {
        if (strcmp(books_arr[i].title, title) == 0)
        {
            index = i;
            break;
        }
    }

    // if the book was found, delete the book from the array
    if (index >= 0)
    {
        // shift the remaining elements in the array to fill the gap
        for (int i = index; i < num_books - 1; i++)
        {
            books_arr[i] = books_arr[i + 1];
        }

        // decrease the number of books
        num_books--;

        // sort the books array by title
        qsort(books_arr, num_books, sizeof(book), compare_books_by_title);

        // delete the records for the book from the writes array
        for (int i = 0; i < num_writes; i++)
        {
            if (strcmp(writes_arr[i].title, title) == 0)
            {
                // shift the remaining elements in the array to fill the gap
                for (int j = i; j < num_writes - 1; j++)
                {
                    writes_arr[j] = writes_arr[j + 1];
                }

                // decrease the number of writes
                num_writes--;

                // decrease the index to account for the shifted elements
                i--;
            }
        }

        // sort the writes array by title
        qsort(writes_arr, num_writes, sizeof(writes), compare_writes_by_title);
    }
}

void save_data()
{
    // open the files in write mode
    FILE *books_file = fopen("Books.txt", "w");
    FILE *authors_file = fopen("Author.txt", "w");
    FILE *writes_file = fopen("Writes.txt", "w");

    // check if the files were successfully opened
    if (books_file == NULL || authors_file == NULL || writes_file == NULL)
    {
        printf("Error: unable to open one or more of the output files.\n");
        return;
    }

    // write the modified data to the books file
    for (int i = 0; i < num_books; i++)
    {
        fprintf(books_file, "%s %d %.2f\n", books_arr[i].title, books_arr[i].release_date, books_arr[i].price);
    }

    // write the modified data to the authors file
    for (int i = 0; i < num_authors; i++)
    {
        fprintf(authors_file, "%d %s %s %d\n", author_arr[i].writer_id, author_arr[i].surname, author_arr[i].name, author_arr[i].num_of_books);
    }

    // write the modified data to the writes file
    for (int i = 0; i < num_writes; i++)
    {
        fprintf(writes_file, "%s %d\n", writes_arr[i].title, writes_arr[i].writer_id);
    }

    // close the files
    fclose(books_file);
    fclose(authors_file);
    fclose(writes_file);

    // free the memory allocated to the books, authors, and writes arrays
    for (int i = 0; i < num_books; i++)
    {
        free(books_arr[i].title);
    }
    free(books_arr);

    for (int i = 0; i < num_authors; i++)
    {
        free(author_arr[i].surname);
        free(author_arr[i].name);
    }
    free(author_arr);

    for (int i = 0; i < num_writes; i++)
    {
        free(writes_arr[i].title);
    }
    free(writes_arr);
}
void display_books()
{
    // check if the books array is empty
    if (num_books == 0)
    {
        printf("No books are available.\n");
        return;
    }

    // print the books data
    printf("Title\t\tRelease Date\tPrice\n");
    printf("---------------------------------\n");
    for (int i = 0; i < num_books; i++)
    {
        printf("%s\t\t%d\t\t%.2f\n", books_arr[i].title, books_arr[i].release_date, books_arr[i].price);
    }
}

void display_authors()
{
    // check if the authors array is empty
    if (num_authors == 0)
    {
        printf("No authors are available.\n");
        return;
    }

    // print the authors data
    printf("ID\t\tName\t\t\t\tBooks\n");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < num_authors; i++)
    {
        printf("%d\t\t%s %s\t\t%d\n", author_arr[i].writer_id, author_arr[i].surname, author_arr[i].name, author_arr[i].num_of_books);
    }
}

void display_writes()
{
    // check if the writes array is empty
    if (num_writes == 0)
    {
        printf("No writes are available.\n");
        return;
    }

    // print the writes data
    printf("Title\t\tAuthor ID\n");
    printf("------------------------------\n");
    for (int i = 0; i < num_writes; i++)
    {
        printf("%s\t\t%d\n", writes_arr[i].title, writes_arr[i].writer_id);
    }
}

