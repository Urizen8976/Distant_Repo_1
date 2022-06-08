#pragma once
#include "LibraryBT.h"

class SearchTree : public BinaryTree
{
private:
	bool InsertNodePrivate(Node* const subTreeRoot, const int key)
	{
		if (subTreeRoot == nullptr)
		{
			if (subTreeRoot == m_root)
			{
				m_root = new Node(key);
				return true;
			}
			return false;
		}
		Node* temp = subTreeRoot;
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

	Node* FindByKeyPrivate(Node* const subTreeRoot, int key) override
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

	int GetLevelOfNodeByKeyPrivate(Node* subTreeRoot, const int key) override
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

	bool ErasePrivate(Node* const nodeToDelete) override
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
				m_root = nodeToDelete->m_right;

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
					if (leftDescendant->m_right)
					{
						Node* maxLeftLeafParent = leftDescendant;
						while (maxLeftLeafParent->m_right && maxLeftLeafParent->m_right->m_right)
							maxLeftLeafParent = maxLeftLeafParent->m_right;
						if (maxLeftLeafParent->m_right->m_left)
						{
							Node* maxLeftLeaf = maxLeftLeafParent->m_right;
							maxLeftLeafParent->m_right = maxLeftLeafParent->m_right->m_left;
							parent->m_left = maxLeftLeaf;
							maxLeftLeaf->m_right = rightDescendant;
							maxLeftLeaf->m_left = leftDescendant;
						}
						else
						{
							Node* maxLeftLeaf = maxLeftLeafParent->m_right;
							maxLeftLeafParent->m_right = nullptr;
							parent->m_left = maxLeftLeaf;
							maxLeftLeaf->m_right = rightDescendant;
							maxLeftLeaf->m_left = leftDescendant;
						}
						return true;
					}
					else
					{
						parent->m_left = leftDescendant;
						leftDescendant->m_right = rightDescendant;
						return true;
					}
				}
				else if (parent->m_right == nodeToDelete)
				{
					Node* rightDescendant = nodeToDelete->m_right;
					Node* leftDescendant = nodeToDelete->m_left;
					delete nodeToDelete;
					if (leftDescendant->m_right)
					{
						Node* maxLeftLeafParent = leftDescendant;
						while (maxLeftLeafParent->m_right && maxLeftLeafParent->m_right->m_right)
							maxLeftLeafParent = maxLeftLeafParent->m_right;
						if (maxLeftLeafParent->m_right->m_left)
						{
							Node* maxLeftLeaf = maxLeftLeafParent->m_right;
							maxLeftLeafParent->m_right = maxLeftLeafParent->m_right->m_left;
							parent->m_right = maxLeftLeaf;
							maxLeftLeaf->m_right = rightDescendant;
							maxLeftLeaf->m_left = leftDescendant;
						}
						else
						{
							Node* maxLeftLeaf = maxLeftLeafParent->m_right;
							maxLeftLeafParent->m_right = nullptr;
							parent->m_right = maxLeftLeaf;
							maxLeftLeaf->m_right = rightDescendant;
							maxLeftLeaf->m_left = leftDescendant;
						}
						return true;
					}
					else
					{
						parent->m_right = leftDescendant;
						leftDescendant->m_right = rightDescendant;
						return true;
					}
				}
			}
			else
			{
				Node* rightDescendant = nodeToDelete->m_right;
				Node* leftDescendant = nodeToDelete->m_left;
				delete nodeToDelete;
				if (leftDescendant->m_right)
				{
					Node* maxLeftLeafParent = leftDescendant;
					while (maxLeftLeafParent->m_right && maxLeftLeafParent->m_right->m_right)
						maxLeftLeafParent = maxLeftLeafParent->m_right;
					if (maxLeftLeafParent->m_right->m_left)
					{
						Node* maxLeftLeaf = maxLeftLeafParent->m_right;
						maxLeftLeafParent->m_right = maxLeftLeafParent->m_right->m_left;
						m_root = maxLeftLeaf;
						maxLeftLeaf->m_right = rightDescendant;
						maxLeftLeaf->m_left = leftDescendant;
					}
					else
					{
						Node* maxLeftLeaf = maxLeftLeafParent->m_right;
						maxLeftLeafParent->m_right = nullptr;
						m_root = maxLeftLeaf;
						maxLeftLeaf->m_right = rightDescendant;
						maxLeftLeaf->m_left = leftDescendant;
					}
					return true;
				}
				else
				{
					m_root = leftDescendant;
					leftDescendant->m_right = rightDescendant;
					return true;
				}
			}
		}
		return false;
	}


