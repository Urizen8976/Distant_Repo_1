#pragma once
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

typedef unsigned char byte;

class BooleanVector
{
public:
	BooleanVector();
	BooleanVector(int size, int num = 0);
	BooleanVector(const char *array);
	BooleanVector(const BooleanVector& copy);
	~BooleanVector();
	void inverse_all();
	void inverse_bit(int bit);
	void set_bit(int num, int bit, int amount = 1);
	void set_all(int num);
	int weight();
	int get_size();
	void resize(int newSize);
	void filePrint(const char* fileName);
	void getFromFile(const char* fileName);

	BooleanVector operator&(const BooleanVector& bv);
	void operator&=(const BooleanVector& bv);
	BooleanVector operator|(const BooleanVector& bv);
	void operator|=(const BooleanVector& bv);
	BooleanVector operator^(const BooleanVector& bv);
	void operator^=(const BooleanVector& bv);
	BooleanVector operator<<(int amount);
	void operator<<=(int amount);
	BooleanVector operator>>(int amount);
	void operator>>=(int amount);
	BooleanVector operator~();
	void operator=(const BooleanVector& bv);
	int operator[](int const& bit) const;
	BooleanVector operator/(const BooleanVector& bv);
	void operator/=(const BooleanVector& bv);
	bool operator==(const BooleanVector& bv);

	friend ostream& operator<<(ostream &os, const BooleanVector& v);
	friend istream& operator>>(istream &is, BooleanVector& v);

	byte* vector;
	int m_size;
	int m_memory;
};



BooleanVector::BooleanVector()
{
	m_size = 0;
	m_memory = 1;
	vector = new byte[m_memory];
	vector[0] = 0;
}

BooleanVector::BooleanVector(int size, int num)
{
	if (size < 0)
	{
		throw "Boolean vector: size < 0";
	}
	m_size = size;
	m_memory = (m_size - 1) / 8 + 1;
	vector = new byte[m_memory];
	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = 0;
	}
	if (!num)
	{
		return;
	}
	if (num == 1)
	{
		byte mask = 1;
		int vector_index = m_memory - 1;
		for (int i = m_size - 1; i >= 0; i--, mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				vector_index--;
			}
			vector[vector_index] |= mask;
		}
		return;
	}
	throw "\nBoolean vector: wrong number(not 1 or 0)";
}

BooleanVector::BooleanVector(const char* array)
{
	for (int i = 0; i < strlen(array); i++)
	{
		if (array[i] != '0' && array[i] != '1')
		{
			throw "\nBoolean vector: not all symbols are '0' or '1'";
		}
	}
	m_size = strlen(array);
	m_memory = (m_size - 1) / 8 + 1;
	vector = new byte[m_memory];
	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = 0;
	}
	byte mask = 1;
	int vector_index = m_memory - 1;
	for (int i = m_size - 1; i >= 0; i--, mask <<= 1)
	{
		if (!mask)
		{
			mask = 1;
			vector_index--;
		}
		if (array[i] == '1')
		{
			vector[vector_index] |= mask;
		}
	}
}

BooleanVector::BooleanVector(const BooleanVector& copy)
{
	m_size = copy.m_size;
	m_memory = copy.m_memory;
	vector = new byte[m_memory];
	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = 0;
	}

	for (int i = 0; i < m_memory; i++)
	{
		vector[i] |= copy.vector[i];
	}
}

BooleanVector::~BooleanVector()
{
	delete[]vector;
}

void BooleanVector::inverse_all()
{
	int amount = m_memory * 8 - m_size;
	for (int i = m_memory - 1; i >= 0; i--)
	{
		vector[i] = ~vector[i];
	}
	vector[0] <<= amount;
	vector[0] >>= amount;
}

void BooleanVector::inverse_bit(int bit)
{
	if (bit < 0 || bit > m_size)
	{
		return;
	}
	int index_vector = m_memory - 1 - bit / 8;
	byte mask = 1;
	mask <<= bit % 8;
	if (vector[index_vector] & mask)
	{
		vector[index_vector] &= (~mask);
	}
	else
	{
		vector[index_vector] |= mask;
	}
}

void BooleanVector::set_bit(int num, int bit, int amount)
{
	if (bit < 0 || bit > m_size || amount > bit + 1)
	{
		cout << "\nset_bit: wrong bit";
		return;
	}
	int index_vector = m_memory - 1 - bit / 8;
	byte mask = 1;
	mask <<= bit % 8;
	if (!num)
	{
		for (int i = 0; i < amount; i++, mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
				index_vector++;
			}
			vector[index_vector] &= (~mask);
		}
		return;
	}
	if (num == 1)
	{
		for (int i = 0; i < amount; i++, mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
				index_vector++;
			}
			vector[index_vector] |= mask;
		}
		return;
	}
	cout << "\nset_bit: wrong number (not 1 or 0)";
	return;
}

void BooleanVector::set_all(int num)
{
	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = 0;
	}
	if (num)
	{
		BooleanVector temp(8, 1);
		for (int i = 0; i < m_memory; i++)
		{
			vector[i] |= temp.vector[0];
		}
	}
}

