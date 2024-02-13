﻿/*************************************************************
Практическое занятие №5. Структуры
//динамический массив структур
//поиск
//сортировка
//сохранение в файле
//чтение из файла
*************************************************************/
#define _CRT_SECURE_NO_WARNINGS 
#include "library.h" 
#include <cmath>
#include <cstring>
#include <cstdio>
#include <iostream>

#define	  stop __asm nop	
using namespace std;


void main()
{
	setlocale(LC_ALL, "rus");
	//Используйте структуру BOOK, созданную в предыдущей работе.
	//Для этого достаточно переписать и подключить к проекту файлы
	//book.h и book.cpp

	//Задание 1. Создаем «картотеку».
	//«Картотека» - это массив структур => нужно такой массив создать.
	//Замечание: размер массива придется увеличивать по мере добавления книг =>
	//Каким должен быть такой массив???
	

	//Пользователь должен иметь возможность по своему желанию выполнять
	//разные действия с картотекой => нужно такую возможность ему
	//предоставить: это может выглядеть как вывод "меню" (перечень
	//возможных действий и соответствующих реакций пользователя), например:
	//Распечатать содержимое картотеки (1)
	//Ввести новую книгу (2)
	//Удалить существующую(ие) (3)
	//Записать текущее содержимое картотеки в файл (4)
	//Считать из файла содержимое в картотеку (5)
	//...
	//Выход из программы (...)


	//Реализуйте посредством функций разные возможности работы с картотекой




	//Подсказка1: для файлового ввода/вывода используйте функции fprintf и fscanf
	//(заголовочный файл <cstdio>



	// Подсказка2: удобно в качестве первого данного в файле хранить количество
	// книг в картотеке
	//Если файл существует и его удалось открыть
	//if()
	//{
	//Чтение данных из файла
	//а) считали количество элементов
	//б) создали массив требуемой размерности
	//в) считали данные из файла в массив
	//}
	printf("\nДобро пожаловать в MyLibrary! Пожалуйста, выберите действие:\n");
	LIBRARY library;
	initLibrary(library);
	initFileNames();
	bool end = false;
	while (!end) performMenuAction(library);
	flushLibrary(library);
	deleteFileNames();


	//****************************************************************
	//Задание 2. Предоставьте пользователю возможность выводить перечень книг
	//в определенном порядке => напишите функцию (функции) сортировки массива
	//по любому из полей структуры.
	//Замечание: признак - "по какому полю сортируем" можно ввести с помощью
	//перечисления.

}