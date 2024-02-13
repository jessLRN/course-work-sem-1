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
		printf("\n���������� ������� �������.\n");
	}
	else printf("\n���������� ��� �����!\n");
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
	if (library.CountOfBooks == 0) printf("\n���������� �����! �� ������ �������� ����� ����� ����\n\n");
	else
	{
		while (true)
		{
			printf("\n���� �� ������ ������� ������ ��������� ����, ������� 0; ��� ����� ������������� ������, ������� 1: ");
			int choice = input();
			if (choice == 0)
			{
				printf("\n��������� ����:\n\n");
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
			else printf("\n������������ ����! ����������, ���������� �����\n");
		}
	}
}
void printTitles(LIBRARY& library)
{
	if (library.CountOfBooks > 0)
	{
		printf("������ ����, �������� � ����������:\n");
		for (int i = 0; i < library.CountOfBooks; i++) printf("\t[%d] %s\n", i + 1, (*library.books[i]).title);
	}
	else printf("\n���������� �����!\n");
}



int WantToContinue()
{
	while (true)
	{
		printf("\n�� ������������� ������ ����������?\n");
		printf("������� 1, ��� �����������, 0 ��� ������: ");
		int choice = input();
		if (choice == 1) return 1;
		else if (choice == 0) return 0;
		else printf("������������ ����! ����������, ���������� ������\n");
	}
}

void deleteBook(LIBRARY& library)
{
	//int wantToContinue = WantToContinue();
	while (true)
	{
		if (library.CountOfBooks > 0)
		{
			printf("��������, ����������, �����, ������� �� ������ �������:\n\n");
			printTitles(library);
			printf("\n����� ����� ��� ��������:\n> ");
			int choice = input();
			if (choice > 0 && choice <= library.CountOfBooks)
			{
				for (int i = choice - 1; i < library.CountOfBooks; i++) library.books[i] = library.books[i + 1];
				library.CountOfBooks--;
				printf("\n�������� ������ �������! ������ ������ ���� �������� ���: \n\n");
				printTitles(library);
				break;
			}
			else
			{
				printf("\n����� ��� ����� ������� ���! ����������, ���������� ������\n");
			}
		}
		else
		{
			printf("\n���������� �����! �� ������ �������� � ��� ����� ����� ����\n");
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
			printf("���� �� ������ ������� ���� �����, ������� 0; �������� ���� - 1: ");
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
						printf("\n������ ��������� ��� ��������: ");
						int choice1 = input();
						printf("\n����� ��������� ��� ��������: ");
						int choice2 = input();
						if (choice1 > choice2) std::swap(choice1, choice2);
						if (choice1 > 0 && choice1 <= library.CountOfBooks && choice2 > 0 && choice2 <= library.CountOfBooks)
						{

							for (int i = 0; i < choice2 - choice1 + 1; i++)
							{
								library.CountOfBooks--;
								library.books[i + choice1 - 1] = library.books[i + choice2];
							}

							printf("\n�������� ������ �������! ������ ������ ���� �������� ���: \n\n");
							printTitles(library);
							break;
						}
						else
						{
							printf("\n\n����� ��� ����� ������� ���! ����������, ���������� ������\n");
						}
					}
					else
					{
						printf("\n���������� �����! �� ������ �������� � ��� ����� ����� ����\n");
						break;
					}
				}
				if (library.CountOfBooks > 0) printf("\n�����(�) ������� �������(�)!\n");
				break;
			}
			else if (wantToContinue != 0) printf("\n�������� ����! ����������, ���������� ������\n");
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
	addDefaultBook(library, "���� ����, ������� ������", "���������� �������", 1928, 991, CLASSICS);
	addDefaultBook(library, "����� �����", "������ � 6", 1892, 600, CLASSICS);
	addDefaultBook(library, "������ ���������", "������ � ����", 1952, 1315, CLASSICS);
	addDefaultBook(library, "���� ������", "����� ����", 1906, 653, CLASSICS);
	addDefaultBook(library, "������ �������", "����� ���", 1940, 1201, CLASSICS);

	addDefaultBook(library, "���� Z. �����������", "��� �������", 2000, 280, POST_MODERN);
	addDefaultBook(library, "���� ��������", "������� ��� ���������", 1973, 339, POST_MODERN);
	addDefaultBook(library, "������ �. �������", "����� � ���������� � ���-������", 1971, 170, POST_MODERN);
	addDefaultBook(library, "���� ����� �����", "������������ ��������", 1991, 611, POST_MODERN);
	addDefaultBook(library, "������ ������", "������-22", 1961, 1000, POST_MODERN);

	addDefaultBook(library, "����� ���", "������� ������ � ������������ ��������", 1934, 500, SCIENCE);
	addDefaultBook(library, "����� ������", "��������", 1987, 304, SCIENCE);
	addDefaultBook(library, "������ ������", "���� ��� ��������", 1994, 200, SCIENCE);
	addDefaultBook(library, "������ ������", "����� - ���� �����", 1930, 1200, SCIENCE);
	addDefaultBook(library, "��� ����������", "������ ������", 1975, 850, SCIENCE);

	addDefaultBook(library, "��������� ����", "������� ������ �����", 1963, 800, BIBLIOGRAPHY);
	addDefaultBook(library, "������� �����", "������������ � �����������", 1969, 900, BIBLIOGRAPHY);
	addDefaultBook(library, "������ �����", "����� ������", 1935, 748, BIBLIOGRAPHY);
	addDefaultBook(library, "����� �����", "����", 1888, 1107, BIBLIOGRAPHY);
	addDefaultBook(library, "������� ������", "����� ��� �����", 2010, 1000, BIBLIOGRAPHY);
	printf("\n���������� ������� ���������. �� ������ ������� �� ����� ����\n");

}

