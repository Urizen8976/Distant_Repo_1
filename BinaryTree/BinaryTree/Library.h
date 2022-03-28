#pragma once
#include <vector>

class Node {
public:
	int m_key;
	Node* m_left;
	Node* m_right;

	Node()
		: m_key(0)
		, m_left(nullptr)
		, m_right(nullptr)
	{
	}

	Node(int key, Node* leftDescendant = nullptr, Node* rightDescendant = nullptr)
		: m_key(key)
		, m_left(leftDescendant)
		, m_right(rightDescendant)
	{
	}

	~Node()
	{
	}

	int GetKey()
	{
		return m_key;
	}

	int GetAmountOfDescendants() //empty
	{	
		int amount = 0;
		if (this && this->m_left)
			amount++;
		if (this && this->m_left)
			amount++;
		return amount;
	}
};


class BinaryTree {
private:
	Node * m_root = nullptr;

private:
	Node * CopyTree(Node* subTreeRoot)
	{
		Node* root = nullptr;
		if (subTreeRoot)
		{
			root = new Node(subTreeRoot->m_key);
			root->m_left = CopyTree(subTreeRoot->m_left);
			root->m_right = CopyTree(subTreeRoot->m_right);
		}

		return root;
	}

	void DeleteSubTree(Node* subTreeRoot)
	{
		if (subTreeRoot)
		{
			DeleteSubTree(subTreeRoot->m_left);
			DeleteSubTree(subTreeRoot->m_right);
			delete subTreeRoot;
		}
	}

public:
	BinaryTree(int key = 0)
		: m_root(new Node(key))
	{
	}

	BinaryTree(const BinaryTree& binaryTree)
	{
		m_root = CopyTree(binaryTree.m_root);
	}

	~BinaryTree() 
	{
		DeleteSubTree(m_root);
	}

	Node* GetRoot()
	{
		return m_root;
	}

	Node* Insert(const int key)
	{
		return Insert(m_root, key);
	}

	Node* Insert(Node* subTreeRoot, const int key)
	{
		if (subTreeRoot == nullptr) {
			if (m_root == nullptr) {
				m_root = new Node(key);
				return m_root;
			}
			else {
				return nullptr;
			}
		}
		if (subTreeRoot->m_left == nullptr) {
			subTreeRoot->m_left = new Node(key);
			return subTreeRoot->m_left;
		}
		else if (subTreeRoot->m_right == nullptr) {
			subTreeRoot->m_right = new Node(key);
			return subTreeRoot->m_right;
		}
		else {
			if (rand() % 2) {
				return Insert(subTreeRoot->m_left, key);
			}
			else {
				return Insert(subTreeRoot->m_right, key);
			}
		}
	}

	bool IsEmpty()
	{
		if (this && this->m_root == nullptr)
			return true;
		else
			return false;
	}

	Node* FindByKey(const int key)
	{
		return FindByKey(m_root, key);
	}

	Node* FindByKey(Node* subTreeRoot, int key)
	{
		if (subTreeRoot)
		{
			if (subTreeRoot->m_key == key)
				return subTreeRoot;
			else
			{
				Node* leftDescendant = FindByKey(subTreeRoot->m_left, key);
				Node* rightDescendant = FindByKey(subTreeRoot->m_right, key);
				if (leftDescendant && leftDescendant->m_key == key)
					return leftDescendant;

				if (rightDescendant && rightDescendant->m_key == key)
					return rightDescendant;

				return nullptr;
			}
		}

		return nullptr;
	}

	Node* FindByIndex(const int index)
	{
		return FindByIndex(m_root, index);
	}

	Node* FindByIndex(Node* subTreeRoot, int index)
	{
		if (index == 0) {
			return subTreeRoot;
		}
		else if (subTreeRoot == nullptr) {
			return nullptr;
		}

		std::vector<Node*> currentLevelNodes;
		currentLevelNodes.push_back(subTreeRoot);

		while (currentLevelNodes.size() != 0 && index >= currentLevelNodes.size()) {
			std::vector<Node*> nextLevelNodes;
			nextLevelNodes.reserve(currentLevelNodes.size() * 2);

			for (Node* node : currentLevelNodes) {
				if (node->m_left) {
					nextLevelNodes.push_back(node->m_left);
				}

				if (node->m_right) {
					nextLevelNodes.push_back(node->m_right);
				}
			}

			index -= currentLevelNodes.size();
			currentLevelNodes.swap(nextLevelNodes);
		}

		if (currentLevelNodes.size() == 0) {
			return nullptr;
		}
		else {
			return currentLevelNodes[index];
		}
	}

	Node* FindParentByKey(const int key)
	{
		return FindParentByKey(m_root, key);
	}