int BooleanVector::weight()
{
	byte mask;
	int count = 0;
	for (int i = 0; i < m_memory; i++)
	{
		for (mask = 1 << 7; mask; mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
			}
			if (vector[i] & mask)
			{
				count++;
			}
		}
	}
	return count;
}

int BooleanVector::get_size()
{
	return m_size;
}

void BooleanVector::resize(int newSize)
{
	if (newSize == m_size)
	{
		return;
	}
	if (newSize > m_memory * 8)
	{
		BooleanVector temp(*this);
		delete[]vector;
		int diff = abs(newSize - m_size);
		m_size = newSize;
		m_memory = (m_size - 1) / 8 + 1;
		vector = new byte[m_memory];
		set_all(0);
		for (int i = 0; i < temp.get_size(); i++)
		{
			set_bit(temp[i], i + diff);
		}
	}
	else
	{
		BooleanVector temp(*this);
		delete[]vector;
		int diff = abs(newSize - m_size);
		m_size = newSize;
		m_memory = (m_size - 1) / 8 + 1;
		vector = new byte[m_memory];
		set_all(0);
		for (int i = 0; i < temp.get_size(); i++)
		{
			set_bit(temp[i], i + diff);
		}
	}
}

void BooleanVector::filePrint(const char* fileName)
{
	ofstream file(fileName, std::ios::binary);
	if (!file.is_open())
	{
		return;
	}

	if (!(m_size % 8))
	{
		file << '0';
	}
	else
	{
		file << 8 - m_size % 8;
	}

	for (int i = 0; i < m_memory; i++)
	{
		file << vector[i];
	}

	file.close();
}

void BooleanVector::getFromFile(const char* fileName)
{
	ifstream file(fileName, std::ios::binary);
	if (!file.is_open())
	{
		return;
	}

	int extraCode;
	extraCode = file.get() - '0';

	std::vector<unsigned char> symbols;

	int count = 0;
	unsigned char symbol;

	while (!file.eof())
	{
		symbol = file.get();
		count++;
		if (!file.eof())
		{
			symbols.push_back(symbol);
		}
	}

	if (vector)
	{
		delete[]vector;
	}

	m_memory = symbols.size();
	vector = new byte[m_memory];
	m_size = m_memory * 8 - extraCode;

	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = symbols[i];
	}
	file.close();
}

void BooleanVector::operator=(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator =: the same vector";
		return;
	}
	if (vector)
	{
		delete[]vector;
	}

	m_size = bv.m_size;
	m_memory = bv.m_memory;
	vector = new byte[m_memory];

	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = 0;
	}

	for (int i = 0; i < m_memory; i++)
	{
		vector[i] |= bv.vector[i];
	}
}

BooleanVector BooleanVector::operator&(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &: the same vector";
		return *this;
	}

	int size, memory;
	if (m_size > bv.m_size)
	{
		size = bv.m_size;
		memory = bv.m_memory;
	}
	else
	{
		size = m_size;
		memory = m_memory;
	}

	BooleanVector temp(size, 0);
	for (int i = m_memory, index_vector = bv.m_memory; memory >= 0;)
	{
		temp.vector[memory--] = vector[i--] & bv.vector[index_vector--];
	}
	return temp;
}

void BooleanVector::operator&=(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &=: the same vector";
		return;
	}
	BooleanVector temp = (*this & bv);
	*this = temp;
}

BooleanVector BooleanVector::operator|(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &: the same vector";
		return *this;
	}

	BooleanVector temp;

	int i;

	if (m_size > bv.m_size)
	{
		temp <<= m_size;
	}
	else
	{
		temp <<= bv.m_size;
	}

	if (m_memory > bv.m_memory)
	{
		for (i = 0; i < m_memory - bv.m_memory; i++)
		{
			temp.vector[i] |= (*this).vector[i];
		}

		for (int j = 0; i < m_memory; i++, j++)
		{
			temp.vector[i] = bv.vector[j] | (*this).vector[i];
		}
		return temp;
	}

	if (bv.m_memory > m_memory)
	{
		for (i = 0; i < bv.m_memory - m_memory; i++)
		{
			temp.vector[i] |= bv.vector[i];
		}

		for (int j = 0; i < bv.m_memory; i++, j++)
		{
			temp.vector[i] = bv.vector[i] | (*this).vector[j];
		}

		return temp;
	}

	for (int i = 0; i < m_memory; i++)
	{
		temp.vector[i] = bv.vector[i] | vector[i];
	}

	return temp;
}



void BooleanVector::operator|=(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &=: the same vector";
		return;
	}
	BooleanVector temp = (*this | bv);
	*this = temp;
}

