#pragma once
#include <vector>
#include <assert.h>
#include <iostream>

class Node {
private:
	int m_key;

public:
	Node * m_left;
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
protected: 
	Node * m_root = nullptr;


private:
	Node * CopyTreePrivate(Node* subTreeRoot)
	{
		Node* root = nullptr;
		if (subTreeRoot)
		{
			root = new Node(subTreeRoot->GetKey());
			root->m_left = CopyTreePrivate(subTreeRoot->m_left);
			root->m_right = CopyTreePrivate(subTreeRoot->m_right);
		}

		return root;
	}

	void DeleteSubTreePrivate(Node* subTreeRoot)
	{
		if (subTreeRoot)
		{
			DeleteSubTreePrivate(subTreeRoot->m_left);
			DeleteSubTreePrivate(subTreeRoot->m_right);
			delete &subTreeRoot;
			if (subTreeRoot == m_root) //do not forget about "subTreeRoot == m_root" case
				m_root = nullptr;
		}
	}

	int GetHeightPrivate(Node* const subTreeRoot)
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

	int GetAmountOfNodesPrivate(Node* const subTreeRoot)
	{
		int amountOfNodes = 0;
		if (subTreeRoot)
		{
			amountOfNodes++;
			amountOfNodes += GetAmountOfNodesPrivate(subTreeRoot->m_left);
			amountOfNodes += GetAmountOfNodesPrivate(subTreeRoot->m_right);
		}

		return amountOfNodes;
	}

	int GetMaxKeyPrivate(Node* const subTreeRoot)
	{
		if (subTreeRoot == nullptr)
		{
			return 0;
		}

		int subTreeRootMaxKey = subTreeRoot->GetKey();
		if (subTreeRoot->m_left)
		{
			int localMaxKey = GetMaxKeyPrivate(subTreeRoot->m_left);
			if (subTreeRootMaxKey < localMaxKey)
				subTreeRootMaxKey = localMaxKey;
		}

		if (subTreeRoot->m_right)
		{
			int localMaxKey = GetMaxKeyPrivate(subTreeRoot->m_right);
			if (subTreeRootMaxKey < localMaxKey)
				subTreeRootMaxKey = localMaxKey;
		}

		return subTreeRootMaxKey;
	}

	int GetMinKeyPrivate(Node* const subTreeRoot)
	{
		if (subTreeRoot == nullptr)
		{
			return 0;
		}

		int subTreeRootMinKey = subTreeRoot->GetKey();
		if (subTreeRoot->m_left)
		{
			int localMinKey = GetMinKeyPrivate(subTreeRoot->m_left);
			if (subTreeRootMinKey > localMinKey)
				subTreeRootMinKey = localMinKey;
		}

		if (subTreeRoot->m_right)
		{
			int localMinKey = GetMinKeyPrivate(subTreeRoot->m_right);
			if (subTreeRootMinKey > localMinKey)
				subTreeRootMinKey = localMinKey;
		}

		return subTreeRootMinKey;
	}

	Node* InsertNodePrivate(Node* const subTreeRoot, const int key)
	{
		if (subTreeRoot == nullptr)
		{
			if (m_root == nullptr)
			{
				m_root = new Node(key);
				return m_root;
			}
			else
			{
				return nullptr;
			}
		}
		if (subTreeRoot->m_left == nullptr)
		{
			subTreeRoot->m_left = new Node(key);
			return subTreeRoot->m_left;
		}
		else if (subTreeRoot->m_right == nullptr)
		{
			subTreeRoot->m_right = new Node(key);
			return subTreeRoot->m_right;
		}
		else
		{
			if (rand() % 2)
			{
				return InsertNodePrivate(subTreeRoot->m_left, key);
			}
			else
			{
				return InsertNodePrivate(subTreeRoot->m_right, key);
			}
		}
	}

	Node* FindByKeyPrivate(Node* const subTreeRoot, int key)
	{
		if (subTreeRoot)
		{
			if (subTreeRoot->GetKey() == key)
				return subTreeRoot;
			else
			{
				Node* leftDescendant = FindByKeyPrivate(subTreeRoot->m_left, key);
				Node* rightDescendant = FindByKeyPrivate(subTreeRoot->m_right, key);
				if (leftDescendant && leftDescendant->GetKey() == key)
					return leftDescendant;

				if (rightDescendant && rightDescendant->GetKey() == key)
					return rightDescendant;

				return nullptr;
			}
		}

		return nullptr;
	}

