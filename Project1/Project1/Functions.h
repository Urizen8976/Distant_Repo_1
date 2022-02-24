#pragma once
#include <cstdio>
#include <string>
using namespace std;
#pragma warning(disable: 4996)

// const char *fileName, f = fopen(fileName, "w");
// равнозначно const std::string &fileName, f = fopen(fileName.c_str(), "w");
bool createFileWithRandomNumbers(const std::string &fileName, const int numbersCount, const int maxNumberValue)
{
	int x, i; FILE *f;
	f = fopen(fileName.c_str(), "w");
	if (f == NULL) {
		//perror("error opening file in CreateFile");
		return false;
	}
	else {
		for (i = 0; i < numbersCount; i++)
		{
			x = rand() % (maxNumberValue + 1); 
			fprintf(f, "%d ", x);
		}
		fclose(f);
		return true;
	}
}
//Создаёт файл со случайным массивом размера numbersCount и диапазоном значений [0, maxNumberValue].
//Возвращает true, если файл был успешно создан.
//Функция должна быть способна сгенерировать файл размера больше, чем доступная оперативная память.

int fibonacci(int n)
{
	int a = 1, b = 1, buff;
	if (n == 1 || n == 2)
		n = 1;
	else
	{
		for (int i = 2; i < n; i++)
		{
			buff = a + b;
			a = b;
			b = buff;
		}
		n = buff;
	}
	return n;
}

int theNearestHigherFibonacciNumberIndex(const std::string &fileName)
{
	FILE *f;
	int number1 = 0, number2 = 0;
	f = fopen(fileName.c_str(), "r");
	if (f == NULL) {
		perror("error open files");
		exit(1);
	}
	fscanf(f, "%d", &number1);
	int numberOfAscendingSegments = 1;
	while (!feof(f)) 
	{
		fscanf(f, "%d", &number2);
		if (number1 <= number2) 
		{
			number1 = number2;
		}
		else
		{
			number1 = number2;
			numberOfAscendingSegments++;
		}
	}
	fclose(f);
	int count;
	for (count = 1; fibonacci(count) < numberOfAscendingSegments; count++) {};
	return count;
}

void fragmentation(const std::string &fileName, const char* name2, const char* name3, int fibBigNumber, int fibSmallNumber) {
	FILE *f1, *f2, *f3;
	int x1, x2;
	f1 = fopen(fileName.c_str(), "r");
	f2 = fopen(name2, "w");
	f3 = fopen(name3, "w");
	if (f1 == NULL || f2 == NULL || f3 == NULL) {
		perror("error open files");
		exit(1);
	}
	fscanf(f1, "%d", &x1);
	fprintf(f3, "%d ", x1);
	for (int i = 1; i < fibBigNumber && !feof(f1); i++)
	{
		fscanf(f1, "%d", &x2);
		while (!feof(f1) && x1 <= x2)
		{
			x1 = x2;
			fprintf(f3, "%d ", x2);
			fscanf(f1, "%d", &x2);
		}
		fprintf(f3, "%d ", x2);
		x1 = x2;
	}
	fscanf(f1, "%d", &x2);
	while (!feof(f1) && x1 <= x2)
	{
		x1 = x2;
		fprintf(f3, "%d ", x2);
		fscanf(f1, "%d", &x2);
	}
	int amount = 0;
	if (!feof(f1))
		amount++;
	x1 = x2;
	for (int i = 0; !feof(f1); i++)
	{
		fprintf(f2, "%d ", x2);
		fscanf(f1, "%d", &x2);
		if (x1 > x2)
			amount++;
		x1 = x2;
	}
	for (int i = 1; i < fibSmallNumber - amount + 1; i++)
	{
		fprintf(f2, "%d ", -i);
	}
	fclose(f1);
	fclose(f2);
	fclose(f3);
}

void merger(const char* name1, const char* name2, const char* name3) {
	FILE* f1, *f2, *f3;
	int x1, x2, y1, y2;
	f1 = fopen(name1, "w");
	f2 = fopen(name2, "r");
	f3 = fopen(name3, "r");
	if (f1 == NULL || f2 == NULL || f3 == NULL) {
		perror("error open files");
		exit(1);
	}
	fscanf(f2, "%d", &x1);
	fscanf(f3, "%d", &y1);
	while (!feof(f2) && !feof(f3)) {
		if (!feof(f2) && x1 < y1) {
			fprintf(f1, "%d ", x1);
			fscanf(f2, "%d", &x2);

			if (!feof(f3) && (feof(f2) || x1 > x2)) {
				fprintf(f1, "%d ", y1);
				fscanf(f3, "%d", &y2);

				while (!feof(f3) && y1 <= y2) {
					y1 = y2;
					fprintf(f1, "%d ", y1);
					fscanf(f3, "%d", &y2);
				}
				y1 = y2;
			}
			x1 = x2;
		}
		else {
			fprintf(f1, "%d ", y1);
			fscanf(f3, "%d", &y2);

			if (!feof(f2) && y1 > y2) {
				fprintf(f1, "%d ", x1);
				fscanf(f2, "%d", &x2);

				while (!feof(f2) && (x2 == EOF || x1 <= x2)) {
					x1 = x2;
					fprintf(f1, "%d ", x1);
					fscanf(f2, "%d", &x2);
				}
				x1 = x2;				
			}
			y1 = y2;
		}
	}

	fclose(f2);
	f2 = fopen(name2, "w");
    while (!feof(f3))
	{
		fprintf(f2, "%d ", y1);
		fscanf(f3, "%d", &y1);
	}
	
	fclose(f2);
	f2 = fopen(name2, "r");
	fclose(f3);
	f3 = fopen(name3, "w");
	fscanf(f2, "%d", &x1);
	while (!feof(f2))
	{
		fprintf(f3, "%d ", x1);
		fscanf(f2, "%d", &x1);
	}
	
	fclose(f1);
	fclose(f2);
	fclose(f3);
}

