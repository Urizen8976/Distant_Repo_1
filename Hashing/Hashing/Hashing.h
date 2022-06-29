#pragma once
#include <math.h>
#include <iostream>

//My number in the list - 11;
//Way of implementation a hash table - 1 - open addressing; 
//Hash function to be implemented - 2 - hi(K) = [hi-1(K) × a × N] mod N, a = – (1 – √5) ÷ 2, [ ] – целая часть;

class HashFunction
{
public:
	virtual int hash(int index, int key, int size) = 0;
};


class HashFunction1 : public HashFunction
{
public:
	int hash(int index, int key, int size) override
	{
		//1 - hi(K) = (hi-1(K) + c × i + d × i2) mod N, 
		//parameters c and d are defined as the remainder of dividing your number in the list below by 5 and 7 respectively;
		//c = 1, d = 4;
		int hash = key % size;
		for (int i = 0; i < index; i++)
		{
			hash = (hash + i + 4 * i * i) % size;
		}
		return hash;
	}
} hf1;


class HashFunction2 : public HashFunction
{
public:
	int hash(int index, int key, int size) override
	{
		//2 - hi(K) = [hi-1(K) × a × N] mod N, a = – (1 – √5) ÷ 2, [ ] – целая часть;
		int hash = key % size;
		double a = -(1 - sqrt(5)) / 2;
		for (int i = 0; i < index; i++)
		{
			hash = ((int)(hash * a * size) + 1) % size;
		}
		return hash;
	}
} hf2;


class HashFunction3 : public HashFunction
{
public:
	//3 - hi(K) = (K mod N) + i × (1+ K mod (N – 2)) mod N;
	int hash(int index, int key, int size) override
	{
		return (key % size + index * (1 + key % abs(size - 2))) % size;
	}
} hf3;


template<typename T>
class HashTable
{
public:
	HashTable();
	HashTable(int size);
	HashTable(const HashTable<T>& copy);
	~HashTable();
	bool addElementByKey(int key, T value);
	bool deleteElementByKey(int key);
	bool checkElementByKey(int key);
	void replaceHashFunction(HashFunction* newHashFunction);
	HashTable<T>& operator=(const HashTable<T>& ht);
	void print();


private:
	HashFunction * hf;
	int m_actual_size = 0;
	int m_size;
	int* m_keys;
	T* m_values;
	enum state //enumeration - grouped set of integer constants;
	{
		empty,
		filled,
		deleted
	} *m_states;
};

template<typename T>
HashTable<T>::HashTable()
{
	m_size = 1;
	m_keys = new int[m_size];
	m_values = new T[m_size];
	m_states = new state[m_size];
	m_keys[0] = 0;
	m_values[0] = T();
	m_states[0] = empty;
	hf = &hf2;
}

template<typename T>
HashTable<T>::HashTable(int size)
{
	m_size = size;
	m_keys = new int[m_size];
	m_values = new T[m_size];
	m_states = new state[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_keys[i] = 0;
		m_values[i] = T();
		m_states[i] = empty;
	}
	hf = &hf1;
}

template<typename T>
HashTable<T>::HashTable(const HashTable<T>& copy)
{
	if (&copy == this)
	{
		return;
	}

	if (m_size != copy.m_size)
	{
		m_size = copy.m_size;

		if (m_keys)
		{
			delete[]m_keys;
		}
		m_keys = new int[m_size];

		if (m_values)
		{
			delete[]m_values;
		}
		m_values = new T[m_size];

		if (m_states)
		{
			delete[]m_states;
		}
		m_states = new bool[m_size];
	}

	for (int i = 0; i < m_size; i++)
	{
		m_keys[i] = copy.m_keys[i];
		m_values[i] = copy.m_values[i];
		m_states[i] = copy.m_states[i];
	}
	hf = copy.hf;
}

template<typename T>
HashTable<T>::~HashTable()
{
	delete[]m_keys;
	delete[]m_values;
	delete[]m_states;
}

template<typename T>
bool HashTable<T>::checkElementByKey(int key)
{
	int index = 0;
	int hash;
	while (true) //Searching element, using the linear probing formula hi(key)=(h(key) + i) % M, increasing value i
	{
		hash = hf->hash(index, key, m_size);
		if (m_states[hash] == empty)
		{
			return false;
		}
		else if (m_keys[hash] == key)
		{
			return true;
		}
		else if (m_keys[hash] != key)
		{
			index++;
		}
	}
	return false;
}

template<typename T>
bool HashTable<T>::addElementByKey(int key, T value)
{
	if (m_actual_size >= m_size)
	{
		return false;
	}
	if (checkElementByKey(key))
	{
		return false;
	}

	m_actual_size++;
	int index = 0;
	while (true)
	{
		int hash = hf->hash(index, key, m_size);
		if (m_states[hash] != filled)
		{
			m_keys[hash] = key;
			m_values[hash] = value;
			m_states[hash] = filled;
			return true;
		}
		else if (m_keys[hash] != key)
		{
			index++;
		}
	}
}

template<typename T>
bool HashTable<T>::deleteElementByKey(int key)
{
	if (checkElementByKey(key))
	{
		m_actual_size--;
		int index = 0;
		while (true)
		{
			int hash = hf->hash(index, key, m_size);
			if (m_states[hash] == empty)
			{
				return false;
			}
			else if (m_keys[hash] == key)
			{
				m_states[hash] = deleted;
				return true;
			}
			else if (m_keys[hash] != key)
			{
				index++;
			}
		}
	}
	return false;
}

template<typename T>
void HashTable<T>::replaceHashFunction(HashFunction* newHashFunction)
{
	hf = newHashFunction;
	HashTable temp(m_size);
	temp.hf = newHashFunction;
	for (int i = 0; i < m_size; i++)
	{
		if (m_states[i] != empty)
		{
			temp.addElementByKey(m_keys[i], m_values[i]);
		}
	}
	*this = temp;
}

template<typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht)
{
	if (&ht == this)
	{
		return *this;
	}
	if (m_size != ht.m_size)
	{
		m_size = ht.m_size;

		if (m_keys)
		{
			delete[]m_keys;
		}
		m_keys = new int[m_size];

		if (m_values)
		{
			delete[]m_values;
		}
		m_values = new T[m_size];

		if (m_states)
		{
			delete[]m_states;
		}
		m_states = new state[m_size];
	}
	for (int i = 0; i < m_size; i++)
	{
		m_keys[i] = ht.m_keys[i];
		m_values[i] = ht.m_values[i];
		m_states[i] = ht.m_states[i];
	}
	return *this;
}

template<typename T>
void HashTable<T>::print()
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_states[i] != empty)
		{
			std::cout << "(" << i << ") ";
			std::cout << m_keys[i] << " : '" << m_values[i] << "'";
			std::cout << ((m_states[i] == filled) ? " filled" : " deleted");
			std::cout << std::endl;
		}
	}
}
