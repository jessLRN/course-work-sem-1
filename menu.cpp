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
	printf("\n\t[1] ����������� ���������� ����������\n");
	printf("\t[2] ������ ����� �����\n");
	printf("\t[3] ������� ������������ �����\n");
	printf("\t[4] �������� ������� ���������� ���������� � ����\n");
	printf("\t[5] ������� �� ����� ���������� � ����������\n");
	printf("\t[6] ������������� �����\n");
	printf("\t[7] �������� ����������������� ����������\n");
	printf("\t[8] �������� ����������\n");
	printf("\t[9] �������� ����\n");
	printf("\t[0] ����� �� ���������\n");
	
}

void performMenuAction(LIBRARY& library)
{
	printMenu();
	bool badinput = true;
	while (badinput)
	{
		printf("\n������� �������� [0...9]: ");
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
				printf("\n������� �� ������������� ����� ���������!\n");
				exit(0);
				break;
			default:
				printf("\n������ ���� ������� ����� �� 0 �� 10. ���������� �����!\n");
				break;
		}
	} 
}	