void libraryToFile(LIBRARY& library)
{
	int wantToContinue = WantToContinue();
	char* name = { 0 };
	int choice = 2;
	if (wantToContinue)
	{

		printf("\n������� 0 ��� ������ ������������� �����, 1 ��� �������� �����: ");
		while (true) {

			static char buf[100];
			scanf("%s", &buf);
			ClearBuffer();
			sscanf(buf, "%d", &choice);
			if (choice < 0 || choice > 1) printf("\n�������� ����, ���������� �����: ");
			else break;
		}
		FILE* file = NULL;
		if (choice == 1)
		{
			file = makeFile();
			printf("\n���� ������� ������!\n");
		}
		else
		{
			const char* FileName = chooseFileName();
			name = const_cast<char*>(FileName);
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);
			printf("\n��������� � ���� '%s'....\n", FileName);
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
				printf("\n���������� ������� ��������!\n");
			}
			else
			{
				printf("\n���������� �����! �� ������ �������� � ��� ����� ����� ����\n");
			}
		}
		else printf("���� �� ������!");
	}
	else if (wantToContinue != 0) printf("\n�������� ������!\n");
}

void readBooksFromFile(LIBRARY& library)
{
	setlocale(LC_ALL, "");
	int wantToContinue = WantToContinue();
	if (wantToContinue)
	{
		const char* FileName = chooseFileName();
		printf("\n��������� � ����� '%s'....\n", FileName);
		FILE* file = fopen(FileName, "rt");
		if (file)
		{
			int CountOfLines = 0;
			fscanf(file, "%d", &CountOfLines);
			if (CountOfLines == 0) printf("\n���� ���� ��� ���������!\n");
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
				if (library.CountOfBooks > 0) printf("\n���� ������� ��������� � ����������. �� ������ ������� �� ����� ����\n");
				fclose(file);
			}
		}
		else printf("\n���� �� ������!\n");
	}
	else if (wantToContinue != 0) printf("\n�������� ������!\n");
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
				printf("\n���� ������� ������\n");
			}
			else printf("\n���� ��� ������!\n");
			fclose(file);
		}
		else printf("���� �� ������");
	}
	else if (wantToContinue != 0) printf("\n�������� ������!\n");
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
		if (prevCount == library.CountOfBooks) printf("\n��� ����� ��� ���� � ����������!\n");
		else printf("\n����� ������� ��������! ������ �� ������ ������� �� � ����������\n");
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
		printf("\n�������� ����� ����� ��� �������� � ���: ");
		int choice = input();
		if (choice > 0 && choice <= CountOfFiles)
		{
			return FileNames[choice - 1];
			break;
		}
		else printf("\n������������ ����! ����������, ���������� �����\n");
	}
}

FILE* makeFile()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("������� ��� �������� ����� ��� .txt � ������ ����� 49 ��������: ");
	char FileName[54];
	static char buf[54];
	scanf("%s", &buf);
	sscanf(buf, "%[^.]", FileName);
	strcat(FileName, ".txt");
	FILE* file = fopen(FileName, "w");
	printf("\n��������� � ���� '%s'....\n", FileName);
	FileNames[CountOfFiles] = new char[54];
	strcpy(FileNames[CountOfFiles], FileName);
	CountOfFiles++;
	return file;
}