BooleanVector BooleanVector::operator^(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &: the same vector";
		return *this;
	}

	int size, memory, min_memory;
	bool flag;
	if (m_size > bv.m_size)
	{
		size = m_size;
		memory = m_memory - 1;
		min_memory = bv.m_memory - 1;
		flag = true;
	}
	else
	{
		size = bv.m_size;
		memory = bv.m_memory - 1;
		min_memory = m_memory - 1;
		flag = false;
	}
	BooleanVector temp(size);
	int i, index_vector;
	for (i = min_memory, index_vector = memory; i >= 0; i--, index_vector--)
	{
		if (flag)
		{
			temp.vector[index_vector] = vector[index_vector] ^ bv.vector[i];
		}
		else
		{
			temp.vector[index_vector] = vector[i] ^ bv.vector[index_vector];
		}
	}
	for (i = index_vector; i >= 0; i--)
	{
		if (flag)
		{
			temp.vector[i] ^= vector[i];
		}
		else
		{
			temp.vector[i] ^= bv.vector[i];
		}
	}

	return temp;
}

void BooleanVector::operator^=(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &=: the same vector";
		return;
	}
	BooleanVector temp = (*this ^ bv);
	*this = temp;
}

BooleanVector BooleanVector::operator<<(int amount)
{
	BooleanVector temp(*this);
	temp <<= amount;
	return temp;
}

void BooleanVector::operator<<=(int amount)
{
	if (!amount)
	{
		return;
	}
	if (m_size + amount > m_memory * 8)
	{
		BooleanVector temp(*this);
		delete[]vector;
		m_size += amount;
		m_memory = (m_size - 1) / 8 + 1;
		vector = new byte[m_memory];
		set_all(0);
		for (int i = 0; i < temp.get_size(); i++)
		{
			set_bit(temp[i], i + amount);
		}
	}
	else
	{
		BooleanVector temp(*this);
		m_size += amount;
		set_all(0);
		for (int i = 0; i < temp.get_size(); i++)
		{
			set_bit(temp[i], i + amount);
		}
	}
}

BooleanVector BooleanVector::operator>>(int amount)
{
	BooleanVector temp(*this);
	temp >>= amount;
	return temp;
}

void BooleanVector::operator>>=(int amount)
{
	if (!m_memory)
	{
		cout << "\noperator >>=: the size of vector is 0";
		return;
	}
	int i, bit = amount;
	for (i = 0; bit < m_size; i++, bit++)
	{
		if ((*this)[bit])
		{
			set_bit(1, i);
		}
		else
		{
			set_bit(0, i);
		}
	}
	set_bit(0, m_size - 1, amount);
	m_size = m_size - amount;
}

BooleanVector BooleanVector::operator~()
{
	BooleanVector temp(*this);
	temp.inverse_all();
	return temp;
}

int BooleanVector::operator[](int const& bit) const
{
	if (bit < 0 || bit > m_size)
	{
		throw "\nopeartor []: wrong bit";
	}
	int index_vector = m_memory - 1 - bit / 8;
	byte mask = 1;
	mask <<= bit % 8;
	if (vector[index_vector] & mask)
	{
		return 1;
	}
	return 0;
}

BooleanVector BooleanVector::operator/(const BooleanVector& bv)
{
	if (this == &bv)
	{
		BooleanVector temp(m_size, 0);
		return temp;
	}
	//BooleanVector temp;
	//temp = *this | bv;
	BooleanVector temp(*this);
	temp &= ~(*this & bv);
	return temp;
}

void BooleanVector::operator/=(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &=: the same vector";
		return;
	}
	*this = (*this / bv);
}

bool BooleanVector::operator==(const BooleanVector& bv)
{
	if (m_size != bv.m_size)
	{
		return false;
	}
	for (int i = 0; i < m_memory; i++)
	{
		if ((vector[i] & bv.vector[i]) != vector[i])
		{
			return false;
		}
	}
	return true;
}

ostream& operator<<(ostream& os, const BooleanVector& bv)
{
	byte mask;
	bool flag = true;
	for (int i = 0; i < bv.m_memory; i++)
	{
		for (mask = 1 << 7; mask; mask >>= 1)
		{
			if (!i && flag)
			{
				mask = 1 << bv.m_size % 8 - 1;
				flag = false;
			}
			if (!mask)
			{
				mask = 1 << 7;
			}
			if (bv.vector[i] & mask)
			{
				os << '1';
			}
			else
			{
				os << '0';
			}
		}
	}
	return os;
}

istream& operator>>(istream& is, BooleanVector& bv)
{
	if (bv.vector)
	{
		delete[]bv.vector;
	}
	char* string;
	string = new char[INT16_MAX];
	cin >> string;

	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] != '0' && string[i] != '1')
		{
			throw "\noperator>>: not all symbols are '0' or '1'";
		}
	}

	bv.m_size = strlen(string);
	bv.m_memory = (bv.m_size - 1) / 8 + 1;
	bv.vector = new byte[bv.m_memory];
	for (int i = 0; i < bv.m_memory; i++)
	{
		bv.vector[i] = 0;
	}

	byte mask = 1;
	int index_vector = bv.m_memory - 1;
	for (int i = bv.m_size - 1; i >= 0; i--, mask <<= 1)
	{
		if (!mask)
		{
			mask = 1;
			index_vector--;
		}
		if (string[i] == '1')
		{
			bv.vector[index_vector] |= mask;
		}

	}
	delete[]string;
	return is;
}