	Node* FindParentByKeyPrivate(Node* const subTreeRoot, int key)
	{
		if (subTreeRoot)
		{
			if (subTreeRoot->m_left || subTreeRoot->m_right)
			{
				if ((subTreeRoot->m_left && subTreeRoot->m_left->GetKey() == key) || (subTreeRoot->m_right && subTreeRoot->m_right->GetKey() == key))
					return subTreeRoot;
				else
				{

					Node* m_Left = FindParentByKeyPrivate(subTreeRoot->m_left, key);
					Node* m_Right = FindParentByKeyPrivate(subTreeRoot->m_right, key);
					if (m_Left)
						return m_Left;

					if (m_Right)
						return m_Right;
				}
			}
		}

		return nullptr;
	}

	bool EraseByKeyPrivate(Node* const subTreeRoot, int key)
	{
		Node* nodeToDelete = FindByKeyPrivate(subTreeRoot, key);
		return ErasePrivate(nodeToDelete);
	}

	bool ErasePrivate(Node* const nodeToDelete)
	{
		if (nodeToDelete == nullptr)
		{
			return false;
		}
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

	bool CheckForBalancePrivate(Node* const subTreeRoot)
	{
		if (subTreeRoot == nullptr)
			return true;

		if (abs(GetHeightPrivate(subTreeRoot->m_left) - GetHeightPrivate(subTreeRoot->m_right)) <= 1 && CheckForBalancePrivate(subTreeRoot->m_left) && CheckForBalancePrivate(subTreeRoot->m_right))
			return true;
		else
			return false;
	}

	int GetSumOfAllKeysPrivate(Node* const subTreeRoot)
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

	int GetLevelOfNodeByKeyPrivate(Node* const subTreeRoot, int key)
	{
		if (subTreeRoot == nullptr) {
			return -1;
		}

		if (subTreeRoot->GetKey() == key)
			return 0;

		int h = GetHeightPrivate(subTreeRoot);
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

	std::vector<int> GetVectorOfAllKeysPrivate(Node* const subTreeRoot)
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

	void PrintTreeByLevelsPrivate(Node* const subTreeRoot, const int level = 0)
	{
		using std::cout;
		using std::endl;

		if (subTreeRoot == nullptr) {
			if (subTreeRoot == m_root) {
				cout << "Tree is empty" << endl;
			}
			return;
		}

		PrintTreeByLevelsPrivate(subTreeRoot->m_right, level + 1);

		for (int i = 0; i < level; i++)
			cout << "   ";
		cout << subTreeRoot->GetKey() << endl;

		PrintTreeByLevelsPrivate(subTreeRoot->m_left, level + 1);
	}

	void PrintLevelPrivate(Node* const subTreeRoot, int &amountOfX, const int level, const int currentLevel = 0)
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
			PrintLevelPrivate(subTreeRoot->m_left, amountOfX, level, currentLevel + 1);
			PrintLevelPrivate(subTreeRoot->m_right, amountOfX, level, currentLevel + 1);
		}
	}

	void PrintLeavesPrivate(Node* const subTreeRoot)
	{
		if (subTreeRoot == nullptr)
			return;
		if (subTreeRoot->m_left == nullptr && subTreeRoot->m_right == nullptr)
			std::cout << subTreeRoot->GetKey() << " ";
		else
		{
			PrintLeavesPrivate(subTreeRoot->m_left);
			PrintLeavesPrivate(subTreeRoot->m_right);
		}
	}



public:
	/*BinaryTree CopyTree(Node* const subTreeRoot)
	{
	BinaryTree bintr;
	if (subTreeRoot)
	{
	bintr.m_root = new Node(subTreeRoot->GetKey());
	bintr.m_root->m_left = CopyTreePrivate(subTreeRoot->m_left);
	bintr.m_root->m_right = CopyTreePrivate(subTreeRoot->m_right);
	}
	return bintr;
	}*/
	BinaryTree CopyTree(Node& subTreeRoot)
	{
		BinaryTree bintr;
		bintr.m_root = new Node(subTreeRoot.GetKey());
		bintr.m_root->m_left = CopyTreePrivate(subTreeRoot.m_left);
		bintr.m_root->m_right = CopyTreePrivate(subTreeRoot.m_right);
		return bintr;
	}

