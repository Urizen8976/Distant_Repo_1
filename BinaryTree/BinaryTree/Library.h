#pragma once
#include <vector>
#include <assert.h>
#include <iostream>

class Node {
private:
	int m_key;

public:
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

	int GetAmountOfDescendants()
	{	
		int amount = 0;
		if (m_left)
			amount++;
		if (m_right)
			amount++;
		return amount;
	}
};


class BinaryTree {
private:
	Node * m_root = nullptr;


public:
	Node * CopyTree(Node* subTreeRoot)
	{
		Node* root = nullptr;
		if (subTreeRoot)
		{
			root = new Node(subTreeRoot->GetKey());
			root->m_left = CopyTree(subTreeRoot->m_left);
			root->m_right = CopyTree(subTreeRoot->m_right);
		}

		return root;
	}

	BinaryTree() = default;
	
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
		if (this->m_root == nullptr)
		{
			assert(false && "Ошибка: Попытка получить корень пустого дерева!");
			throw std::runtime_error("Ошибка: Попытка получить корень пустого дерева!");
		}
		return m_root;
	}

	void DeleteSubTree() //Сlearing the tree (deleting all nodes)
	{
		DeleteSubTree(m_root);
	}

	void DeleteSubTree(Node* subTreeRoot)
	{
		if (subTreeRoot)
		{
			DeleteSubTree(subTreeRoot->m_left);
			DeleteSubTree(subTreeRoot->m_right);
			delete subTreeRoot;
			if (subTreeRoot == m_root) //do not forget about "subTreeRoot == m_root" case
				m_root = nullptr;
		}
	}

	bool IsEmpty()
	{
		if (this->m_root == nullptr)
			return true;
		else
			return false;
	}

	int GetHeight()
	{
		return GetHeight(m_root);
	}

	int GetHeight(Node* subTreeRoot)
	{
		int height = 0;
		if (subTreeRoot == nullptr)
			return height;

		std::vector<Node*> currentLevelNodes;
		currentLevelNodes.push_back(subTreeRoot);

		while (currentLevelNodes.size() != 0)
		{
			height++;
			std::vector<Node*> nextLevelNodes;
			nextLevelNodes.reserve(currentLevelNodes.size() * 2);

			for (Node* node : currentLevelNodes)
			{
				if (node->m_left)
				{
					nextLevelNodes.push_back(node->m_left);
				}

				if (node->m_right) {
					nextLevelNodes.push_back(node->m_right);
				}
			}

			currentLevelNodes.swap(nextLevelNodes);
		}

		return height;
	}

	int GetAmountOfNodes()
	{
		return GetAmountOfNodes(m_root);
	}

	int GetAmountOfNodes(Node* subTreeRoot)
	{
		int amountOfNodes = 0;
		if (subTreeRoot)
		{
			amountOfNodes++;
			amountOfNodes += GetAmountOfNodes(subTreeRoot->m_left);
			amountOfNodes += GetAmountOfNodes(subTreeRoot->m_right);
		}

		return amountOfNodes;
	}

	int GetMaxKey()
	{
		return GetMaxKey(m_root);
	}

	int GetMaxKey(Node* subTreeRoot)
	{
		if (subTreeRoot == nullptr)
		{
			return 0;
		}

		int subTreeRootMaxKey = subTreeRoot->GetKey();
		if (subTreeRoot->m_left)
		{
			int localMaxKey = GetMaxKey(subTreeRoot->m_left);
			if (subTreeRootMaxKey < localMaxKey)
				subTreeRootMaxKey = localMaxKey;
		}

		if (subTreeRoot->m_right)
		{
			int localMaxKey = GetMaxKey(subTreeRoot->m_right);
			if (subTreeRootMaxKey < localMaxKey)
				subTreeRootMaxKey = localMaxKey;
		}

		return subTreeRootMaxKey;
	}

	int GetMinKey()
	{
		return GetMinKey(m_root);
	}

	int GetMinKey(Node* subTreeRoot)
	{
		if (subTreeRoot == nullptr)
		{
			return 0;
		}

		int subTreeRootMinKey = subTreeRoot->GetKey();
		if (subTreeRoot->m_left)
		{
			int localMinKey = GetMinKey(subTreeRoot->m_left);
			if (subTreeRootMinKey > localMinKey)
				subTreeRootMinKey = localMinKey;
		}

		if (subTreeRoot->m_right)
		{
			int localMinKey = GetMinKey(subTreeRoot->m_right);
			if (subTreeRootMinKey > localMinKey)
				subTreeRootMinKey = localMinKey;
		}

		return subTreeRootMinKey;
	}

	Node* InsertNode(const int key)
	{
		return InsertNode(m_root, key);
	}

	Node* InsertNode(Node* subTreeRoot, const int key)
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
				return InsertNode(subTreeRoot->m_left, key);
			}
			else {
				return InsertNode(subTreeRoot->m_right, key);
			}
		}
	}

    
	Node* FindByKey(const int key)
	{
		return FindByKey(m_root, key);
	}

	Node* FindByKey(Node* subTreeRoot, int key)
	{
		if (subTreeRoot)
		{
			if (subTreeRoot->GetKey() == key)
				return subTreeRoot;
			else
			{
				Node* leftDescendant = FindByKey(subTreeRoot->m_left, key);
				Node* rightDescendant = FindByKey(subTreeRoot->m_right, key);
				if (leftDescendant && leftDescendant->GetKey() == key)
					return leftDescendant;

				if (rightDescendant && rightDescendant->GetKey() == key)
					return rightDescendant;

				return nullptr;
			}
		}

		return nullptr;
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
				if (subTreeRoot->m_left->GetKey() == key || subTreeRoot->m_right->GetKey() == key)
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

	bool EraseByKey(int key)
	{
		return EraseByKey(m_root, key);
	}

	bool EraseByKey(Node* subTreeRoot, int key)
	{
		Node* nodeToDelete = FindByKey(subTreeRoot, key);
		return Erase(nodeToDelete);
	}

	bool Erase(Node* nodeToDelete)
	{
		if (nodeToDelete->m_left == nullptr && nodeToDelete->m_right == nullptr)
		{
			Node* parent = FindParentByKey(nodeToDelete->GetKey());

			if (parent && parent->m_left == nodeToDelete)
				parent->m_left = nullptr;

			if (parent && parent->m_right == nodeToDelete)
				parent->m_right = nullptr;

			if (!parent)
				m_root = nullptr;

			delete nodeToDelete;

			return true;
		}

		if (nodeToDelete->m_left == nullptr && nodeToDelete->m_right != nullptr)
		{
			Node* parent = FindParentByKey(nodeToDelete->GetKey());

			if (parent && parent->m_left == nodeToDelete)
				parent->m_left = nodeToDelete->m_right;

			if (parent && parent->m_right == nodeToDelete)
				parent->m_right = nodeToDelete->m_right;

			if (!parent)
				m_root = nodeToDelete->m_left;

			delete nodeToDelete;

			return true;
		}

		if (nodeToDelete->m_left != nullptr && nodeToDelete->m_right == nullptr)
		{
			Node* parent = FindParentByKey(nodeToDelete->GetKey());

			if (parent && parent->m_left == nodeToDelete)
				parent->m_left = nodeToDelete->m_left;

			if (parent && parent->m_right == nodeToDelete)
				parent->m_right = nodeToDelete->m_left;

			if (!parent)
				m_root = nodeToDelete->m_left;

			delete nodeToDelete;

			return true;
		}

		if (nodeToDelete->m_left && nodeToDelete->m_right)
		{
			Node* parent = FindParentByKey(nodeToDelete->GetKey());
			if (parent)
			{
				if (parent->m_left == nodeToDelete)
				{
					Node* rightDescendant = nodeToDelete->m_right;
					Node* leftDescendant = nodeToDelete->m_left;
					delete nodeToDelete;
					parent->m_left = leftDescendant;
					Node* parentOfLeaf = leftDescendant;
					while (parentOfLeaf->m_left != nullptr)
						parentOfLeaf = parentOfLeaf->m_left;
					parentOfLeaf->m_left = rightDescendant;
					return true;
				}
				else if (parent->m_right == nodeToDelete)
				{
					Node* rightDescendant = nodeToDelete->m_right;
					Node* leftDescendant = nodeToDelete->m_left;
					delete nodeToDelete;
					parent->m_right = leftDescendant;
					Node* parentOfLeaf = leftDescendant;
					while (parentOfLeaf->m_left != nullptr)
						parentOfLeaf = parentOfLeaf->m_left;
					parentOfLeaf->m_left = rightDescendant;
					return true;
				}
			}
			else
			{
				Node* rightDescendant = nodeToDelete->m_right;
				Node* leftDescendant = nodeToDelete->m_left;
				delete nodeToDelete;
				m_root = leftDescendant;
				Node* parentOfLeaf = m_root;
				while (parentOfLeaf->m_left != nullptr)
					parentOfLeaf = parentOfLeaf->m_left;
				parentOfLeaf->m_left = rightDescendant;
				return true;
			}
		}
		return false;
	}

	bool CheckForBalance() 
	{
		return CheckForBalance(m_root);
	}

	bool CheckForBalance(Node* subTreeRoot)
	{
		if (subTreeRoot == nullptr)
			return true;

		if (abs(GetHeight(subTreeRoot->m_left) - GetHeight(subTreeRoot->m_right)) <= 1 && CheckForBalance(subTreeRoot->m_left) && CheckForBalance(subTreeRoot->m_right))
			return true;
		else
			return false;
	}

	int GetSumOfAllKeys() 
	{
		return GetSumOfAllKeys(m_root);
	}

	int GetSumOfAllKeys(Node* subTreeRoot)
	{
		if (subTreeRoot == nullptr) {
			return -1;
		}

		int sum = 0;
		std::vector<Node*> currentLevelNodes;
		currentLevelNodes.push_back(subTreeRoot);
		sum += subTreeRoot->GetKey();

		while (currentLevelNodes.size() != 0)
		{
			std::vector<Node*> nextLevelNodes;
			nextLevelNodes.reserve(currentLevelNodes.size() * 2);

			for (Node* node : currentLevelNodes) {
				if (node->m_left) {
					nextLevelNodes.push_back(node->m_left);
					sum += node->m_left->GetKey();
				}

				if (node->m_right) {
					nextLevelNodes.push_back(node->m_right);
					sum += node->m_right->GetKey();
				}
			}

			currentLevelNodes.swap(nextLevelNodes);
		}

		return sum;
	}

	int GetLevelOfNodeByKey(int key) 
	{
		return GetLevelOfNodeByKey(m_root, key);
	}

	int GetLevelOfNodeByKey(Node* subTreeRoot, int key)
	{
		if (subTreeRoot == nullptr) {
			return -1;
		}

		if (subTreeRoot->GetKey() == key)
			return 0;

		int h = GetHeight(subTreeRoot);
		std::vector<Node*> currentLevelNodes;
		currentLevelNodes.push_back(subTreeRoot);

		for (int i = 0; i < h; i++)
		{
			std::vector<Node*> nextLevelNodes;
			nextLevelNodes.reserve(currentLevelNodes.size() * 2);

			for (Node* node : currentLevelNodes) {
				if (node->m_left) {
					nextLevelNodes.push_back(node->m_left);
					if (node->m_left->GetKey() == key)
						return i + 1;
				}

				if (node->m_right) {
					nextLevelNodes.push_back(node->m_right);
					if (node->m_right->GetKey() == key)
						return i + 1;
				}
			}

			currentLevelNodes.swap(nextLevelNodes);
		}

		return -1;
	}

	std::vector<int> GetVectorOfAllKeys() 
	{
		return GetVectorOfAllKeys(m_root);
	}

	std::vector<int> GetVectorOfAllKeys(Node* subTreeRoot)
	{
		if (subTreeRoot == nullptr)
			return std::vector<int>();

		std::vector<int> keys;
		std::vector<Node*> currentLevelNodes;
		currentLevelNodes.push_back(subTreeRoot);
		keys.push_back(subTreeRoot->GetKey());

		while (currentLevelNodes.size() != 0)
		{
			std::vector<Node*> nextLevelNodes;
			nextLevelNodes.reserve(currentLevelNodes.size() * 2);

			for (Node* node : currentLevelNodes) {
				if (node->m_left) {
					nextLevelNodes.push_back(node->m_left);
					keys.push_back(node->m_left->GetKey());
				}

				if (node->m_right) {
					nextLevelNodes.push_back(node->m_right);
					keys.push_back(node->m_right->GetKey());
				}
			}

			currentLevelNodes.swap(nextLevelNodes);
		}

		return keys;
	}

	void PrintTreeByLevels()
	{
		PrintTreeByLevels(m_root);
	}

	void PrintTreeByLevels(Node *subTreeRoot, const int level = 0)
	{
		using std::cout;
		using std::endl;

		if (subTreeRoot == nullptr) {
			if (subTreeRoot == m_root) {
				cout << "Tree is empty" << endl;
			}
			return;
		}

		PrintTreeByLevels(subTreeRoot->m_right, level + 1);

		for (int i = 0; i < level; i++)
			cout << "   ";
		cout << subTreeRoot->GetKey() << endl;

		PrintTreeByLevels(subTreeRoot->m_left, level + 1);
	}

	void PrintLevel(int &amountOfX, const int level)
	{
		PrintLevel(m_root, amountOfX, level, 0);
	}

	void PrintLevel(Node* subTreeRoot, int &amountOfX, const int level, const int currentLevel = 0)
	{
		using std::cout;
		using std::endl;

		if (subTreeRoot == nullptr) {
			if (subTreeRoot == m_root)
				cout << "Tree is empty" << endl;
			return;
		}

		if (currentLevel == level) {
			cout << subTreeRoot->GetKey() << "   ";
			++amountOfX;
		}
		else if (currentLevel < level) {
			PrintLevel(subTreeRoot->m_left, amountOfX, level, currentLevel + 1);
			PrintLevel(subTreeRoot->m_right, amountOfX, level, currentLevel + 1);
		}
	}

	void PrintLeaves() 
	{
		return PrintLeaves(m_root);
	}

	void PrintLeaves(Node* subTreeRoot)
	{
		if (subTreeRoot == nullptr)
			return;
		if (subTreeRoot->m_left == nullptr && subTreeRoot->m_right == nullptr)
			std::cout << subTreeRoot->GetKey() << " ";
		else
		{
			PrintLeaves(subTreeRoot->m_left);
			PrintLeaves(subTreeRoot->m_right);
		}
	}

	BinaryTree operator=(const BinaryTree& binaryTree)
	{
		if (&binaryTree == this) 
			return *this;
		DeleteSubTree(m_root);
		m_root = CopyTree(binaryTree.m_root);
		return *this;
	}
};