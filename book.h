#pragma once
//#include "sort.h"
enum Category {
    CLASSICS=1,
    POST_MODERN,
    SCIENCE,
    BIBLIOGRAPHY,
    ANCIENT,
};
struct BOOK {
    int year;
    int price;
    Category category;
    char author[50];
    char title[100];
};
void printBook(const BOOK& book);
void printBook(const BOOK* book);
void ClearBuffer();
void initBook(BOOK& book);
int compareTitles(const BOOK& first, const BOOK& second);
int compareAuthors(const BOOK& first, const BOOK& second);
int compareYears(const BOOK& first, const BOOK& second);
int compareCategories(const BOOK& first, const BOOK& second);
int comparePrices(const BOOK& first, const BOOK& second);
int input();