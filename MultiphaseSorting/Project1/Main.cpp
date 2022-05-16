#include <iostream>
#include <fstream>
#include "Functions.h"
using namespace std;

int createAndSortFile(const std::string &fileName, const int numbersCount, const int maxNumberValue)
{
	if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
		return -1;
	}

	multiphaseSortFile(fileName.c_str()); // Вызов вашей функции сортировки

	if (!isFileContainsSortedArray(fileName)) {
		return -2;
	}

	return 1;
}

int main()
{
	string fileName = "file1.txt";
	int numbersCount, maxNumberValue;
	cout << "numbersCount: ";
	cin >> numbersCount;
	cout << endl << "maxNumberValue: ";
	cin >> maxNumberValue;
	cout << endl << "createFileWithRandomNumbers: ";

	switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
	case 1:
		cout << endl << "Test passed.";
		break;

	case -1:
		cout << endl << "Test failed: can't create file.";
		break;

	case -2:
		cout << endl << "Test failed: file isn't sorted.";
		break;
	}

	cout << endl;
	system("pause");
	return 0;
}

