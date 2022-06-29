#include "Hashing.h"
#include <iostream>
#include <string>

int main()
{
	HashTable<std::string> ht(10);

	ht.addElementByKey(10, "All the other kids");
	ht.addElementByKey(21, "with the pumped up kicks");
	ht.addElementByKey(666, "You better run");
	ht.addElementByKey(11, "better run");

	ht.print();

	ht.deleteElementByKey(21);
	ht.deleteElementByKey(10);

	HashTable<std::string> ht1(10);

	ht1.addElementByKey(10, "All the other kids");
	ht1.addElementByKey(21, "with the pumped up kicks");
	ht1.addElementByKey(666, "You better run");
	ht1.addElementByKey(11, "better run");
	ht1.addElementByKey(22, "Outrun my gun");
	ht1.addElementByKey(111, "All the other kids");
	ht1.addElementByKey(111, "with the pumped up kicks");

	std::cout << std::endl;
	ht1.print();

	ht1.replaceHashFunction(&hf3);

	std::cout << "\nafter changing hash function: \n";
	ht1.print();

	HashTable<std::string> copy;
	copy = ht1;

	ht1.deleteElementByKey(10);
	ht1.deleteElementByKey(21);
	ht1.deleteElementByKey(666);
	ht1.deleteElementByKey(11);
	ht1.deleteElementByKey(22);
	ht1.deleteElementByKey(111);

	std::cout << "\nafter deleting:" << std::endl;
	ht1.print();

	std::cout << "\ncopy: " << std::endl;
	copy.print();

	copy = ht1;

	std::cout << "\nht1 copy: " << std::endl;
	copy.print();

	system("pause");
	return 0;
}