protected:
	SearchTree(Node * root) : BinaryTree{ root } {};


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

	int GetMinKey(Node& subTreeRoot) override
	{
		assert(&subTreeRoot != nullptr && "getMin: subTreeRoot was nullptr");
		Node* temp = &subTreeRoot;
		while (temp->m_left)
		{
			temp = temp->m_left;
		}
		return temp->GetKey();
	}

	int GetMaxKey(Node& subTreeRoot) override
	{
		assert(&subTreeRoot != nullptr && "getMax: subTreeRoot was nullptr");
		Node* temp = &subTreeRoot;
		while (temp->m_right)
		{
			temp = temp->m_right;
		}
		return temp->GetKey();
	}

	using BinaryTree::InsertNode;

	bool InsertNode(const int key)
	{
		return InsertNodePrivate(m_root, key);
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

	bool Erase(Node& nodeToDelete) override
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
				m_root = nodeToDelete.m_right;

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
					if (leftDescendant->m_right)
					{
						Node* maxLeftLeafParent = leftDescendant;
						while (maxLeftLeafParent->m_right && maxLeftLeafParent->m_right->m_right)
							maxLeftLeafParent = maxLeftLeafParent->m_right;
						if (maxLeftLeafParent->m_right->m_left)
						{
							Node* maxLeftLeaf = maxLeftLeafParent->m_right;
							maxLeftLeafParent->m_right = maxLeftLeafParent->m_right->m_left;
							parent->m_left = maxLeftLeaf;
							maxLeftLeaf->m_right = rightDescendant;
							maxLeftLeaf->m_left = leftDescendant;
						}
						else
						{
							Node* maxLeftLeaf = maxLeftLeafParent->m_right;
							maxLeftLeafParent->m_right = nullptr;
							parent->m_left = maxLeftLeaf;
							maxLeftLeaf->m_right = rightDescendant;
							maxLeftLeaf->m_left = leftDescendant;
						}
						return true;
					}
					else
					{
						parent->m_left = leftDescendant;
						leftDescendant->m_right = rightDescendant;
						return true;
					}
				}
				else if (parent->m_right == &nodeToDelete)
				{
					Node* rightDescendant = nodeToDelete.m_right;
					Node* leftDescendant = nodeToDelete.m_left;
					delete &nodeToDelete;
					if (leftDescendant->m_right)
					{
						Node* maxLeftLeafParent = leftDescendant;
						while (maxLeftLeafParent->m_right && maxLeftLeafParent->m_right->m_right)
							maxLeftLeafParent = maxLeftLeafParent->m_right;
						if (maxLeftLeafParent->m_right->m_left)
						{
							Node* maxLeftLeaf = maxLeftLeafParent->m_right;
							maxLeftLeafParent->m_right = maxLeftLeafParent->m_right->m_left;
							parent->m_right = maxLeftLeaf;
							maxLeftLeaf->m_right = rightDescendant;
							maxLeftLeaf->m_left = leftDescendant;
						}
						else
						{
							Node* maxLeftLeaf = maxLeftLeafParent->m_right;
							maxLeftLeafParent->m_right = nullptr;
							parent->m_right = maxLeftLeaf;
							maxLeftLeaf->m_right = rightDescendant;
							maxLeftLeaf->m_left = leftDescendant;
						}
						return true;
					}
					else
					{
						parent->m_right = leftDescendant;
						leftDescendant->m_right = rightDescendant;
						return true;
					}
				}
			}
			else
			{
				Node* rightDescendant = nodeToDelete.m_right;
				Node* leftDescendant = nodeToDelete.m_left;
				delete &nodeToDelete;
				if (leftDescendant->m_right)
				{
					Node* maxLeftLeafParent = leftDescendant;
					while (maxLeftLeafParent->m_right && maxLeftLeafParent->m_right->m_right)
						maxLeftLeafParent = maxLeftLeafParent->m_right;
					if (maxLeftLeafParent->m_right->m_left)
					{
						Node* maxLeftLeaf = maxLeftLeafParent->m_right;
						maxLeftLeafParent->m_right = maxLeftLeafParent->m_right->m_left;
						m_root = maxLeftLeaf;
						maxLeftLeaf->m_right = rightDescendant;
						maxLeftLeaf->m_left = leftDescendant;
					}
					else
					{
						Node* maxLeftLeaf = maxLeftLeafParent->m_right;
						maxLeftLeafParent->m_right = nullptr;
						m_root = maxLeftLeaf;
						maxLeftLeaf->m_right = rightDescendant;
						maxLeftLeaf->m_left = leftDescendant;
					}
					return true;
				}
				else
				{
					m_root = leftDescendant;
					leftDescendant->m_right = rightDescendant;
					return true;
				}
			}
		}
		return false;
	}

	Node* FindByKey(const int key) override
	{
		return FindByKeyPrivate(m_root, key);
	}

	Node* FindByKey(Node& subTreeRoot, int key) override
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

	int GetLevelOfNodeByKey(Node& subTreeRoot, const int key) override
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

	static SearchTree BuildOptimalSearchTree(std::vector <int> const & d, std::vector <int> const & p, std::vector <int > const & q) 
	{
		const std::size_t n = d.size() + 1;
		//d - keys, p - frequencies, q - intermediate frequencies, w - weights, r - indexes, c - tree price
		if (not ((d.size() == p.size()) and (n == q.size())) or n == 1) 
			throw std::invalid_argument("Inputs must satisfy relation: |d| = |p| = (|q| + 1) > 1");

		int * const cw = new int[n * n];
		int * const r = new int[n * n]{ 0 };

		{
			for (std::size_t i = 0; i < n; i++) cw[i * n + i] = q[i];
		}

		{
			for (std::size_t j = 1; j < n; j++) 
			{
				for (std::size_t i = 0; i + j < n; i++) 
				{
					cw[i * n + (i + j)] = cw[i * n + (i + j - 1)] + p[(i + j - 1)] + q[(i + j)];
				}
			}
		}

		{
			for (std::size_t j = 1; j < n; j++) 
			{
				for (std::size_t i = 0; i + j < n; i++) 
				{
					int min_c = cw[i*n + i] + cw[(i + j)*n + i + 1];
					int min_k = i + 1;

					for (std::size_t k = i + 1; k <= (i + j); k++) 
					{
						int c = cw[(k - 1)*n + i] + cw[(i + j)*n + k];
						if (c < min_c) 
						{
							min_c = c; min_k = k;
						}
					}

					cw[(i + j)*n + i] = cw[i*n + (i + j)] + min_c;
					r[i*n + (i + j)] = min_k;
				}
			}
		}

		Node * const root = BuildRecursively(0, n - 1, r, d);

		delete[] r;
		delete[] cw;

		return SearchTree{ root };
	}

	static Node * BuildRecursively(int i, int j, int const * const r, std::vector <int> const & d) 
	{
		if (i >= j) return nullptr;
		int k = r[i * (d.size() + 1) + j];
		return 
		{ 
			new Node
		    { 
			    d[k - 1], BuildRecursively(i, k - 1, r, d), BuildRecursively(k, j, r, d)
		    } 
		};
	}
};