	Node* FindParentByKey(Node* subTreeRoot, int key)
	{
		if (subTreeRoot)
		{
			if (subTreeRoot->m_left && subTreeRoot->m_right)
			{
				if (subTreeRoot->m_left->m_key == key || subTreeRoot->m_right->m_key == key)
					return subTreeRoot;
				else
				{

					Node* m_Left = FindParentByKey(subTreeRoot->m_left, key);
					Node* m_Right = FindParentByKey(subTreeRoot->m_right, key);
					if (m_Left)
						return m_Left;

					if (m_Right)
						return m_Right;
				}
			}
		}

		return nullptr;
	}

	Node* FindParentByIndex(const int index)
	{
		return FindParentByIndex(m_root, index);
	}

	Node* FindParentByIndex(Node* subTreeRoot, int index)
	{
		if (index == 0) {
			return subTreeRoot;
		}
		else if (subTreeRoot == nullptr) {
			return nullptr;
		}

		std::vector<Node*> prevLevelNodes;
		std::vector<Node*> currentLevelNodes;
		currentLevelNodes.push_back(subTreeRoot);


		while (currentLevelNodes.size() != 0 && index >= currentLevelNodes.size()) {
			std::vector<Node*> nextLevelNodes;
			nextLevelNodes.reserve(currentLevelNodes.size() * 2);

			for (Node* node : currentLevelNodes) {
				if (node->m_left) {
					nextLevelNodes.push_back(node->m_left);
				}

				if (node->m_right) {
					nextLevelNodes.push_back(node->m_right);
				}
			}

			index -= currentLevelNodes.size();
			prevLevelNodes = currentLevelNodes;
			currentLevelNodes.swap(nextLevelNodes);
		}

		if (currentLevelNodes.size() == 0) {
			return nullptr;
		}
		else {
			for (Node* i : prevLevelNodes)
				if (i->m_left == currentLevelNodes[index] || i->m_right == currentLevelNodes[index])
					return i;
			return nullptr;
		}
	}

	void FindAndEraseByKey(int key)
	{
		FindAndEraseByKey(m_root, key);
	}

	void FindAndEraseByKey(Node* subTreeRoot, int key)
	{
		Node* nodeToDelete = FindByKey(subTreeRoot, key);
		Erase(nodeToDelete);
	}

	void FindAndEraseByIndex(int index)
	{
		FindAndEraseByIndex(m_root, index);
	}

	void FindAndEraseByIndex(Node* subTreeRoot, int index)
	{
		Node* nodeToDelete = FindByIndex(subTreeRoot, index);
		Erase(nodeToDelete);
	}

	void Erase(Node* nodeToDelete) //empty
	{
		return;
	}

	int GetHeight() //empty
	{
		return;
	}

	int GetAmountOfNodes() //empty
	{
		return;
	}
	int GetMinKey() //empty
	{
		return;
	}

	int GetMaxKey() //empty
	{
		return;
	}

	bool CheckForBalance() //empty
	{
		return;
	}

	int GetSumOfAllKeys() //empty
	{
		return;
	}

	int GetLevelOfNodeByKey() //empty
	{
		return;
	}

	std::vector<int> GetVectorOfAllKeys() //empty
	{
		return;
	}

	void PrintByLevels()
	{
		PrintByLevels(m_root);
	}

	void PrintByLevels(Node *subTreeRoot, const int level = 0)
	{
		using std::cout;
		using std::endl;

		if (subTreeRoot == nullptr) {
			if (subTreeRoot == m_root) {
				cout << "Tree is empty" << endl;
			}
			return;
		}

		PrintByLevels(subTreeRoot->m_right, level + 1);

		for (int i = 0; i < level; i++)
			cout << "   ";
		cout << subTreeRoot->m_key << endl;

		PrintByLevels(subTreeRoot->m_left, level + 1);
	}

	void PrintLevel(const int level)
	{
		PrintLevel(m_root, level, 0);
	}

	void PrintLevel(Node* subTreeRoot, const int level, const int currentLevel = 0)
	{
		using std::cout;
		using std::endl;

		if (subTreeRoot == nullptr) {
			if (subTreeRoot == m_root) {
				cout << "Tree is empty" << endl;
			}
			return;
		}

		if (currentLevel == level) {
			cout << subTreeRoot->m_key << "   ";
		}
		else if (currentLevel < level) {
			PrintLevel(subTreeRoot->m_left, level, currentLevel + 1);
			PrintLevel(subTreeRoot->m_right, level, currentLevel + 1);
		}
	}

	void PrintLeaves() //empty
	{
		return;
	}

	void operator=(const BinaryTree& binaryTree)
	{
		if (&binaryTree == this)
		{
			return;
		}
		if (m_root)
		{
			delete m_root;
		}
		CopyTree(binaryTree.m_root);
	}
};