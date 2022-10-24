
#include <stdlib.h> // ��� �������� �� ������� ����
#include <stdio.h>


int main()
{
	//�������� ����� � ������ ������
	FILE* file = fopen("input.txt", "r");
	if (file == NULL) return 0;

	// ���������� �������
	int N = 0;
	fscanf(file, "%d", &N);
	// ��������� �����������
	if (N <= 0) N = 1;
	if (N > 100) N = 100;

	// ������� �������
	int *sizeList = (int*)malloc(N * sizeof(int));
	int MAX = 0; // ������������ ������ ��������
	int sum = 0; // ����� ����� ��� ���� �������
	// ������ �������� �������
	for (int i = 0; i < N; i++) {
		fscanf(file, "%d", &sizeList[i]);
		// ����� ������������� ������� ��������
		if (i == 0 || MAX < sizeList[i]) MAX = sizeList[i];
		sum += sizeList[i];
	}
	fclose(file);// �������� �����
	

	
	int rows = sum * 2 - (N - 2);		// ����� ����� ��� ���� �������
	int cols = MAX * 2 + 1;	// ����� �������� ��� ���� �������
	// ���� �������� ������� 1
	if (rows == 1) rows += 2;

	// ������������� ���������� ������� ��� ���������� �������
	int** mtrx = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; i++) {
		mtrx[i] = (int*)malloc(cols * sizeof(int));
	}
	// ���������� ������� ������ �� �������� '.'
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			mtrx[i][j] = '.';


	
	// ������� ��������� ������� ��������
	int x = 0;// �� ������
	int y = 0;// �� ������
	// ����� ������ �������� ��� �� ��������� � �������
	for (int g = 0; g < N; g++) {
		int size = sizeList[g];// ������ ������� ��������
		char sz = '#';
		if ((g + 1) % 2 == 0) sz = '*';


		// ������������ ������� �������� ����� ��������
		int middle = cols / 2;
		for (int i = y, j = 0; i < y + size + 1; i++, j++) {
			// ������ ������ ����� ��������
			if (i == y) {
				mtrx[i][middle] = sz;
				continue;
			}
			mtrx[i][middle-j] = sz;	// ������ � ����� �������
			mtrx[i][middle+j] = sz;	// ������ � ������ �������
		}

		// ������������ ������ �������� ����� ��������
		int part = (size + 1 + y) + size;
		for (int i = size + 1 + y, j = size-1; i < part; i++, j--) {
			mtrx[i][middle-j] = sz;		// ������ � ����� �������
			mtrx[i][middle + j] = sz;	// ������ � ������ �������
			y = i-1;// �������, � ������� ����� ����������� ���������� ��������
		}

	}

	// �������� ����� ��� ������
	file = fopen("output.txt", "w");
	// ����� ������� � ����
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fprintf(file, "%c", mtrx[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);// �������� �����

	return 0;
}