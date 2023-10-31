#include <algorithm>
#include <iostream>
#include <vector>

class MyClass {
public:
	MyClass();
	~MyClass();
	MyClass(const MyClass&);
private:
	int* data;
};

MyClass::MyClass()
{
	std::cout << "Regular constructor called" << std::endl;
	data = new int[10];
}

MyClass::~MyClass()
{
	std::cout << "Destructor called" << std::endl;
	delete data;
}

MyClass::MyClass(const MyClass& other)
{
	std::cout << "Copy constructor called" << std::endl;
	data = new int[10];
	std::copy(other.data, other.data + 10, data);
}

int main() {
	std::cout << "Making an instance of the class from scratch (regular constructor)" << std::endl;
	MyClass instanceA;

	std::cout << "Making a new instance of the class from instanceA" << std::endl;
	MyClass instanceB(instanceA);

	std::vector<MyClass> vector;

	std::cout << "Pushing back an instance of the class into a vector" << std::endl;
	vector.push_back(instanceA);

	std::cout << "Using emplace_back to make an instance of the class in-place in the vector" << std::endl;
	std::cout << "this shouldn't call the copy constructor, as we're making a new instance from scratch" << std::endl;
	vector.emplace_back();

	return 0;
}
