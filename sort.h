#pragma once
#include "library.h"
#include <iostream>
enum SortType 
{
    title,
    author,
    year,
    price,
    category,
    SortLabelsSize,
};
extern const char* sortLabels[];
void sortChoice(LIBRARY& library);
void printSortTypes();
void sortLibrary(LIBRARY& library, int (*sorts)(const BOOK&, const BOOK&));
void printBooksByAuthor(LIBRARY& library);
int printAuthors(LIBRARY& library);
extern int (*sorts[])(const BOOK&, const BOOK&);
void printBooksByAuthor(LIBRARY& library);
int printAuthors(LIBRARY& library);