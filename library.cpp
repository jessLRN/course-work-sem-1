#define _CRT_SECURE_NO_WARNINGS
#include "library.h"
#include "sort.h"
#include <errno.h>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;
int CountOfFiles = 3;
char** FileNames = new char* [10];
void initFileNames()
{
	FileNames[0] = const_cast<char*>("library1.txt");
	FileNames[1] = const_cast<char*>("library2.txt");
	FileNames[2] = const_cast<char*>("library3.txt");
}
void deleteFileNames()
{
	for (int i = 0; i < CountOfFiles; i++) delete[] FileNames[i];
	delete[] FileNames;
}
void initLibrary(LIBRARY& library)
{
	library.CountOfBooks = 0;
	library.capacity = InitialSize;
	library.books = new BOOK * [InitialSize];
}
void flushLibrary(LIBRARY& library)
{
	if (library.CountOfBooks > 0)
	{
		for (int i = 0; i < library.CountOfBooks; i++) delete library.books[i];
		initLibrary(library);
		printf("\nБиблиотека успешно очищена.\n");
	}
	else printf("\nБиблиотека уже пуста!\n");
}
void enlargeLibrary(LIBRARY& library)
{
	BOOK** temp = new BOOK * [library.capacity];
	int LastCapacity = library.capacity;
	int NewCapacity = LastCapacity + InitialSize;
	for (int i = 0; i < library.CountOfBooks; i++) temp[i] = library.books[i];
	//if (library.CountOfBooks > 0) delete[] library.books;
	library.books = new BOOK * [NewCapacity];
	library.capacity = NewCapacity;
	for (int i = 0; i < library.CountOfBooks; i++) library.books[i] = temp[i];
	delete[] temp;
}

void insertBook(LIBRARY& library)
{
	BOOK* NewBook = new BOOK;
	initBook(*NewBook);
	if (notInLibrary(library, *NewBook))
	{
		library.CountOfBooks++;
		library.books[library.CountOfBooks - 1] = NewBook;
	}
}
void insertBook(LIBRARY& library, BOOK* book)
{
	BOOK* NewBook = book;
	if (notInLibrary(library, *NewBook))
	{
		library.CountOfBooks++;
		library.books[library.CountOfBooks - 1] = NewBook;
	}

}
void printBooks(LIBRARY& library) //4
{
	if (library.CountOfBooks == 0) printf("\nБиблиотека пуста! Вы можете добавить книгу через меню\n\n");
	else
	{
		while (true)
		{
			printf("\nЕсли вы хотите вывести полную коллекцию книг, введите 0; все книги определенного автора, введите 1: ");
			int choice = input();
			if (choice == 0)
			{
				printf("\nКоллекция книг:\n\n");
				for (int i = 0; i < library.CountOfBooks; i++)
				{
					printf("[%d] ", i + 1);
					printBook(library.books[i]);
				}
				break;
			}
			else if (choice == 1)
			{
				printBooksByAuthor(library); //4
				break;
			}
			else printf("\nНеправильный ввод! Пожалуйста, попробуйте снова\n");
		}
	}
}
void printTitles(LIBRARY& library)
{
	if (library.CountOfBooks > 0)
	{
		printf("Список книг, входящих в библиотеку:\n");
		for (int i = 0; i < library.CountOfBooks; i++) printf("\t[%d] %s\n", i + 1, (*library.books[i]).title);
	}
	else printf("\nБиблиотека пуста!\n");
}



int WantToContinue()
{
	while (true)
	{
		printf("\nВы действительно хотите продолжить?\n");
		printf("Введите 1, для продолжения, 0 для выхода: ");
		int choice = input();
		if (choice == 1) return 1;
		else if (choice == 0) return 0;
		else printf("Неправильный ввод! Пожалуйста, попробуйте заново\n");
	}
}

