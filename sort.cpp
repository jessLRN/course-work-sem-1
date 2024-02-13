#define _CRT_SECURE_NO_WARNINGS
#include "sort.h"
#include <cmath>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;
const char* sortLabels[] = { "по названию", "по автору", "по году издания", "по цене", "по категории" };
int (*sorts[])(const BOOK&, const BOOK&) =
{
	compareTitles,
	compareAuthors,
	compareYears,
	comparePrices,
	compareCategories,
};

void sortChoice(LIBRARY& library)
{
	if (library.CountOfBooks > 0)
	{
		while (true)
		{
			printf("Выберите, пожалуйста, тип сортировки из предложенных:\n\n");
			printSortTypes();
			printf("\nТип сортировки: ");
			int choice = input();
			if (choice > 0 && choice <= 5)
			{
				sortLibrary(library, sorts[choice - 1]);
				printf("\nУспешно! Теперь библиотека выглядит так:\n\n");
				printBooks(library);
				break;
			}
			else
			{
				printf("\nТакого типа сортировки нет! Пожалуйста, попробуйте заново\n");
			}
		}
	}
	else printf("\nБиблиотека пуста\n");
}

void printSortTypes()
{
	for (int i = 0; i < sizeof(sortLabels) / sizeof(sortLabels[0]); i++)
	{
		printf("%d - %s\n", i + 1, sortLabels[i]);
	}
}

void sortLibrary(LIBRARY& library, int (*sorts)(const BOOK&, const BOOK&))
{
	BOOK** books = library.books;
	for (int i = 1; i < library.CountOfBooks; i++)
	{
		int cur = i;
		while (cur > 0 && sorts(*books[cur-1], *books[cur]) >= 0)
		{
			std::swap(books[cur - 1], books[cur]);
			cur--;
		}
	}

}

void printBooksByAuthor(LIBRARY& library)
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int CountOfAuthors = printAuthors(library);
	while (true)
	{
		printf("\nПожалуйста, введите номер автора: ");
		int j = input();
		if (j >= 0 && j < CountOfAuthors)
		{
			int k = 0;
			const char* author = (*library.books[j]).author;
			for (int i = 0; i < CountOfAuthors; i++)
			{
				if (strcmp((*library.books[i]).author, author) == 0)
				{
					printf("\t[%d] %s\n", k + 1, (*library.books[i]).title);
					k++;
				}
			}
			if (k == 0) printf("\nТакого автора в библиотеке нет!\n");
			break;
		}
		else printf("\nНет автора под таким номером!\n");
	}

}
int printAuthors(LIBRARY& library)
{
	if (library.CountOfBooks > 0)
	{
		printf("\nСписок авторов, входящих в библиотеку:\n\n");
		sortLibrary(library, sorts[1]);
		int k = 1;
		printf("\t[%d] %s\n", 1, (*library.books[0]).author);
		for (int i = 1; i < library.CountOfBooks; i++)
		{
			if (strcmp((*library.books[i]).author, (*library.books[i - 1]).author) != 0)
			{
				printf("\t[%d] %s\n", ++k, (*library.books[i]).author);
			}
		}
		return k;
	}
	else printf("\nБиблиотека пуста!\n");
	return 0;
}