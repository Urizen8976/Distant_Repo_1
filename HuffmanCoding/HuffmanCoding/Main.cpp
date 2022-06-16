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
	string text = "aaaaabbbbbbaa";
	//1: asdasdgfads
	//2: asdasdÙ˚‚‡‚˚Ù
	//3: aaaaa
	HuffmanCoding::buildHuffmanTree(text);
	cout << "\n";
	system("pause");
	return 0;
}






/*
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <deque>
#include <algorithm>
#include <cstdint>
#include <array>


class Multiplicity 
{
private:
	std::array <uint32_t, 8> arrrr;

public:
	Multiplicity() : arrrr{ 0 } {}

	Multiplicity(Multiplicity const & other) { arrrr = other.arrrr; }

	Multiplicity(unsigned char c) : arrrr{ 0 }
	{
		std::size_t const arri = static_cast <std::size_t> (c) / 32;
		std::size_t const biti = static_cast <std::size_t> (c) % 32;
		arrrr[arri] |= (std::size_t(1) << biti);
	}

	Multiplicity & operator = (Multiplicity const & other) 
	{ 
		if (this == &other) return *this; arrrr = other.arrrr; return *this; 
	}

	bool operator [] (unsigned char c) const 
	{
		std::size_t const arri = static_cast <std::size_t> (c) / 32;
		std::size_t const biti = static_cast <std::size_t> (c) % 32;

		return { ((arrrr[arri]) & (std::size_t(1) << biti)) != 0 };
	}

	Multiplicity operator | (Multiplicity const & other) const 
	{
		Multiplicity cs = *this;
		for (std::size_t i = 0; i < 8; i++) cs.arrrr[i] |= other.arrrr[i];
		return cs;
	}

	friend std::ostream & operator << (std::ostream &, Multiplicity const &);
};

std::ostream & operator << (std::ostream & os, Multiplicity const & ch) 
{
	for (std::size_t i = 0; i < 256; i++) 
	{
		if (ch[i]) 
		{
			os << static_cast <char> (i);
		}
	}
	return os;
}



struct HuffmanNode 
{
	HuffmanNode() : freq{ 0 }, left{ nullptr }, right{ nullptr } {}
	HuffmanNode(unsigned char ch) : freq{ 1 }, chars{ ch }, left{ nullptr }, right{ nullptr } {}
	HuffmanNode(HuffmanNode &&) = default;
	HuffmanNode(HuffmanNode const &) = default;
	~HuffmanNode() = default;

	HuffmanNode operator + (HuffmanNode &);
	bool is_leaf() { return (left == nullptr and right == nullptr); }

	int freq;
	Multiplicity chars;
	HuffmanNode * left;
	HuffmanNode * right;
};



class HuffmanCoding {
private:
	HuffmanNode * m_root;
	void delete_rec(HuffmanNode * & root) 
	{
		//std::cout << root->chars << "\n";
		if (root->left != nullptr) delete_rec(root->left);
		if (root->right != nullptr) delete_rec(root->right);

		delete root;
		root = nullptr;
	}
	void clear() { if (m_root != nullptr) { delete_rec(m_root); } }

public:
	HuffmanCoding() : m_root(nullptr) {}
	~HuffmanCoding() { clear(); }

	void build(std::istream &);
	double encode(std::istream &, std::ostream &);
	bool decode(std::istream &, std::ostream &);
};

HuffmanNode HuffmanNode::operator + (HuffmanNode & other) {
	HuffmanNode huff;
	huff.freq = freq + other.freq;
	huff.chars = chars | other.chars;
	huff.left = this;
	huff.right = &other;
	return huff;
}


void HuffmanCoding::build(std::istream & file) {
	if (not (file.good())) throw std::invalid_argument{ "something's not right with the file" };

	clear();

	auto g = file.tellg();

	std::deque <HuffmanNode *> nodes;

	char ch;
	while (file.get(ch)) {
		bool found = false;
		for (auto const & node : nodes) {
			if (node->chars[ch]) {
				node->freq++;
				found = true;
				break;
			}
		}
		if (not found) {
			nodes.push_back(new HuffmanNode{ static_cast <unsigned char> (ch) });
		}
	}

	if (nodes.size() == 0) throw std::invalid_argument("kindly and politely asking you not to pass me empty files");

	std::sort(nodes.begin(), nodes.end(), [](HuffmanNode * a, HuffmanNode * b) { return a->freq < b->freq; });

	while (nodes.size() > 1) {
		HuffmanNode * sum = new HuffmanNode{ *nodes[0] + *nodes[1] };
		nodes.pop_front();
		nodes.pop_front();
		nodes.push_front(sum);
		std::sort(nodes.begin(), nodes.end(), [](HuffmanNode * a, HuffmanNode * b) { return a->freq < b->freq; });
	}

	m_root = nodes.front();

	file.clear();
	file.seekg(g);
	file.sync();
}


double HuffmanCoding::encode(std::istream & orfile, std::ostream & enfile) {
	build(orfile);

	if (not enfile.good()) throw std::invalid_argument("something aint right");

	std::size_t or_char_length = 0;
	std::size_t en_bit_length = 0;

	char ch;
	while (orfile.get(ch)) {
		auto walk = m_root;
		while (not walk->is_leaf()) {
			en_bit_length++;
			if (walk->left->chars[ch]) {
				walk = walk->left;
				enfile << '0';
			}
			else {
				walk = walk->right;
				enfile << '1';
			}
		}
		or_char_length++;
	}

	if (m_root->is_leaf()) {
		for (int i = 0; i < or_char_length; i++) enfile << "0";
		en_bit_length = 1;
	}

	return double(en_bit_length) / double(or_char_length * 8);
}


bool HuffmanCoding::decode(std::istream & enfile, std::ostream & defile) {
	if (not (enfile.good() and defile.good())) throw std::invalid_argument("blargh what an invalid arg");
	if (m_root == nullptr) throw std::logic_error("blargh i don't even have the tree");

	char ch;
	auto walk = m_root;

	if (walk->is_leaf()) {
		while (enfile.get(ch)) defile << walk->chars;
		return true;
	}

	while (enfile.get(ch)) {
		if (ch == '0') {
			walk = walk->left;
		}
		else if (ch == '1') {
			walk = walk->right;
		}
		else {
			return false;
		}

		if (walk->is_leaf()) {
			defile << walk->chars;
			walk = m_root;
		}
	}

	return true;
}




int main() {
	std::fstream orfile{ "orfile.txt", std::ios_base::in };
	std::fstream enfile{ "enfile.txt", std::ios_base::out | std::ios_base::trunc };
	std::fstream defile{ "defile.txt", std::ios_base::out | std::ios_base::trunc };
	HuffmanCoding huffman;

	std::cout << huffman.encode(orfile, enfile) << "\n";

	enfile.close();
	enfile.open("enfile.txt", std::ios_base::in);
	huffman.decode(enfile, defile);
}*/