#pragma once
#include "BooleanVector.h"

class Set : public BooleanVector
{
public:
	Set();
	Set(const char *string);
	Set(const Set &copy);
	~Set() {};

	void print() const;
	bool check_element(char ch);
	int get_max();
	int get_min();
	int get_power();

	//using BooleanVector::operator=;
	//using BooleanVector::operator[];

	void operator=(const Set &set);
	bool operator==(const Set &set);
	bool operator!=(const Set &set);
	Set operator|(const Set &set);
	void operator|=(const Set &set);
	Set operator&(const Set &set);
	void operator&=(const Set &set);
	Set operator/(const Set &set);
	void operator/=(const Set &set);
	Set operator~();
	Set operator+(const char ch);
	void operator+=(const char ch);
	Set operator-(const char ch);
	void operator-=(const char ch);

	friend ostream& operator<<(ostream &os, const Set &set);
	friend istream& operator>>(istream &is, Set &set);
private:
	int m_power; 
};



Set::Set() : BooleanVector(256)
{
	m_power = 0;
}

Set::Set(const char* string) : BooleanVector(256)
{
	for (int i = 0; i < strlen(string); i++)
	{
		set_bit(1, string[i]);
	}
	m_power = weight();
}

Set::Set(const Set& copy) : BooleanVector(copy)
{
	m_power = copy.m_power;
}

void Set::print() const
{
	for (int i = 0; i <= 256; i++)
	{
		if ((*this)[i])
		{
			cout << (char)i << " ";
		}
	}
}

bool Set::check_element(char ch)
{
	if ((*this)[ch])
	{
		return true;
	}
	return false;
}

int Set::get_max()
{
	for (int i = 255; i >= 0; i--)
	{
		if ((*this)[i])
		{
			return i;
		}
	}
	return -1;
}

int Set::get_min()
{
	for (int i = 0; i < 256; i++)
	{
		if ((*this)[i])
		{
			return i;
		}
	}
	return -1;
}

int Set::get_power()
{
	return m_power;
}

void Set::operator=(const Set& set)
{
	if (this == &set)
	{
		return;
	}
	m_power = set.m_power;
	BooleanVector::operator=(set);
}

bool Set::operator==(const Set& set)
{
	if (m_power != set.m_power)
	{
		return false;
	}
	if ((BooleanVector)*this == set)
	{
		return true;
	}
	return false;
}

bool Set::operator!=(const Set& set)
{
	if (*this == set)
	{
		return false;
	}
	return true;
}

Set Set::operator|(const Set& set)
{
	if (this == &set)
	{
		return *this;
	}
	Set temp(*this);
	temp |= set;
	return temp;
}

void Set::operator|=(const Set& set)
{
	if (this == &set)
	{
		return;
	}
	BooleanVector::operator|=(set);
	m_power = weight();
}

Set Set::operator&(const Set& set)
{
	if (this == &set)
	{
		return *this;
	}
	Set temp(*this);
	temp &= set;
	return temp;
}

void Set::operator&=(const Set& set)
{
	if (this == &set)
	{
		return;
	}
	BooleanVector::operator&=(set);
	m_power = weight();
}

Set Set::operator/(const Set& set)
{
	Set temp;

	temp.m_power = temp.weight();
	return temp;
}

void Set::operator/=(const Set& set)
{
	BooleanVector::operator/=(set);
	m_power = weight();
}

Set Set::operator~()
{
	Set temp(*this);
	temp.inverse_all();
	temp.m_power = temp.weight();
	return temp;
}

Set Set::operator+(const char ch)
{
	Set temp(*this);
	if (!temp[ch])
	{
		temp.set_bit(1, ch);
		temp.m_power++;
	}
	return temp;
}

void Set::operator+=(const char ch)
{
	*this = *this + ch;
}

Set Set::operator-(const char ch)
{
	Set temp(*this);
	if (temp[ch])
	{
		temp.set_bit(0, ch);
		temp.m_power--;
	}
	return temp;
}

void Set::operator-=(const char ch)
{
	*this = *this - ch;
}

ostream& operator<<(ostream& os, const Set& set)
{
	for (int i = 0; i < 256; i++)
	{
		if (set[i])
		{
			os << (char)i;
		}
	}
	return os;
}

istream& operator>>(istream& is, Set& set)
{
	if (set.weight())
	{
		set.vector = 0;
	}
	int size;
	cout << "\nEnter the number of elements: ";
	cin >> size;
	while (size <= 0)
	{
		cout << "\nThe number of elements can't be less than 1";
		cout << "\nEnter another number of elements";
		cin >> size;
	}
	if (size > 0)
	{
		char* string;
		string = new char[size];
		cout << "\nEnter the elements: ";
		for (int i = 0; i < size; i++)
		{
			cin >> string[i];
		}
		for (int i = 0; i < size; i++)
		{
			set.set_bit(1, string[i]);
		}
		delete[]string;
	}
	set.m_power = size;
	return is;
}