void multiphaseSortFile(const std::string &fileName)
{
	FILE *f1;
	f1 = fopen(fileName.c_str(), "r");
	if (f1 == NULL)
	{
		perror("error open file");
		exit(1);
	}
	int index = theNearestHigherFibonacciNumberIndex("file1.txt");
	cout << endl << "theNearestHigherFibonacciNumberIndex: " << index;
	cout << endl << "theNearestHigherFibonacciNumber: " << fibonacci(index);
	int fibSmallNumberIndex = index - 2;
	int fibBigNumberIndex = index - 1;
	if (fibBigNumberIndex > 1)
		fragmentation("file1.txt", "file2.txt", "file3.txt", fibonacci(fibBigNumberIndex), fibonacci(fibSmallNumberIndex));
	int flag = 0;
	while (true)
	{
		//-   
		//small   
		//big 
		if (fibSmallNumberIndex <= 0)
		{
			flag = 3;
			break;
		}
		merger(fileName.c_str(), "file2.txt", "file3.txt");
		fibSmallNumberIndex--;
		if (fibSmallNumberIndex <= 0)
		{
			flag = 1;
			break;
		}
		merger("file2.txt", "file3.txt", fileName.c_str());
		fibSmallNumberIndex--;
		if (fibSmallNumberIndex <= 0)
		{
			flag = 2;
			break;
		}
		merger("file3.txt", fileName.c_str(), "file2.txt");
		fibSmallNumberIndex--;
	}
	fclose(f1);
	FILE *f2, *f3;
	cout << endl << "flag: " << flag;
	int x, y, z, d;
	if (flag == 1) {
		f1 = fopen(fileName.c_str(), "r");
		f2 = fopen("file2.txt", "w");
		fscanf(f1, "%d", &x);
		while (!feof(f1))
		{
			if (x >= 0)
				fprintf(f2, "%d ", x);
			fscanf(f1, "%d", &x);
		}
		fclose(f1);
		fclose(f2);
		f2 = fopen("file2.txt", "r");
		f1 = fopen(fileName.c_str(), "w");
		fscanf(f2, "%d", &y);
		while (!feof(f2))
		{
			fprintf(f1, "%d ", y);
			fscanf(f2, "%d", &y);
		}
		fclose(f1);
		fclose(f2);
	}
	else if (flag == 2) {
		f2 = fopen("file2.txt", "r");
		f1 = fopen(fileName.c_str(), "w");
		fscanf(f2, "%d", &z);
		while (!feof(f2))
		{
			if (z >= 0)
				fprintf(f1, "%d ", z);
			fscanf(f2, "%d", &z);
		}
		fclose(f2);
		fclose(f1);
	}
    else if (flag == 3) {
		f3 = fopen("file3.txt", "r");
		f1 = fopen(fileName.c_str(), "w");
		fscanf(f3, "%d", &d);
		while (!feof(f3))
		{
			if (d >= 0)
				fprintf(f1, "%d ", d);
			fscanf(f3, "%d", &d);
		}
		fclose(f3);
		fclose(f1);
	}
}


bool isFileContainsSortedArray(const std::string &fileName)
{
	bool is_ordered = true;
	FILE *f;
	f = fopen(fileName.c_str(), "r");
	if (f == NULL)
	{
		perror(fileName.c_str());
		getchar();
		exit(1);
	}
	else
	{
		int previous = INT_MIN, x;
		if (fscanf_s(f, "%d", &x) == EOF)
			is_ordered = false;
		while (fscanf_s(f, "%d", &x) != EOF && is_ordered)
		{
			if (x >= previous)
				previous = x;
			else
			{
				is_ordered = false;
			}
		}
	}
	fclose(f);
	if (is_ordered)
		return true;
	else
		return false;
}
//Проверяет массив в файле на упорядоченность.
//Возвращает true, если массив в файле упорядочен.
//Функция должна быть способна проверить файл размера больше, чем доступная оперативная память.