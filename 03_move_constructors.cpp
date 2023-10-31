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

MyClass::MyClass(MyClass&& other) noexcept
{
	std::cout << "* Move constructor called" << std::endl;
	data = other.data;
	other.data = nullptr;
}

MyClass& MyClass::operator=(const MyClass& other)
{
	std::cout << "* Copy assignment operator called" << std::endl;
	std::copy(other.data, other.data + 10, data);
	return *this;
}

MyClass& MyClass::operator=(MyClass&& other) noexcept
{
	std::cout << "* Move assignment operator called" << std::endl;
	data = other.data;
	other.data = nullptr;
	return *this;
}

MyClass makeClassInstance()
{
	MyClass instance(1);
	return instance;
}

int main() {
	// You might have realised that in many situations actually copying the data isn't necessary.
	// Suppose we want to create instanceB from instanceA, and we know that we'll never use 
	// instanceA again afterwards. In this case we can just move the pointer to the data over from
	// instanceA to instanceB.
	// If you look above at the move constructor, that's what it does!
	// Notice it also sets the data pointer of instanceA to nullptr, this is necessary so the 
	// destructor of instanceA doesn't mess with the data (calling delete on nullptr has no effect).

	std::cout << "Making an instance of the class from scratch (regular constructor)" << std::endl;
	MyClass instanceA(1);


	std::cout << "If we call this function, it'll create an instance inside the function." << std::endl;
	std::cout << "It then calls the move constructor to make instanceB, as the temporary instance" << std::endl;
	std::cout << "inside the function is about to be destroyed anyway." << std::endl;
	MyClass instanceB = makeClassInstance();

	std::cout << "Now we've defined a move constructor, std::vector will use this when re-allocating." << std::endl;
	std::cout << "Let's see this in action" << std::endl;
	std::cout << "Creating the vector" << std::endl;
	std::vector<MyClass> vector;

	std::cout << "Pushing back an instance of the class into the vector" << std::endl;
	std::cout << "This should call the copy constructor" << std::endl;
	vector.push_back(instanceA);

	std::cout << "Using emplace_back to make an instance of the class in-place in the list" << std::endl;
	std::cout << "this won't call the copy constructor to add this new instance, as we're making it from scratch" << std::endl;
	vector.emplace_back(1);

	std::cout << "Vector size " << vector.size() << " capacity " << vector.capacity() << std::endl;
	std::cout << "Each time we re-allocate, we have to copy over the data from the previous memory block and delete the old ones." << std::endl;

	std::cout << "Let's try adding some more to the vector" << std::endl;
	vector.emplace_back(1);
	std::cout << "Vector size " << vector.size() << " capacity " << vector.capacity() << std::endl;

	std::cout << "and again..." << std::endl;
	vector.emplace_back(1);
	std::cout << "Vector size " << vector.size() << " capacity " << vector.capacity() << std::endl;

	std::cout << "Exiting the program, all the destructors should be called" << std::endl;

	return 0;
}
