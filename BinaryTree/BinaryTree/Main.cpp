#include <iostream>
#include "Library.h"

//class "BinaryTree"

int main()
{
	int s[9] = { 11,15,19,7,2,8,10,12,18 };
	BinaryTree tree(13);
	for (int i = 0; i < 9; i++) { tree.Insert(s[i]); }
	tree.Print();
	system("pause");
	return 0;
}