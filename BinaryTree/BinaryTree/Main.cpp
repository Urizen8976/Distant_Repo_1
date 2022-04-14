#include <iostream>
#include <cmath>
#include "Library.h"

//class "BinaryTree"

int main()
{
	BinaryTree bt;
	for (int i = 0; i < 10; i++)
		bt.InsertNode(i % 10);
	bt.PrintTreeByLevels();
	std::cout << "Height: " << bt.GetHeight() << std::endl;
	bt.GetVectorOfAllKeys();
	for (int i = 0; i < 3; i++)
		if (bt.EraseByKey(i % 10) == true)
			std::cout << "Node '" << i << "' erased successfully" << std::endl;
	BinaryTree bt2 = bt;
	bt.PrintTreeByLevels();
	bt2.PrintTreeByLevels();
	bt2.DeleteSubTree();
	bt2.PrintTreeByLevels();
	if (bt.IsEmpty() == true)
		std::cout << "BinaryTree is Empty" << std::endl;
	else
		std::cout << "BinaryTree is not Empty" << std::endl;
	if (bt2.IsEmpty() == true)
		std::cout << "BinaryTree is Empty" << std::endl;
	else
		std::cout << "BinaryTree is not Empty" << std::endl;
	//bt2 = bt2.CopyTree(bt.GetRoot());
	bt2.PrintTreeByLevels();
	std::cout << "Height: " << bt2.GetHeight() << std::endl;
	std::cout << "Amount Of Nodes: " << bt2.GetAmountOfNodes() << std::endl;
	if (bt2.GetMinKey() == 0)
		std::cout << "BinaryTree is Empty" << std::endl;
	else
		std::cout << "Min Key: " << bt2.GetMinKey() << std::endl;
	if (bt2.GetMaxKey() == 0)
		std::cout << "BinaryTree is Empty" << std::endl;
	else
		std::cout << "Max Key: " << bt2.GetMaxKey() << std::endl;
	bt2.InsertNode(7);
	bt2.PrintTreeByLevels();
	std::cout << std::endl;
	bt.EraseByKey(5);
	bt.PrintTreeByLevels();
	if (bt.CheckForBalance() == 0)
		std::cout << "BinaryTree is not balanced" << std::endl;
	else
		std::cout << "BinaryTree is balanced" << std::endl;
	std::cout << "Sum Of All Keys: " << bt.GetSumOfAllKeys() << std::endl;
	int amountOfX = 0;
	std::cout << "Level: " << std::endl; bt.PrintLevel(amountOfX, 3);
	amountOfX = (int)pow(2, 3) - amountOfX;
	for(int i = 0; i < amountOfX; i++)
	    std::cout << "X" << "   ";
	std::cout << std::endl;
	std::vector<int> ans = bt.GetVectorOfAllKeys();
	std::cout << "Vector Of All Keys: " << std::endl;
	for (int i : ans)
	std::cout << i << " ";
	std::cout << std::endl;
	std::cout << "Leaves: " << std::endl;
	bt.PrintLeaves();
	system("pause");
	return 0;
}