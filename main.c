
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
FILE* file;
int bookCount;
void GetBooksFromFile();
void Display();
void InsertBook();
void LinearSearch();
void DeleteBook();
void DisplaySorted();
void Sort();
int ExitOrContinue();
char* GetBookIdOrName(char* attribute);
void BinarySearch();
void GetSearchTypeFromUser();
struct Book
{
    char Id[50];
    char Name[50];
    char Quantity[50];

};
struct Book books[100];
char booksNames[100][50];
struct Book GetBookFromUser();
int main()
{
    int choice = 0;
    printf("Welcome To Bookstore program:\n");
    while (choice!=6)
    {
        printf("Please Choose an operation:\n");
        printf("\tTo Insert New Book Press:(1)\n");
        printf("\tTo Delete A Book Press:(2)\n");
        printf("\tTo Search A Book Press:(3)\n");
        printf("\tTo Display All Books Press:(4)\n");
        printf("\tTo Display All Books Sorted Press:(5)\n");
        printf("\tTo Exit Press:(6)\n");
        printf("\nYour Choice:");
        scanf("%d", &choice);
        GetBooksFromFile();
        switch (choice)
        {
        case 1:
            printf("\n(Insert):\n");
            InsertBook();
            break;

        case 2:
            printf("\n(Delete):\n");

            DeleteBook();
            break;

        case 3:
            printf("\n(Search):\n");
            GetSearchTypeFromUser();
            break;
        case 4:
            printf("\n(Display):\n");

            Display();
            break;
        case 5:
            printf("\n(Display Sorted):\n");
            DisplaySorted();
            break;
        case 6:
            printf("\n(Program Ended!):\n");
            printf("Thank You!\n");
            break;
        default:
            printf("Please Choose A valid operation(numbers from 1 - 6)\n");
            break;
        }
        printf("\n-------------------------------------------------------------------------");
        if(choice>=1 && choice <= 5)
            choice = ExitOrContinue();
    }
    printf("Thank You!\n");
    return 0;
}


void InsertBook()
{
    struct Book book = GetBookFromUser();

    file=fopen("F:\\Bookstore.txt", "a");

    fprintf(file, "%s\t%s\t%s\t\n", book.Id, book.Name, book.Quantity);
    printf("Book has been Inserted Successfully!");
    bookCount++;
    fclose(file);
}

int ExitOrContinue()
{
    char answer[10];
    printf("\n\n");

    while (true)
    {
        printf("Do You Want To Make Another Operation? (Yes-No)\n");
        printf("Answer:");
        gets(answer);
        int size = strlen(answer);
        if (size == 0)
            gets(answer);


        if ((answer[0] == 'n' || answer[0] == 'N') && (answer[1] == 'o' || answer[1] == 'O'))
        {
            return 6;
            break;
        }
        else if ((answer[0] == 'y' || answer[0] == 'Y') && (answer[1] == 'e' || answer[1] == 'E')
                 && (answer[2] == 's' || answer[2] == 'S'))
        {
            printf("\n-------------------------------------------------------------------------\n");

            return 0;
            break;
        }
        else
        {
            printf("Incorrect Answer!\n\n");
        }
    }
}
void LinearSearch()
{
    char id[50];
    memcpy(id, GetBookIdOrName("Id"), 50);

    bool found = false;
    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(id, books[i].Id) == 0)
        {
            printf("%s found at location %d.\n", id, i + 1);
            printf("Book Name:%s\t\tBook Quantity:%s\n",books[i].Name, books[i].Quantity);
            found = true;
            break;
        }
    }
    if (!found)
        printf("Not Found!\n");
}

void BinarySearch()
{
    char name[50];
    memcpy(name, GetBookIdOrName("Name"), 50);
    Sort();
    int low, high, middle;
    low = 0;
    high = bookCount- 1;
    middle = (low + high) / 2;
    while (low <= high)
    {
        char* currntName = booksNames[middle];
        int cmpValue = strcmp(currntName, name);

        if (cmpValue <0)
            low = middle + 1;
        else if (cmpValue==0)
        {
            printf("%s found at location %d.\n", name, middle + 1);
            printf("Book Id:%s\t\tBook Quantity:%s\n", books[middle].Id, books[middle].Quantity);
            break;
        }
        else
            high = middle - 1;

        middle = (low + high) / 2;
    }
    if (low > high)
        printf("Not found! %s isn't present in the list.\n", name);
}



