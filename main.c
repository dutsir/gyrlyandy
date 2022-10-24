
#include <stdlib.h> // для перехода на русский язык
#include <stdio.h>


int main()
{
	//открытие файла в режиме чтения
	FILE* file = fopen("input.txt", "r");
	if (file == NULL) return 0;

	// количество герлянд
	int N = 0;
	fscanf(file, "%d", &N);
	// установка ограничения
	if (N <= 0) N = 1;
	if (N > 100) N = 100;

	// размеры герлянд
	int *sizeList = (int*)malloc(N * sizeof(int));
	int MAX = 0; // максимальный размер герлянды
	int sum = 0; // сумма строк для всех герлянд
	// чтение размеров герлянд
	for (int i = 0; i < N; i++) {
		fscanf(file, "%d", &sizeList[i]);
		// поиск максимального размера герлянды
		if (i == 0 || MAX < sizeList[i]) MAX = sizeList[i];
		sum += sizeList[i];
	}
	fclose(file);// закрытие файла
	

	
	int rows = sum * 2 - (N - 2);		// колво строк для всех гирлянд
	int cols = MAX * 2 + 1;	// колво столбцов для всех гирлянд
	// если герлянда шириной 1
	if (rows == 1) rows += 2;

	// инициализация двумерного массива для построения гирлянд
	int** mtrx = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; i++) {
		mtrx[i] = (int*)malloc(cols * sizeof(int));
	}
	// заполнение массива сеткой из символов '.'
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			mtrx[i][j] = '.';


	
	// позиция отрисовки текущей герлянды
	int x = 0;// по ширине
	int y = 0;// по высоте
	// обход каждой герлянды для ее отрисовки в массиве
	for (int g = 0; g < N; g++) {
		int size = sizeList[g];// размер текущей герлянды
		char sz = '#';
		if ((g + 1) % 2 == 0) sz = '*';


		// формирование верхней половины лампы герлянды
		int middle = cols / 2;
		for (int i = y, j = 0; i < y + size + 1; i++, j++) {
			// первый символ лампы герлянды
			if (i == y) {
				mtrx[i][middle] = sz;
				continue;
			}
			mtrx[i][middle-j] = sz;	// символ с левой стороны
			mtrx[i][middle+j] = sz;	// символ с правой стороны
		}

		// формирование нижней половины лампы герлянды
		int part = (size + 1 + y) + size;
		for (int i = size + 1 + y, j = size-1; i < part; i++, j--) {
			mtrx[i][middle-j] = sz;		// символ с левой стороны
			mtrx[i][middle + j] = sz;	// символ с правой стороны
			y = i-1;// позиция, с которой будет нарисованна следующеая герлянда
		}

	}

	// открытие файла для записи
	file = fopen("output.txt", "w");
	// вывод герлянд в файл
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fprintf(file, "%c", mtrx[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);// закрытие файла

	return 0;
}