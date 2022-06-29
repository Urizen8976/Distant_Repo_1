#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "set.h"
#pragma once

class HuffmanCoding
{
public:
	struct HuffmanNode
	{
	public:
		HuffmanNode(int frequency = 0,
			Set symbols = Set(),
			HuffmanNode* leftChild = nullptr,
			HuffmanNode* rightChild = nullptr) :
			frequency(frequency),
			symbols(symbols),
			leftChild(leftChild),
			rightChild(rightChild)
		{}

		~HuffmanNode() = default;

		int numberOfChildren() const;

		Set symbols = Set();
		int frequency = 0;
		HuffmanNode* leftChild = nullptr;
		HuffmanNode* rightChild = nullptr;
	};

	struct
	{
		bool operator()(HuffmanNode* first, HuffmanNode* second) const {
			return first->frequency < second->frequency;
		}
	} compare;


	HuffmanCoding() = default;
	HuffmanCoding(const HuffmanCoding& copy);
	~HuffmanCoding();

	void huffman(const string fileName,
		const string codedName = "enfile.txt",
		const string resultName = "defile.txt")
	{
		HuffmanCoding hc;
		hc.build(fileName);
		cout << hc.encode(fileName, codedName);
		if (hc.decode(codedName, resultName))
			cout << "\ntrue";
		else
			cout << "\nfalse";
	}

	void build(const string fileName)
	{
		char character;
		const int charactersAmount = 256;
		int* allCharacters = new int[charactersAmount];
		for (int i = 0; i < charactersAmount; i++) {
			allCharacters[i] = 0;
		}

		ifstream file(fileName);

		if (!file.is_open()) {
			cerr << "\nunable to open file";
			return;
		}

		while (!file.eof()) {
			character = file.get();
			if (!file.eof()) {
				allCharacters[(unsigned char)character]++;
			}
		}

		file.close();

		std::list<HuffmanNode*> nodes;
		for (int i = 0; i < charactersAmount; i++) {
			if (allCharacters[i]) {
				HuffmanNode* temp = new HuffmanNode(allCharacters[i]);
				temp->symbols.set_bit(1, i);
				nodes.push_back(temp);
			}
		}

		nodes.sort(compare);
		std::list<HuffmanNode*>::iterator nodesIterator;

		while (nodes.size() > 1) {

			HuffmanNode* first = nodes.front();	nodes.pop_front();
			HuffmanNode* second = nodes.front(); nodes.pop_front();

			HuffmanNode* newNode = new HuffmanNode(first->frequency + second->frequency,
				first->symbols | second->symbols,
				first,
				second);

			if (!nodes.size()) {
				nodes.push_back(newNode);
			}
			else if (newNode->frequency <= nodes.front()->frequency) {
				nodes.push_front(newNode);
			}
			else if (newNode->frequency >= nodes.back()->frequency) {
				nodes.push_back(newNode);
			}
			else {

				nodesIterator = nodes.begin();

				for (HuffmanNode* temp : nodes) {
					if (temp->frequency > newNode->frequency) {
						nodes.insert(nodesIterator, newNode);
						break;
					}
					advance(nodesIterator, 1);
				}
			}
		}
		m_root = nodes.front();
	}

	int encode(const string originalText, const string codedText)
	{
		int oldSize = m_root->frequency * 8;

		map<char, BooleanVector> codes;
		if (m_root->leftChild && m_root->rightChild) {
			codeSymbols(m_root, codes);
		}
		else {
			char symbol;
			for (int i = 0; i < 256; i++) {
				if (m_root->symbols[i]) {
					symbol = (char)i;
					break;
				}
			}
			codes[symbol] = BooleanVector(1);
		}

		ifstream original(originalText);
		if (!original.is_open() || original.eof()) {
			return -1;
		}

		char symbol;
		int newSize = 0;

		ofstream coded(codedText);
		if (!coded.is_open()) {
			return -1;
		}

		while (!original.eof()) {
			symbol = original.get();
			if (!original.eof()) {
				coded << codes[symbol];
				newSize += codes[symbol].get_size();
			}
		}

		original.close();
		coded.close();

		return ((double)newSize / oldSize * 100); //data compression ratio
	}

	bool decode(const string codedText, const string decodedText)
	{
		if (!m_root) {
			return false;
		}

		ofstream decoded(decodedText);

		if (!decoded.is_open()) {
			return false;
		}

		ifstream coded(codedText);
		std::vector<char> str;
		char ch;
		while (!coded.eof()) {

			ch = coded.get();

			if (!coded.eof()) {
				str.push_back(ch);
			}
		}

		HuffmanNode* temp = m_root;

		for (auto ch : str) {
			if (ch == '1') {
				if (temp->rightChild) {
					temp = temp->rightChild;
				}
				else {
					decoded << temp->symbols;
					if (m_root->rightChild) {
						temp = m_root->rightChild;
					}
				}
			}
			else {
				if (temp->leftChild) {
					temp = temp->leftChild;
				}
				else {
					decoded << temp->symbols;
					if (m_root->leftChild) {
						temp = m_root->leftChild;
					}
				}
			}
		}
		if (m_root->leftChild || m_root->rightChild)
			decoded << temp->symbols;

		decoded.close();
		coded.close();

		return true;
	}


