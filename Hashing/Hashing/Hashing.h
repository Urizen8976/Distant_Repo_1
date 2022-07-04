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
	enum state //enumeration - grouped set of integer constants;
	{
		empty,
		filled,
		deleted
	};

	class HashCell
	{
	public:
		HashCell(int key = -1, int next = -1, T value = T(), state initialState = empty)
		{
			m_key = key;
			m_next = next;
			m_value = value;
			m_state = initialState;
		}
		T m_value;
		int m_key;
		int m_next;
		state m_state;
	};

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
	HashCell* m_table;
};

template<typename T>
HashTable<T>::HashTable()
{
	m_size = 1;
	m_actual_size = 0;
	m_table = new HashCell[m_size];
	hf = &hf2;
}

template<typename T>
HashTable<T>::HashTable(int size)
{
	m_size = size;
	m_actual_size = 0;
	m_table = new HashCell[m_size];
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
		delete[]m_table;
		m_table = new HashNode[m_size];
	}
	m_actual_size = copy.m_actual_size;
	for (int i = 0; i < m_size; i++)
	{
		m_table[i].m_key = copy.m_table[i].m_key;
		m_table[i].m_value = copy.m_table[i].m_value;
		m_table[i].m_next = copy.m_table[i].m_next;
		m_table[i].m_state = copy.m_table[i].m_state;
	}
	hf = copy.hf;
}

template<typename T>
HashTable<T>::~HashTable()
{
	delete[]m_table;
}

template<typename T>
bool HashTable<T>::checkElementByKey(int key)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_table[i].m_key == key)
		{
			return true;
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
	int index = hf->hash(1, key, m_size);
	if (m_table[index].m_state != filled)
	{
		m_table[index].m_key = key;
		m_table[index].m_value = value;
		m_table[index].m_state = filled;
		return true;
	}
	for (int i = 0; i < m_size; i++)
	{
		if (m_table[i].m_state != filled)
		{
			m_table[i].m_key = key;
			m_table[i].m_value = value;
			m_table[i].m_state = filled;

			HashCell* temp = &m_table[index];
			while (temp->m_next != -1)
			{
				temp = &m_table[temp->m_next];
			}
			temp->m_next = i;
			return true;
		}
	}
	return false;
}

template<typename T>
bool HashTable<T>::deleteElementByKey(int key)
{
	if (!m_actual_size)
	{
		return false;
	}
	if (checkElementByKey(key))
	{
		m_actual_size--;
		int index = hf->hash(1, key, m_size);
		if (m_table[index].m_key == key)
		{
			m_table[index].m_state = deleted;
			return true;
		}
		HashCell* temp = &m_table[index];
		while (temp->m_key != key)
		{
			temp = &m_table[temp->m_next];
		}
		temp->m_state = deleted;
		return true;
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
		if (m_table[i].m_state != empty)
		{
			temp.addElementByKey(m_table[i].m_key, m_table[i].m_value);
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

		delete[]m_table;
		m_table = new HashCell[m_size];
	}
	m_actual_size = ht.m_actual_size;
	hf = ht.hf;
	for (int i = 0; i < m_size; i++)
	{
		m_table[i].m_key = ht.m_table[i].m_key;
		m_table[i].m_value = ht.m_table[i].m_value;
		m_table[i].m_next = ht.m_table[i].m_next;
		m_table[i].m_state = ht.m_table[i].m_state;
	}
	return *this;
}

template<typename T>
void HashTable<T>::print()
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_table[i].m_state != empty)
		{
			std::cout << "(" << i << ") ";
			std::cout << m_table[i].m_key << " : '" << m_table[i].m_value << "'";
			std::cout << ((m_table[i].m_state == filled) ? " filled" : " deleted");
			std::cout << std::endl;
		}
	}
}
