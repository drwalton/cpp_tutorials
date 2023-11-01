#include <algorithm>
#include <iostream>
#include <vector>

const size_t listLen = 10;

class MyClass {
public:
	MyClass(int);
	~MyClass();
	MyClass(const MyClass&);
	MyClass(MyClass&&) noexcept;
	MyClass& operator=(const MyClass&);
	MyClass& operator=(MyClass&&) noexcept;
	const int* data() const; // Do you know what each of these consts mean?
	int* dataNonConst();
private:
	int* data_;
};

MyClass::MyClass(int initialVal)
{
	std::cout << "* Regular constructor called" << std::endl;

	data_ = new int[listLen];

	for (size_t i = 0; i < listLen; ++i)
		data_[i] = initialVal;
}

MyClass::~MyClass()
{
	std::cout << "* Destructor called" << std::endl;
	delete data_;
}

MyClass::MyClass(const MyClass& other)
{
	std::cout << "* Copy constructor called" << std::endl;
	data_ = new int[10];
	std::copy(other.data_, other.data_ + 10, data_);
}

MyClass::MyClass(MyClass&& other) noexcept
{
	std::cout << "* Move constructor called" << std::endl;
	data_ = other.data_;
	other.data_ = nullptr;
}

MyClass& MyClass::operator=(const MyClass& other)
{
	std::cout << "* Copy assignment operator called" << std::endl;
	std::copy(other.data_, other.data_ + 10, data_);
	return *this;
}

MyClass& MyClass::operator=(MyClass&& other) noexcept
{
	std::cout << "* Move assignment operator called" << std::endl;
	data_ = other.data_;
	other.data_ = nullptr;
	return *this;
}

const int* MyClass::data() const
{
	return data_;
}

int* MyClass::dataNonConst()
{
	return data_;
}

void printFirstElementVal(MyClass instance)
{
	std::cout << instance.data()[0] << std::endl;
}

void printFirstElementRef(const MyClass& instance)
{
	std::cout << instance.data()[0] << std::endl;
}

void addOneToInt(int* x) {
	*x += 1;
}

int main() {
	int x;
	addOneToInt(&x);


	MyClass instance(4);

	std::cout << "This version of the function passes in the instance by value." << std::endl;
	std::cout << "To do this it has to make a full copy of the object, and calls the copy constructor." << std::endl;
	std::cout << "Question: why doesn't it use the move constructor here?" << std::endl;
	printFirstElementVal(instance);

	std::cout << "This version of the function passes in the instance by reference." << std::endl;
	std::cout << "This doesn't need a copy, and is much more efficient." << std::endl;
	std::cout << "One concern is that passing by reference means the function could actually modify instance" << std::endl;
	std::cout << "However we use a const reference to say this function shouldn't change anything." << std::endl;
	std::cout << "If we did change something this would be a compiler error." << std::endl;
	printFirstElementRef(instance);

	printFirstElementPtr(&instance);

	// Question: having looked at this, which of the following is best?
	// Mesh loadMeshFile(std::string filename);
	// Mesh loadMeshFile(const std::string& filename);
	// Why is it better?

	return 0;
}
