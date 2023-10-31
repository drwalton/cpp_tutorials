#include <algorithm>
#include <iostream>
#include <vector>

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
	// Now we know how vectors work, let's see how that interacts with the copy constructor
	std::cout << "Making an instance of the class from scratch (regular constructor)" << std::endl;
	MyClass instanceA(1);

	std::cout << "Creating the vector" << std::endl;
	std::vector<MyClass> vector;

	std::cout << "Pushing back an instance of the class into the vector" << std::endl;
	std::cout << "This should call the copy constructor" << std::endl;
	vector.push_back(instanceA);

	std::cout << "Using emplace_back to make an instance of the class in-place in the list" << std::endl;
	std::cout << "this won't call the copy constructor to add this new instance, as we're making it from scratch" << std::endl;
	vector.emplace_back(1);

	std::cout << "Wait what ? Why did the copy constructor and destructor get called ?" << std::endl;
	std::cout << "Note the vector was re-allocated (to size 2)" << std::endl;
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
