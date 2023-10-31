#include <algorithm>
#include <iostream>
#include <list>

const size_t listLen = 10;

class MyClass {
public:
	MyClass(int);
	~MyClass();
	MyClass(const MyClass&);
	MyClass& operator=(const MyClass&);
private:
	int* data;
};

MyClass::MyClass(int initialVal)
{
	std::cout << "* Regular constructor called" << std::endl;

	data = new int[listLen];

	for (size_t i = 0; i < listLen; ++i)
		data[i] = initialVal;
}

MyClass::~MyClass()
{
	std::cout << "* Destructor called" << std::endl;
	delete data;
}

MyClass::MyClass(const MyClass& other)
{
	std::cout << "* Copy constructor called" << std::endl;
	data = new int[10];
	std::copy(other.data, other.data + 10, data);
}

MyClass& MyClass::operator=(const MyClass& other)
{
	std::cout << "* Copy assignment operator called" << std::endl;
	std::copy(other.data, other.data + 10, data);
	return *this;
}

int main() {
	std::cout << "Making an instance of the class from scratch (regular constructor)" << std::endl;
	MyClass instanceA(1);

	std::cout << "Making a new instance of the class from instanceA" << std::endl;
	std::cout << "This calls the copy constructor." << std::endl;
	MyClass instanceB(instanceA);


	std::cout << "Doing an assignment like this calls the copy assignment operator." << std::endl;
	instanceB = instanceA;

	// std::list is usually implemented as a doubly-linked list.
	std::list<MyClass> list;

	std::cout << "Pushing back an instance of the class into a list" << std::endl;
	list.push_back(instanceA);

	std::cout << "Using emplace_back to make an instance of the class in-place in the list" << std::endl;
	std::cout << "this shouldn't call the copy constructor, as we're making a new instance from scratch" << std::endl;
	list.emplace_back(1);

	std::cout << "Exiting the program, all the destructors should be called" << std::endl;

	return 0;
}
