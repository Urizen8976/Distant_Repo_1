#include <iostream>
#include <cmath>
#include "LibraryBT.h"
#include "LibraryST.h"

//class "SearchTree"

int testSearchTreeRec(BinaryTree &tree, const int size, Node &root)
{
	BinaryTree subTree = tree.CopyTree(root);
	int subTreeSize = subTree.GetAmountOfNodes();
	if (subTreeSize > 1) {
		int rootKey = subTree.GetRoot().GetKey();
		int rootLevel = subTree.GetLevelOfNodeByKey(rootKey);

		int firstChildKey;
		if (subTree.GetRoot().HasLeftDescendant())
		{
			firstChildKey = subTree.GetRoot().GetLeftDescendant().GetKey();
		}
		else
		{
			firstChildKey = -1;
		}
		int childsLevel = subTree.GetLevelOfNodeByKey(firstChildKey);


		int secondChildKey = -1;
		if (subTreeSize > 2) {
			if (subTree.GetRoot().HasRightDescendant())
				secondChildKey = subTree.GetRoot().GetRightDescendant().GetKey();
			if (subTree.GetLevelOfNodeByKey(secondChildKey) != childsLevel) {
				secondChildKey = -1;
			}
		}


		if (secondChildKey >= 0 && !(firstChildKey < rootKey && rootKey <= secondChildKey)) {
			return -2;
		}
	}
	if (root.HasLeftDescendant() && testSearchTreeRec(tree, size, root.GetLeftDescendant()) == -2)
		return -2;
	if (root.HasRightDescendant() && testSearchTreeRec(tree, size, root.GetRightDescendant()) == -2)
		return -2;
	return 0;
}

int testSearchTree(SearchTree &tree, const int size)
{
	if (tree.GetAmountOfNodes() != size) {
		return -1;
	}


	std::vector<int> nodesKeys = tree.GetVectorOfAllKeys();

	return testSearchTreeRec(tree, size, tree.GetRoot());
}


bool testSearchTree(int size)
{
	int failedCase = 0;
	SearchTree searchTree;
	std::vector<int> nodesKeys;


	for (int i = 0; i < size; ++i) {
		searchTree.InsertNode(i);
		nodesKeys.push_back(i);
	}


	int index, key;


	while (nodesKeys.size()) {
		if (testSearchTree(searchTree, nodesKeys.size())) {
			failedCase = 2;
			break;
		}


		if (nodesKeys.size()) {
			index = rand() % nodesKeys.size();
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			if (!searchTree.EraseByKey(key)) {
				failedCase = 3;
				break;
			}


			if (testSearchTree(searchTree, nodesKeys.size())) {
				failedCase = 4;
				break;
			}
		}
	}


	if (failedCase || !searchTree.IsEmpty()) {
		if (!failedCase) {
			failedCase = -1;
		}


		std::cout << size << " " << searchTree.GetAmountOfNodes() << std::endl;
		searchTree.PrintTreeByLevels();
		std::cout << std::endl;
		std::cout << std::endl;




	}
	return (failedCase == 0);
}

int testSearchTreeAsBinaryTree(BinaryTree &tree, const int size)
{
	if (tree.GetAmountOfNodes() != size) {
		return -1;
	}


	std::vector<int> nodesKeys = tree.GetVectorOfAllKeys();


	return testSearchTreeRec(tree, size, tree.GetRoot());
}


bool testSearchTreeAsBinaryTree(int size)
{
	int failedCase = 0;
	SearchTree searchTree;
	BinaryTree &searchTreeRef = searchTree;
	std::vector<int> nodesKeys;


	for (int i = 0; i < size; ++i) {
		searchTreeRef.InsertNode(i);
		nodesKeys.push_back(i);
	}


	int index, key;


	while (nodesKeys.size()) {
		if (testSearchTreeAsBinaryTree(searchTreeRef, nodesKeys.size())) {
			failedCase = 2;
			break;
		}


		if (nodesKeys.size()) {
			index = rand() % nodesKeys.size();
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			if (!searchTreeRef.EraseByKey(key)) {
				failedCase = 3;
				break;
			}


			if (testSearchTreeAsBinaryTree(searchTreeRef, nodesKeys.size())) {
				failedCase = 4;
				break;
			}
		}
	}


	if (failedCase || !searchTreeRef.IsEmpty()) {
		if (!failedCase) {
			failedCase = -1;
		}


		std::cout << size << " " << searchTreeRef.GetAmountOfNodes() << std::endl;
		searchTreeRef.PrintTreeByLevels();
		std::cout << std::endl;
		std::cout << std::endl;




	}
	return (failedCase == 0);
}


void testBinaryTree() 
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
	//BinaryTree* btÑopy = &bt2;
	std::cout << "bt2.CopyTree(&bt)" << std::endl;
	bt.PrintTreeByLevels();
	BinaryTree bt3;
	bt3 = bt3.CopyTree(bt.GetRoot());
	bt3.PrintTreeByLevels();
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
	for (int i = 0; i < amountOfX; i++)
		std::cout << "X" << "   ";
	std::cout << std::endl;
	std::vector<int> ans = bt.GetVectorOfAllKeys();
	std::cout << "Vector Of All Keys: " << std::endl;
	for (int i : ans)
		std::cout << i << " ";
	std::cout << std::endl;
	std::cout << "Leaves: " << std::endl;
	bt.PrintLeaves();
}

int main()
{
	
	std::cout << (testSearchTree(10) ? "passed" : "failed") << std::endl;
	std::cout << (testSearchTreeAsBinaryTree(10) ? "passed" : "failed") << std::endl;
	

	system("pause");
	return 0;

	/*
	std::vector <int> d = { 10, 20, 30, 40 };
	std::vector <int> p = { 2, 1, 1, 5 };
	std::vector <int> q = { 1, 10, 1, 1, 10 };
	SearchTree ost = SearchTree::BuildOptimalSearchTree(d, p, q);
	ost.PrintTreeByLevels();
	*/

	/*
	std::vector <int> d = { 10, 20, 30, 40, 50 };
	std::vector <int> p = { 5, 2, 1, 8, 4 };
	std::vector <int> q = { 1, 1, 10, 2, 3, 8 };
	SearchTree ost = SearchTree::BuildOptimalSearchTree(d, p, q);
	ost.PrintTreeByLevels();
	*/

	//testBinaryTree();
	system("pause");
	return 0;
}