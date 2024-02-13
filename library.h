#pragma once
#include "book.h"
#include <iostream>
struct LIBRARY
{
    int CountOfBooks;
    int capacity;
    BOOK** books;
};
extern const char* sortLabels[];
const int InitialSize = 100;
extern const char* categoryStrings[];
void performMenuAction(LIBRARY& library);
void deleteBooks(LIBRARY& library);
void initLibrary(LIBRARY& library);
void flushLibrary(LIBRARY& library);
void enlargeLibrary(LIBRARY& library);
void insertBook(LIBRARY& library);
void insertBook(LIBRARY& library, BOOK* book);
void printBooks(LIBRARY& library);
void printTitles(LIBRARY& library);
int WantToContinue();
void deleteBook(LIBRARY& library);
void addDefaultBook(LIBRARY& library, const char* author, const char* title, int year, int price, Category category);
void createDefaultLibrary(LIBRARY& library);
void libraryToFile(LIBRARY& library);
void readBooksFromFile(LIBRARY& library);
void flushFile();
void addNewBook(LIBRARY& library, BOOK* book);
void addNewBook(LIBRARY& library);
bool notInLibrary(LIBRARY& library, BOOK& book);
const char* chooseFileName();
FILE* makeFile();
void initFileNames();
void deleteFileNames();