	void codeSymbols(HuffmanNode* node, map<char, BooleanVector>& codes) const
	{
		codeSymbols(m_root->leftChild, BooleanVector(1, 0), codes);
		codeSymbols(m_root->rightChild, BooleanVector(1, 1), codes);
	}

	void codeSymbols(HuffmanNode* node,
		BooleanVector code,
		map<char, BooleanVector>& codes) const
	{
		if (!node) {
			return;
		}

		if (!node->leftChild && !node->rightChild) {
			char symbol;
			for (int i = 0; i < 256; i++) {
				if (node->symbols[i]) {
					symbol = (char)i;
					break;
				}
			}
			codes[symbol] = code;
		}

		if (node->leftChild) {
			codeSymbols(node->leftChild, code << 1, codes);
		}

		if (node->rightChild) {
			codeSymbols(node->rightChild, (code << 1) | BooleanVector(1, 1), codes);
		}
	}

	void copyTree(const HuffmanNode* subTreeRoot);
	void copyNodes(const HuffmanNode* subTreeRoot, HuffmanNode* copyRoot);
	void addLeft(HuffmanNode* subTreeRoot, const int frequency, Set symbols);
	void addRight(HuffmanNode* subTreeRoot, const int frequency, Set symbols);
	void deleteTree(HuffmanNode* subTreeRoot);

private:
	HuffmanNode * m_root;
};

HuffmanCoding::HuffmanCoding(const HuffmanCoding& copy)
{
	copyTree(copy.m_root);
}

void HuffmanCoding::copyTree(const HuffmanNode* subTreeRoot)
{
	if (subTreeRoot == nullptr) {
		return;
	}

	if (subTreeRoot == m_root) {
		return;
	}
	if (m_root) {
		deleteTree(m_root);
	}

	m_root = new HuffmanNode(subTreeRoot->frequency, subTreeRoot->symbols);

	if (subTreeRoot->numberOfChildren() > 0) {
		copyNodes(subTreeRoot, m_root);
	}
}

void HuffmanCoding::copyNodes(const HuffmanNode* subTreeRoot, HuffmanNode* copyRoot)
{
	if (subTreeRoot == nullptr || copyRoot == nullptr) {
		return;
	}

	if (subTreeRoot->leftChild) {
		addLeft(copyRoot, subTreeRoot->leftChild->frequency, subTreeRoot->leftChild->symbols);
		copyNodes(subTreeRoot->leftChild, copyRoot->leftChild);
	}

	if (subTreeRoot->rightChild) {
		addRight(copyRoot, subTreeRoot->rightChild->frequency, subTreeRoot->rightChild->symbols);
		copyNodes(subTreeRoot->rightChild, copyRoot->rightChild);
	}
}

void HuffmanCoding::addLeft(HuffmanNode* subTreeRoot, const int frequency, Set symbols)
{
	if (subTreeRoot == nullptr) {
		return;
	}
	if (!subTreeRoot->leftChild) {
		subTreeRoot->leftChild = new HuffmanNode(frequency, symbols);
	}
}

void HuffmanCoding::addRight(HuffmanNode* subTreeRoot, const int frequency, Set symbols)
{
	if (subTreeRoot == nullptr) {
		return;
	}
	if (!subTreeRoot->rightChild) {
		subTreeRoot->rightChild = new HuffmanNode(frequency, symbols);
	}
}

HuffmanCoding::~HuffmanCoding()
{
	if (m_root) {
		deleteTree(m_root);
	}
}

void HuffmanCoding::deleteTree(HuffmanNode* subTreeRoot)
{
	if (subTreeRoot == nullptr) {
		return;
	}

	if (subTreeRoot->leftChild) {
		deleteTree(subTreeRoot->leftChild);
	}

	if (subTreeRoot->rightChild) {
		deleteTree(subTreeRoot->rightChild);
	}

	if (subTreeRoot == m_root) {
		m_root = nullptr;
	}
	delete subTreeRoot;
}

int HuffmanCoding::HuffmanNode::numberOfChildren() const
{
	int count = 0;
	if (leftChild) {
		count++;
	}
	if (rightChild) {
		count++;
	}
	return count;
}

int main() {
	setlocale(LC_ALL, "RUS");
	HuffmanCoding hc;
	//1: asdasdgfads
	//2: asdasdÙ˚‚‡‚˚Ù
	//3: aaaaa
	hc.huffman("orfile.txt");
	system("pause");
	return 0;
}