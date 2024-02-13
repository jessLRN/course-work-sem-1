#define _CRT_SECURE_NO_WARNINGS
#include "library.h"
#include <cmath>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;
const char* categoryStrings[] = { "романы", "классика", "политика", "история", "биографии" };

void printBook(const BOOK& book)
{
	printf("%s, автор %s, вышла в %hu году. категория: %s. цена: %d руб.\n",
		book.title, book.author, book.year, categoryStrings[book.category-1], book.price);
}

void printBook(const BOOK* book)
{
	printf("%s, автор %s, вышла в %hu году. категория: %s. цена: %d руб.\n",
		book->title, book->author, book->year, categoryStrings[book->category-1], book->price);
}

void ClearBuffer()
{
	while (getchar() != '\n');
}


void initBook(BOOK& book) {

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
		printf("\nВведите данные: длина названия < 110 символов\n");
		printf("длина имени автора < 60 символов, цена > 0, 0 < год < 2022,\n");
		printf("категории 1: романы 2: классика 3: политика 4: история, 5: биографии\n");
		char title[100];
		printf("\nНазвание в формате Мастер и Маргарита: ");
		scanf("%99[^\n]", title);
		ClearBuffer();
		strcpy_s(book.title, 100, title);

		char author[50];
		printf("Автор в формате Михаил Булгаков: ");
		scanf("%49[^\n]", author);
		ClearBuffer();
		strcpy_s(book.author, 50, author);

		printf("Год в формате 1967: "); //1
		while (true) {
			int year = 2023;
			static char buf[100];
			scanf("%s", &buf);
			ClearBuffer();
			sscanf(buf, "%d", &year);
			if (year < 0 || year > 2022) printf("\nГод неверный, повторите попытку: ");
			else {
				book.year = year;
				break;
			}

		}
		printf("\nЦена в рублях в формате 429 (без копеек): ");
		while (true) {
			int price = -1000;
			static char buf[100];
			scanf("%s", &buf);
			ClearBuffer();
			sscanf(buf, "%d", &price);
			if (price <= 0) printf("\nВвод неверный, повторите попытку: ");
			else {
				book.price = price;
				break;
			}
		}

		int catNum = sizeof(categoryStrings) / sizeof(categoryStrings[0]);
		while (true) {
			printf("Выберите категорию: [1...%d]\n> ", catNum);
			int catId = -1;
			static char buf[100];
			scanf("%s", &buf);
			ClearBuffer();
			sscanf(buf, "%d", &catId);
			if (catId < 0 || catId > catNum) {
				printf("\nКатегория неверна, повторите попытку\n\n");
			}
			else {
				book.category = static_cast<Category>(catId);
				break;
			}
		}
}


int compareTitles(const BOOK& first, const BOOK& second)
{
	return strcmp(first.title, second.title);
}
int compareAuthors(const BOOK& first, const BOOK& second)
{
	return strcmp(first.author, second.author);
}
int compareYears(const BOOK& first, const BOOK& second)
{
	return first.year - second.year;
}
int compareCategories(const BOOK& first, const BOOK& second)
{
	return first.category - second.category;
}
int comparePrices(const BOOK& first, const BOOK& second)
{
	return first.price - second.price;
}
