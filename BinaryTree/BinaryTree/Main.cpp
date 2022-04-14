#include <iostream>
#include <time.h>
#include "Library.h"

//class "BinaryTree"

int main()
{
	srand(time(0));
	BinaryTree bt;
	for (int i = 0; i < 10; i++)
		bt.InsertNode(i % 10);
	bt.PrintTreeByLevels();
	bt.GetHeight();
	bt.GetVectorOfAllKeys();
	for (int i = 0; i < 9; i++)
		bt.EraseByKey(i % 10);
	BinaryTree bt2 = bt;
	bt.PrintTreeByLevels();
	bt2.PrintTreeByLevels();
	bt2.DeleteSubTree();
	bt2.PrintTreeByLevels();
	std::cout << bt.IsEmpty() << " " << bt2.IsEmpty() << std::endl;
	//bt2 = bt2.CopyTree(bt.GetRoot());
	bt2.PrintTreeByLevels();
	std::cout << bt2.GetHeight() << std::endl;
	std::cout << bt2.GetAmountOfNodes() << std::endl;
	std::cout << bt2.GetMinKey() << std::endl;
	std::cout << bt2.GetMaxKey() << std::endl;
	bt2.InsertNode(7);
	bt2.PrintTreeByLevels();
	bt.EraseByKey(1);
	bt.PrintTreeByLevels();
	std::cout << bt.CheckForBalance() << std::endl;
	std::cout << bt.GetSumOfAllKeys() << std::endl;
	bt.PrintLevel(4); std::cout << std::endl;
	std::vector<int> ans = bt.GetVectorOfAllKeys();
	for (int i : ans)
	std::cout << i << " ";
	std::cout << std::endl;
	bt.PrintLeaves();
	system("pause");
	return 0;
}