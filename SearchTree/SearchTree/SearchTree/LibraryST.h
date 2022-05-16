#pragma once
#include "LibraryBT.h"

class SearchTree : public BinaryTree
{
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

	Node* FindByKeyPrivate(Node* const subTreeRoot, int key)
	{
		if (subTreeRoot)
		{
			if (subTreeRoot->GetKey() == key)
				return subTreeRoot;
			else
			{
				if (subTreeRoot->GetKey() > key)
				{
					Node* leftDescendant = FindByKeyPrivate(subTreeRoot->m_left, key);
					if (leftDescendant && leftDescendant->GetKey() == key)
						return leftDescendant;
				}
					
				if (subTreeRoot->GetKey() <= key)
				{
					Node* rightDescendant = FindByKeyPrivate(subTreeRoot->m_right, key);
					if (rightDescendant && rightDescendant->GetKey() == key)
						return rightDescendant;
				}

				return nullptr;
			}
		}

		return nullptr;
	}

	int GetLevelOfNodeByKeyPrivate(Node* subTreeRoot, const int key)
	{
		if (subTreeRoot == nullptr)
		{
			return -1;
		}
		Node* temp = subTreeRoot;
		int level = 1;
		while (temp)
		{
			while (key < temp->GetKey())
			{
				temp = temp->m_left;
				if (temp == nullptr)
				{
					return -1;
				}
				level++;
			}

			while (key > temp->GetKey())
			{
				temp = temp->m_left;
				if (temp == nullptr)
				{
					return -1;
				}
				level++;
			}
			if (key == temp->GetKey())
			{
				return level;
			}
		}
		return -1;
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



public:
	SearchTree() : BinaryTree() {};
	SearchTree(const SearchTree& searchTree) : BinaryTree(searchTree) {};
	~SearchTree() = default;

	SearchTree CopyTree(Node& subTreeRoot)
	{
		SearchTree bintr;
		bintr.m_root = new Node(subTreeRoot.GetKey());
		bintr.m_root->m_left = CopyTreePrivate(subTreeRoot.m_left);
		bintr.m_root->m_right = CopyTreePrivate(subTreeRoot.m_right);
		return bintr;
	}

	int GetMinKey(Node& subTreeRoot)
	{
		assert(&subTreeRoot != nullptr && "getMin: subTreeRoot was nullptr");
		Node* temp = &subTreeRoot;
		while (temp->m_left)
		{
			temp = temp->m_left;
		}
		return temp->GetKey();
	}

	int GetMaxKey(Node& subTreeRoot)
	{
		assert(&subTreeRoot != nullptr && "getMax: subTreeRoot was nullptr");
		Node* temp = &subTreeRoot;
		while (temp->m_right)
		{
			temp = temp->m_right;
		}
		return temp->GetKey();
	}

	bool InsertNode(Node& subTreeRoot, const int key)
	{
		if (&subTreeRoot == nullptr)
		{
			if (&subTreeRoot == m_root)
			{
				m_root = new Node(key);
				return true;
			}
			return false;
		}
		Node* temp = &subTreeRoot;
		while (true)
		{
			while (key < temp->GetKey())
			{
				if (temp->m_left)
				{
					temp = temp->m_left;
				}
				else if (key < temp->GetKey())
				{
					temp->m_left = new Node(key);
					return true;
				}
			}

			while (key >= temp->GetKey())
			{
				if (temp->m_right)
				{
					temp = temp->m_right;
				}
				else if (key >= temp->GetKey())
				{
					temp->m_right = new Node(key);
					return true;
				}
			}
		}
		return false;
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
				if (subTreeRoot.GetKey() > key)
				{
					Node* leftDescendant = FindByKeyPrivate(subTreeRoot.m_left, key);
					if (leftDescendant && leftDescendant->GetKey() == key)
						return leftDescendant;
				}

				if (subTreeRoot.GetKey() <= key)
				{
					Node* rightDescendant = FindByKeyPrivate(subTreeRoot.m_right, key);
					if (rightDescendant && rightDescendant->GetKey() == key)
						return rightDescendant;
				}

				return nullptr;
			}
		}

		return nullptr;
	}

	int GetLevelOfNodeByKey(Node& subTreeRoot, const int key)
	{
		if (&subTreeRoot == nullptr)
		{
			return -1;
		}
		Node* temp = &subTreeRoot;
		int level = 1;
		while (temp)
		{
			while (key < temp->GetKey())
			{
				temp = temp->m_left;
				if (temp == nullptr)
				{
					return -1;
				}
				level++;
			}

			while (key > temp->GetKey())
			{
				temp = temp->m_left;
				if (temp == nullptr)
				{
					return -1;
				}
				level++;
			}
			if (key == temp->GetKey())
			{
				return level;
			}
		}
		return -1;
	}

	SearchTree& operator=(const SearchTree& other)
	{
		if (this == &other)
		{
			return *this;
		}
		BinaryTree::operator=(other);
		return *this;
	}
};