	BinaryTree() = default;

	BinaryTree(const BinaryTree& binaryTree)
	{
		m_root = CopyTreePrivate(binaryTree.m_root);
	}

	~BinaryTree()
	{
		DeleteSubTreePrivate(m_root);
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
		DeleteSubTreePrivate(m_root);
	}

	void DeleteSubTree(Node& subTreeRoot)
	{
		DeleteSubTreePrivate(subTreeRoot.m_left);
		DeleteSubTreePrivate(subTreeRoot.m_right);
		delete &subTreeRoot;
		if (&subTreeRoot == m_root) //do not forget about "subTreeRoot == m_root" case
			m_root = nullptr;
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
		return GetHeightPrivate(m_root);
	}

	int GetHeight(Node& subTreeRoot)
	{
		int height = 0;

		std::vector<Node*> currentLevelNodes;
		currentLevelNodes.push_back(&subTreeRoot);

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
		return GetAmountOfNodesPrivate(m_root);
	}

	int GetAmountOfNodes(Node& subTreeRoot)
	{
		int amountOfNodes = 0;
		amountOfNodes++;
		amountOfNodes += GetAmountOfNodesPrivate(subTreeRoot.m_left);
		amountOfNodes += GetAmountOfNodesPrivate(subTreeRoot.m_right);

		return amountOfNodes;
	}

	int GetMaxKey()
	{
		return GetMaxKeyPrivate(m_root);
	}

	int GetMaxKey(Node& subTreeRoot)
	{
		if (&subTreeRoot == nullptr)
		{
			return 0;
		}

		int subTreeRootMaxKey = subTreeRoot.GetKey();
		if (subTreeRoot.m_left)
		{
			int localMaxKey = GetMaxKeyPrivate(subTreeRoot.m_left);
			if (subTreeRootMaxKey < localMaxKey)
				subTreeRootMaxKey = localMaxKey;
		}

		if (subTreeRoot.m_right)
		{
			int localMaxKey = GetMaxKeyPrivate(subTreeRoot.m_right);
			if (subTreeRootMaxKey < localMaxKey)
				subTreeRootMaxKey = localMaxKey;
		}

		return subTreeRootMaxKey;
	}

	int GetMinKey()
	{
		return GetMinKeyPrivate(m_root);
	}

	int GetMinKey(Node& subTreeRoot)
	{
		if (&subTreeRoot == nullptr)
		{
			return 0;
		}

		int subTreeRootMinKey = subTreeRoot.GetKey();
		if (subTreeRoot.m_left)
		{
			int localMinKey = GetMinKeyPrivate(subTreeRoot.m_left);
			if (subTreeRootMinKey > localMinKey)
				subTreeRootMinKey = localMinKey;
		}

		if (subTreeRoot.m_right)
		{
			int localMinKey = GetMinKeyPrivate(subTreeRoot.m_right);
			if (subTreeRootMinKey > localMinKey)
				subTreeRootMinKey = localMinKey;
		}

		return subTreeRootMinKey;
	}

	Node* InsertNode(const int key)
	{
		return InsertNodePrivate(m_root, key);
	}

	Node* InsertNode(Node& subTreeRoot, const int key)
	{
		if (&subTreeRoot == nullptr)
		{
			if (m_root == nullptr)
			{
				m_root = new Node(key);
				return m_root;
			}
			else
			{
				return nullptr;
			}
		}
		if (subTreeRoot.m_left == nullptr)
		{
			subTreeRoot.m_left = new Node(key);
			return subTreeRoot.m_left;
		}
		else if (subTreeRoot.m_right == nullptr)
		{
			subTreeRoot.m_right = new Node(key);
			return subTreeRoot.m_right;
		}
		else
		{
			if (rand() % 2)
			{
				return InsertNodePrivate(subTreeRoot.m_left, key);
			}
			else
			{
				return InsertNodePrivate(subTreeRoot.m_right, key);
			}
		}
	}

