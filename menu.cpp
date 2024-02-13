#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include "sort.h"
#include <cmath>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
void printMenu()
{
	printf("\n\t[1] Распечатать содержимое библиотеки\n");
	printf("\t[2] Ввести новую книгу\n");
	printf("\t[3] Удалить существующие книги\n");
	printf("\t[4] Записать текущее содержимое библиотеки в файл\n");
	printf("\t[5] Считать из файла содержимое в библиотеку\n");
	printf("\t[6] Отсортировать книги\n");
	printf("\t[7] Добавить предустановленную библиотеку\n");
	printf("\t[8] Очистить библиотеку\n");
	printf("\t[9] Очистить файл\n");
	printf("\t[0] Выход из программы\n");
	
}

void performMenuAction(LIBRARY& library)
{
	printMenu();
	bool badinput = true;
	while (badinput)
	{
		printf("\nВведите действие [0...9]: ");
		int choice = input();
		switch (choice)
		{
			case 1:
				printBooks(library);
				badinput = false;
				break;
			case 2:
				badinput = false;
				addNewBook(library);
				break;
			case 3:
				badinput = false;
				deleteBooks(library);
				break;
			case 4:
				badinput = false;
				libraryToFile(library);
				//flushLibrary(library);
				break;
			case 5:
				badinput = false;
				readBooksFromFile(library);
				//flushFile();
				break;
			case 6:
				badinput = false;
				sortChoice(library);
				break;
			case 7:
				badinput = false;
				createDefaultLibrary(library);
				break;
			case 8:
				badinput = false;
				flushLibrary(library);
				break;
			case 9:
				badinput = false;
				flushFile();
				break;
			case 0:
				badinput = false;
				printf("\nСпасибо за использование нашей программы!\n");
				exit(0);
				break;
			default:
				printf("\nДолжно быть введено число от 0 до 10. Попробуйте снова!\n");
				break;
		}
	} 
}	