void deleteBook(LIBRARY& library)
{
	//int wantToContinue = WantToContinue();
	while (true)
	{
		if (library.CountOfBooks > 0)
		{
			printf("Выберите, пожалуйста, книгу, которую вы хотите удалить:\n\n");
			printTitles(library);
			printf("\nНомер книги для удаления:\n> ");
			int choice = input();
			if (choice > 0 && choice <= library.CountOfBooks)
			{
				for (int i = choice - 1; i < library.CountOfBooks; i++) library.books[i] = library.books[i + 1];
				library.CountOfBooks--;
				printf("\nОперация прошла успешно! Теперь список книг выглядит так: \n\n");
				printTitles(library);
				break;
			}
			else
			{
				printf("\nКниги под таким номером нет! Пожалуйста, попробуйте заново\n");
			}
		}
		else
		{
			printf("\nБиблиотека пуста! Вы можете добавить в нее книги через меню\n");
			break;
		}
	}

}
void deleteBooks(LIBRARY& library)
{
	int wantToContinue = WantToContinue();
	if (wantToContinue)
	{
		while (true)
		{
			printf("Если вы хотите удалить одну книгу, нажмите 0; диапазон книг - 1: ");
			int choice = input();
			if (choice == 0)
			{
				deleteBook(library);
				break;
			}
			else if (choice == 1)
			{
				while (true)
				{
					if (library.CountOfBooks > 0)
					{
						printTitles(library);
						printf("\nНачало диапазона для удаления: ");
						int choice1 = input();
						printf("\nКонец диапазона для удаления: ");
						int choice2 = input();
						if (choice1 > choice2) std::swap(choice1, choice2);
						if (choice1 > 0 && choice1 <= library.CountOfBooks && choice2 > 0 && choice2 <= library.CountOfBooks)
						{

							for (int i = 0; i < choice2 - choice1 + 1; i++)
							{
								library.CountOfBooks--;
								library.books[i + choice1 - 1] = library.books[i + choice2];
							}

							printf("\nОперация прошла успешно! Теперь список книг выглядит так: \n\n");
							printTitles(library);
							break;
						}
						else
						{
							printf("\n\nКниги под таким номером нет! Пожалуйста, попробуйте заново\n");
						}
					}
					else
					{
						printf("\nБиблиотека пуста! Вы можете добавить в нее книги через меню\n");
						break;
					}
				}
				if (library.CountOfBooks > 0) printf("\nКнига(и) успешно удалена(ы)!\n");
				break;
			}
			else if (wantToContinue != 0) printf("\nНеверный ввод! Пожалуйста, попробуйте заново\n");
			else break;
		}
	}

}
void addDefaultBook(LIBRARY& library, const char* author, const char* title, int year, int price, Category category)
{
	BOOK* book = new BOOK();
	strcpy_s(book->author, 50, author);
	strcpy_s(book->title, 100, title);
	book->year = year;
	book->price = price;
	book->category = category;
	addNewBook(library, book);
}
void deleteTemp(BOOK* book)
{
	book->year = 0;
	book->price = 0;
	book->category = CLASSICS;
	strcpy_s(book->author, 50, "");
	strcpy_s(book->title, 100, "");
}
void createDefaultLibrary(LIBRARY& library)
{
	addDefaultBook(library, "Илья Ильф, Евгений Петров", "Двенадцать стульев", 1928, 991, CLASSICS);
	addDefaultBook(library, "Антон Чехов", "Палата № 6", 1892, 600, CLASSICS);
	addDefaultBook(library, "Эрнест Хемингуэй", "Старик и море", 1952, 1315, CLASSICS);
	addDefaultBook(library, "Джек Лондон", "Белый Клык", 1906, 653, CLASSICS);
	addDefaultBook(library, "Михаил Шолохов", "Тихий Дон", 1940, 1201, CLASSICS);

	addDefaultBook(library, "Марк Z. Данилевский", "Дом листьев", 2000, 280, POST_MODERN);
	addDefaultBook(library, "Курт Воннегут", "Завтрак для чемпионов", 1973, 339, POST_MODERN);
	addDefaultBook(library, "Хантер С. Томпсон", "Страх и отвращение в Лас-Вегасе", 1971, 170, POST_MODERN);
	addDefaultBook(library, "Брет Истон Эллис", "Американский психопат", 1991, 611, POST_MODERN);
	addDefaultBook(library, "Джозеф Хеллер", "Уловка-22", 1961, 1000, POST_MODERN);

	addDefaultBook(library, "Нильс Бор", "Атомная физика и человеческое познание", 1934, 500, SCIENCE);
	addDefaultBook(library, "Питер Эткинс", "Молекулы", 1987, 304, SCIENCE);
	addDefaultBook(library, "Стивен Пинкер", "Язык как инстинкт", 1994, 200, SCIENCE);
	addDefaultBook(library, "Тобиас Данциг", "Числа - язык науки", 1930, 1200, SCIENCE);
	addDefaultBook(library, "Пол Фейерабенд", "Против метода", 1975, 850, SCIENCE);

	addDefaultBook(library, "Сальвадор Дали", "Дневник одного героя", 1963, 800, BIBLIOGRAPHY);
	addDefaultBook(library, "Георгий Жуков", "Воспоминания и рассуждения", 1969, 900, BIBLIOGRAPHY);
	addDefaultBook(library, "Стефан Цвейг", "Мария Стюарт", 1935, 748, BIBLIOGRAPHY);
	addDefaultBook(library, "Антон Чехов", "Пари", 1888, 1107, BIBLIOGRAPHY);
	addDefaultBook(library, "Дмитрий Горчев", "Жизнь без Карло", 2010, 1000, BIBLIOGRAPHY);
	printf("\nБиблиотека успешно добавлена. Вы можете открыть ее через меню\n");

}