	Node* FindByKey(const int key)
	{
		return FindByKeyPrivate(m_root, key);
	}

	Node* FindByKey(Node& subTreeRoot, int key)
	{
		if (&subTreeRoot)
		{
			if (subTreeRoot.GetKey() == key)
				return &subTreeRoot;
			else
			{
				Node* leftDescendant = FindByKeyPrivate(subTreeRoot.m_left, key);
				Node* rightDescendant = FindByKeyPrivate(subTreeRoot.m_right, key);
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
		return FindParentByKeyPrivate(m_root, key);
	}

	Node* FindParentByKey(Node& subTreeRoot, int key)
	{
		if (&subTreeRoot)
		{
			if (subTreeRoot.m_left || subTreeRoot.m_right)
			{
				if ((subTreeRoot.m_left && subTreeRoot.m_left->GetKey() == key) || (subTreeRoot.m_right && subTreeRoot.m_right->GetKey() == key))
					return &subTreeRoot;
				else
				{

					Node* m_Left = FindParentByKeyPrivate(subTreeRoot.m_left, key);
					Node* m_Right = FindParentByKeyPrivate(subTreeRoot.m_right, key);
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
		return EraseByKeyPrivate(m_root, key);
	}

	bool EraseByKey(Node& subTreeRoot, int key)
	{
		Node* nodeToDelete = FindByKeyPrivate(&subTreeRoot, key);
		return ErasePrivate(nodeToDelete);
	}

	bool Erase(Node& nodeToDelete)
	{
		if (&nodeToDelete == nullptr)
		{
			return false;
		}
		if (nodeToDelete.m_left == nullptr && nodeToDelete.m_right == nullptr)
		{
			Node* parent = FindParentByKey(nodeToDelete.GetKey());

			if (parent && parent->m_left == &nodeToDelete)
				parent->m_left = nullptr;

			if (parent && parent->m_right == &nodeToDelete)
				parent->m_right = nullptr;

			if (!parent)
				m_root = nullptr;

			delete &nodeToDelete;

			return true;
		}

		if (nodeToDelete.m_left == nullptr && nodeToDelete.m_right != nullptr)
		{
			Node* parent = FindParentByKey(nodeToDelete.GetKey());

			if (parent && parent->m_left == &nodeToDelete)
				parent->m_left = nodeToDelete.m_right;

			if (parent && parent->m_right == &nodeToDelete)
				parent->m_right = nodeToDelete.m_right;

			if (!parent)
				m_root = nodeToDelete.m_left;

			delete &nodeToDelete;

			return true;
		}

		if (nodeToDelete.m_left != nullptr && nodeToDelete.m_right == nullptr)
		{
			Node* parent = FindParentByKey(nodeToDelete.GetKey());

			if (parent && parent->m_left == &nodeToDelete)
				parent->m_left = nodeToDelete.m_left;

			if (parent && parent->m_right == &nodeToDelete)
				parent->m_right = nodeToDelete.m_left;

			if (!parent)
				m_root = nodeToDelete.m_left;

			delete &nodeToDelete;

			return true;
		}

		if (nodeToDelete.m_left && nodeToDelete.m_right)
		{
			Node* parent = FindParentByKey(nodeToDelete.GetKey());
			if (parent)
			{
				if (parent->m_left == &nodeToDelete)
				{
					Node* rightDescendant = nodeToDelete.m_right;
					Node* leftDescendant = nodeToDelete.m_left;
					delete &nodeToDelete;
					parent->m_left = leftDescendant;
					Node* parentOfLeaf = leftDescendant;
					while (parentOfLeaf->m_left != nullptr)
						parentOfLeaf = parentOfLeaf->m_left;
					parentOfLeaf->m_left = rightDescendant;
					return true;
				}
				else if (parent->m_right == &nodeToDelete)
				{
					Node* rightDescendant = nodeToDelete.m_right;
					Node* leftDescendant = nodeToDelete.m_left;
					delete &nodeToDelete;
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
				Node* rightDescendant = nodeToDelete.m_right;
				Node* leftDescendant = nodeToDelete.m_left;
				delete &nodeToDelete;
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
		return CheckForBalancePrivate(m_root);
	}

	bool CheckForBalance(Node& subTreeRoot)
	{
		if (&subTreeRoot == nullptr)
			return true;

		if (abs(GetHeightPrivate(subTreeRoot.m_left) - GetHeightPrivate(subTreeRoot.m_right)) <= 1 && CheckForBalancePrivate(subTreeRoot.m_left) && CheckForBalancePrivate(subTreeRoot.m_right))
			return true;
		else
			return false;
	}

	int GetSumOfAllKeys()
	{
		return GetSumOfAllKeysPrivate(m_root);
	}

	int GetSumOfAllKeys(Node& subTreeRoot)
	{
		if (&subTreeRoot == nullptr) {
			return -1;
		}

		int sum = 0;
		std::vector<Node*> currentLevelNodes;
		currentLevelNodes.push_back(&subTreeRoot);
		sum += subTreeRoot.GetKey();

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
		return GetLevelOfNodeByKeyPrivate(m_root, key);
	}

	int GetLevelOfNodeByKey(Node& subTreeRoot, int key)
	{
		if (&subTreeRoot == nullptr) {
			return -1;
		}

		if (subTreeRoot.GetKey() == key)
			return 0;

		int h = GetHeightPrivate(&subTreeRoot);
		std::vector<Node*> currentLevelNodes;
		currentLevelNodes.push_back(&subTreeRoot);

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
		return GetVectorOfAllKeysPrivate(m_root);
	}

	std::vector<int> GetVectorOfAllKeys(Node& subTreeRoot)
	{
		if (&subTreeRoot == nullptr)
			return std::vector<int>();

		std::vector<int> keys;
		std::vector<Node*> currentLevelNodes;
		currentLevelNodes.push_back(&subTreeRoot);
		keys.push_back(subTreeRoot.GetKey());

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
		PrintTreeByLevelsPrivate(m_root);
	}

	void PrintTreeByLevels(Node& subTreeRoot, const int level = 0)
	{
		using std::cout;
		using std::endl;

		if (&subTreeRoot == nullptr) {
			if (&subTreeRoot == m_root) {
				cout << "Tree is empty" << endl;
			}
			return;
		}

		PrintTreeByLevelsPrivate(subTreeRoot.m_right, level + 1);

		for (int i = 0; i < level; i++)
			cout << "   ";
		cout << subTreeRoot.GetKey() << endl;

		PrintTreeByLevelsPrivate(subTreeRoot.m_left, level + 1);
	}

	void PrintLevel(int &amountOfX, const int level)
	{
		PrintLevelPrivate(m_root, amountOfX, level, 0);
	}

	void PrintLevel(Node& subTreeRoot, int &amountOfX, const int level, const int currentLevel = 0)
	{
		using std::cout;
		using std::endl;

		if (&subTreeRoot == nullptr) {
			if (&subTreeRoot == m_root)
				cout << "Tree is empty" << endl;
			return;
		}

		if (currentLevel == level) {
			cout << subTreeRoot.GetKey() << "   ";
			++amountOfX;
		}
		else if (currentLevel < level) {
			PrintLevelPrivate(subTreeRoot.m_left, amountOfX, level, currentLevel + 1);
			PrintLevelPrivate(subTreeRoot.m_right, amountOfX, level, currentLevel + 1);
		}
	}

	void PrintLeaves()
	{
		return PrintLeavesPrivate(m_root);
	}

	void PrintLeaves(Node& subTreeRoot)
	{
		if (&subTreeRoot == nullptr)
			return;
		if (subTreeRoot.m_left == nullptr && subTreeRoot.m_right == nullptr)
			std::cout << subTreeRoot.GetKey() << " ";
		else
		{
			PrintLeavesPrivate(subTreeRoot.m_left);
			PrintLeavesPrivate(subTreeRoot.m_right);
		}
	}

	BinaryTree operator=(const BinaryTree& binaryTree)
	{
		if (&binaryTree == this)
			return *this;
		DeleteSubTreePrivate(m_root);
		m_root = CopyTreePrivate(binaryTree.m_root);
		return *this;
	}
};