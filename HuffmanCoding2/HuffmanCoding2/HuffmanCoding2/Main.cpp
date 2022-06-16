#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;


class HuffmanCoding
{
public:
	struct HuffmanNode
	{
		char ch;
		int freq;
		HuffmanNode *left, *right;
	};

	static HuffmanNode* getNode(char ch, int freq, HuffmanNode* left, HuffmanNode* right)
	{
		HuffmanNode* Hnode = new HuffmanNode();

		Hnode->ch = ch;
		Hnode->freq = freq;
		Hnode->left = left;
		Hnode->right = right;

		return Hnode;
	}

	struct compareHuffmanNodes
	{
		bool operator()(HuffmanNode* l, HuffmanNode* r)
		{
			return l->freq > r->freq;
		}
	};

	static void encode(HuffmanNode* root, string str,
		unordered_map<char, string> &huffmanCode)
		//unordered_map - an associative container that contains key-value pairs with unique keys. 
		//Search, insertion, and removal of elements have average constant-time complexity.
	{
		if (root == nullptr)
			return;

		if (!root->left && !root->right) {
			huffmanCode[root->ch] = str;
		}

		encode(root->left, str + "0", huffmanCode);
		encode(root->right, str + "1", huffmanCode);
	}

	static void decode(HuffmanNode* root, int &index, string str)
	{
		if (root == nullptr) {
			return;
		}	

		if (!root->left && !root->right)
		{
			cout << root->ch;
			return;
		}

		index++;

		if (str[index] == '0')
			decode(root->left, index, str);
		else
			decode(root->right, index, str);
	}


	static void buildHuffmanTree(string text)
	{
		unordered_map<char, int> freq;
		for (char ch : text) {
			freq[ch]++;
		}

		priority_queue<HuffmanNode*, vector<HuffmanNode*>, compareHuffmanNodes> pq;
		//priority_queue - a container adaptor that provides constant time lookup of the largest (by default) element, 
		//at the expense of logarithmic insertion and extraction.

		for (auto pair : freq) {
			pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
		}

		while (pq.size() != 1)
		{
			HuffmanNode *left = pq.top(); pq.pop();
			HuffmanNode *right = pq.top();	pq.pop();

			int sum = left->freq + right->freq;
			pq.push(getNode('\0', sum, left, right));
		}

		HuffmanNode* root = pq.top();

		unordered_map<char, string> huffmanCode;
		if (!root->left && !root->right) encode(root, "0", huffmanCode);
		else encode(root, "", huffmanCode);

		cout << "Huffman Codes are :\n" << '\n';
		for (auto pair : huffmanCode) {
			cout << pair.first << " " << pair.second << '\n';
		}

		cout << "\nOriginal string was :\n" << text << '\n';

		string str = "";
		for (char ch : text) {
			str += huffmanCode[ch];
		}

		cout << "\nEncoded string is :\n" << str << '\n';

		int index = -1;
		cout << "\nDecoded string is: \n";
		while (index < (int)str.size() - 1) {
			decode(root, index, str);
			if (!root->left && !root->right)
				index++;
		}
	}
};



int main()
{
	setlocale(LC_ALL, "RUS");
	string text = "aaaaa";
	//1: asdasdgfads
	//2: asdasdÙ˚‚‡‚˚Ù
	//3: aaaaa
	HuffmanCoding::buildHuffmanTree(text);
	cout << "\n";
	system("pause");
	return 0;
}