void libraryToFile(LIBRARY& library)
{
	int wantToContinue = WantToContinue();
	char* name = { 0 };
	int choice = 2;
	if (wantToContinue)
	{

		printf("\nВведите 0 для выбора существующего файла, 1 для создания файла: ");
		while (true) {

			static char buf[100];
			scanf("%s", &buf);
			ClearBuffer();
			sscanf(buf, "%d", &choice);
			if (choice < 0 || choice > 1) printf("\nНеверный ввод, попробуйте снова: ");
			else break;
		}
		FILE* file = NULL;
		if (choice == 1)
		{
			file = makeFile();
			printf("\nФайл успешно создан!\n");
		}
		else
		{
			const char* FileName = chooseFileName();
			name = const_cast<char*>(FileName);
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);
			printf("\nСохраняем в файл '%s'....\n", FileName);
			file = fopen(FileName, "a");
		}
		if (file)
		{
			fprintf(file, "%d\n", library.CountOfBooks);
			if (library.CountOfBooks > 0)
			{
				for (int i = 0; i < library.CountOfBooks; i++)
				{
					BOOK book = *library.books[i];
					for (int i = 0; i < sizeof(book.title) / sizeof(book.title[0]); i++)
					{
						if (book.title[i] == ' ') book.title[i] = '_';
					}
					for (int i = 0; i < sizeof(book.author) / sizeof(book.author[0]); i++)
					{
						if (book.author[i] == ' ') book.author[i] = '_';
					}
					fprintf(file, "%s %s %d %d %d\n", book.title, book.author, book.year, book.category, book.price);
				}
				fclose(file);
				printf("\nБиблиотека успешно записана!\n");
			}
			else
			{
				printf("\nБиблиотека пуста! Вы можете добавить в нее книги через меню\n");
			}
		}
		else printf("Файл не найден!");
	}
	else if (wantToContinue != 0) printf("\nНеверный символ!\n");
}