void Sort()
{
    for (int i = 0; i < bookCount; i++)
    {
        memcpy(booksNames[i], books[i].Name, 50);
    }
    int len = bookCount;
    for(int i=0; i< len; i++)
        for(int j=0; j< len; j++)
        {
            char tempWord[50];
            struct Book tempBook;
            if (strcmp(booksNames[i], booksNames[j]) < 0)
            {
                memcpy(tempWord, booksNames[j], 50);
                memcpy(booksNames[j], booksNames[i], 50);
                memcpy(booksNames[i], tempWord, 50);

                tempBook = books[i];
                books[i] = books[j];
                books[j] = tempBook;
            }
        }
}



void DisplaySorted()
{
    Sort();
    Display();
}
struct Book GetBookFromUser()
{
    printf("Please Enter New Book (Id,Name,Quantity)");
    struct Book book;
    printf("\nId:");
    gets(book.Id);
    gets(book.Id);
    printf("Name:");
    gets(book.Name);
    printf("Quantity:");
    gets(book.Quantity);
    return book;
}

void Display()
{

    for (int i = 0; i < bookCount; i++)
    {
        printf("%s\t%s\t%s\t\n", books[i].Id, books[i].Name, books[i].Quantity);
    }

}

void GetBooksFromFile()
{
    file=fopen("F:\\Bookstore.txt", "r");
    int lineCount = 0;
    bookCount = 0;
    char c;
    struct Book book = { '\0','\0','\0' };
    bool fileEnded = false;
    char line[150] = { '\0' };
    if (file == NULL)
    {
        printf("File is Empty");
        return;
    }
    while (!fileEnded)
    {
        c = fgetc(file);
        if (c== '\n'||c==EOF)
        {
            int len = strlen(line);

            int count = 0;
            int valueIndex = 0;
            char tempValue[50] = { '\0' };

            for (int i = 0; i < 50; i++)
            {
                book.Id[i] = '\0';
                book.Name[i] = '\0';
                book.Quantity[i] = '\0';
            }
            for (int i = 0; i < len+1; i++)
            {
                if (line[i] == '\t')
                {
                    switch (valueIndex)
                    {
                    case 0:
                        for (int s = 0; s < sizeof(tempValue); s++)
                            book.Id[s] = tempValue[s];
                        break;

                    case 1:
                        for (int s = 0; s < sizeof(tempValue); s++)
                            book.Name[s] = tempValue[s];
                        break;
                    case 2:
                        for (int s = 0; s < sizeof(tempValue); s++)
                            book.Quantity[s] = tempValue[s];
                        break;
                    default:
                        break;
                    }
                    memset(tempValue, 0, 50);
                    count = 0;
                    valueIndex++;
                }
                else
                {
                    tempValue[count] = line[i];
                    count++;
                }
            }
            lineCount = 0;
            memset(line, 0, 150);

            books[bookCount] = book;
            bookCount++;
        }
        else
        {
            line[lineCount] = c;
            lineCount++;
        }

        if (c == EOF)
            fileEnded = true;
    }
    fclose(file);
}


char* GetBookIdOrName(char * attribute)
{
    char *attrValue=malloc(50);
    printf("Please Enter Book %s\n", attribute);
    printf("Book %s:", attribute);
    gets(attrValue);
    gets(attrValue);
    return attrValue;
}
void DeleteBook()
{
    FILE* fileptr2;
    char* id=GetBookIdOrName("Id");
    bool deleted = false;
    fileptr2=fopen("F:\\tempFile.txt", "w+");
    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(id, books[i].Id) != 0)
        {
            fprintf(fileptr2, "%s\t%s\t%s\t\n", books[i].Id, books[i].Name, books[i].Quantity);
        }
        else
            deleted = true;
    }
    fclose(fileptr2);
    remove("F:\\Bookstore.txt");
    rename("F:\\tempFile.txt", "F:\\Bookstore.txt" );
    if (!deleted)
        printf("No such book with this ID,Try Again\n");
    else
        printf("Book Has Been Deleted!\n");
}

void GetSearchTypeFromUser()
{
    int choice=0;
    printf("Choose Search Type:\n");
    printf("\t1-Linear Search.\n");
    printf("\t2-Binary Search.\n");
    printf("\tYour Choice:");
    scanf("%d", &choice);

    if (choice == 1)
    {
        LinearSearch();
    }
    else if (choice == 2)
    {
        BinarySearch();
    }
    else
    {
        printf("\n\tIncorrect Choice,Try Again!");
    }
}