void readBooksFromFile(LIBRARY& library)
{
	setlocale(LC_ALL, "");
	int wantToContinue = WantToContinue();
	if (wantToContinue)
	{
		const char* FileName = chooseFileName();
		printf("\nСчитываем с файла '%s'....\n", FileName);
		FILE* file = fopen(FileName, "rt");
		if (file)
		{
			int CountOfLines = 0;
			fscanf(file, "%d", &CountOfLines);
			if (CountOfLines == 0) printf("\nФайл пуст или поврежден!\n");
			else
			{
				library.capacity += CountOfLines; //3
				for (int i = 0; i < CountOfLines; i++)
				{
					BOOK* book = new BOOK;
					fscanf(file, "%s %s %d %d %d\n", book->title, book->author, &book->year, &book->category, &book->price);
					for (int i = 0; i < 100; i++)
					{
						if (book->title[i] == '_') book->title[i] = ' ';
					}
					for (int i = 0; i < 50; i++)
					{
						if (book->author[i] == '_') book->author[i] = ' ';
					}
					addNewBook(library, book);
				}
				if (library.CountOfBooks > 0) printf("\nФайл успешно переписан в библиотеку. Вы можете открыть ее через меню\n");
				fclose(file);
			}
		}
		else printf("\nФайл не найден!\n");
	}
	else if (wantToContinue != 0) printf("\nНеверный символ!\n");
}

void flushFile()
{
	int wantToContinue = WantToContinue();
	if (wantToContinue)
	{
		const char* FileName = chooseFileName();
		FILE* file = fopen(FileName, "w");
		if (file)
		{
			char NoEmptyFile = '\0';
			fscanf(file, "%c", &NoEmptyFile);
			if (NoEmptyFile)
			{
				fflush(file);
				printf("\nФайл успешно очищен\n");
			}
			else printf("\nФайл уже пустой!\n");
			fclose(file);
		}
		else printf("Файл не найден");
	}
	else if (wantToContinue != 0) printf("\nНеверный символ!\n");
}
void addNewBook(LIBRARY& library, BOOK* book)
{
	if (notInLibrary(library, *book))
	{
		if (library.CountOfBooks <= library.capacity)
		{
			insertBook(library, book);
			if (library.CountOfBooks == library.capacity) enlargeLibrary(library);

		}
		else
		{
			enlargeLibrary(library);
			insertBook(library, book);
		}
	}
}
void addNewBook(LIBRARY& library)
{
	int wantToContinue = WantToContinue();
	if (wantToContinue)
	{
		int prevCount = library.CountOfBooks;
		if (library.CountOfBooks <= library.capacity)
		{
			insertBook(library);
			if (library.CountOfBooks == library.capacity) enlargeLibrary(library);
		}
		else
		{
			enlargeLibrary(library);
			insertBook(library);
		}
		if (prevCount == library.CountOfBooks) printf("\nЭта книга уже есть в библиотеке!\n");
		else printf("\nКнига успешно записана! Теперь вы можете увидеть ее в библиотеке\n");
	}
}

int input()
{
	static char buf[100];
	int choice = 111111111;
	scanf("%s", &buf);
	sscanf(buf, "%d", &choice);
	ClearBuffer();
	return choice;
}

bool notInLibrary(LIBRARY& library, BOOK& book)
{
	for (int i = 0; i < library.CountOfBooks; i++)
	{
		if (strcmp(book.title, (*library.books[i]).title) == 0 && strcmp((*library.books[i]).author, book.author) == 0) return false;
	}
	return true;
}

const char* chooseFileName()
{
	int i = 0;
	cout << '\n';
	while (i < CountOfFiles)
	{
		printf("\t[%d] - %s\n", i + 1, FileNames[i]);
		i++;
	}
	while (true)
	{
		printf("\nВыберите номер файла для действия с ним: ");
		int choice = input();
		if (choice > 0 && choice <= CountOfFiles)
		{
			return FileNames[choice - 1];
			break;
		}
		else printf("\nНеправильный ввод! Пожалуйста, попробуйте снова\n");
	}
}

FILE* makeFile()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("Введите имя будущего файла без .txt и длиной менее 49 символов: ");
	char FileName[54];
	static char buf[54];
	scanf("%s", &buf);
	sscanf(buf, "%[^.]", FileName);
	strcat(FileName, ".txt");
	FILE* file = fopen(FileName, "w");
	printf("\nСохраняем в файл '%s'....\n", FileName);
	FileNames[CountOfFiles] = new char[54];
	strcpy(FileNames[CountOfFiles], FileName);
	CountOfFiles++;
	return file;
}