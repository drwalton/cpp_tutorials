#include <algorithm>
#include <iostream>
#include <list>

class Resource
{
	int value;
public:
	Resource(int v) :value(v) {}
	~Resource() { std::cout << "* Resource deleted" << std::endl; }
};

class Owner
{
	std::shared_ptr<Resource> resource_;
	std::unique_ptr<Resource> otherResource_;
public:
	Owner() :otherResource_(new Resource(1)) {};
	Owner& resource(std::shared_ptr<Resource> r)
	{
		resource_ = r;
		return *this;
	}
	const std::shared_ptr<Resource> resource() { return resource_; };
};

std::list<Owner> makeOwners() 
{
	auto resource = std::make_shared<Resource>(10);

	std::cout << "Resource use count: " << resource.use_count() << std::endl;

	std::list<Owner> owners;

	for (size_t i = 0; i < 5; ++i) {
		Owner owner;
		owner.resource(resource);
		owners.push_back(owner);
	}

	std::cout << "Resource use count: " << resource.use_count() << std::endl;

	return owners;
}

int main() {

	// shared_ptr lets you manage a shared resource, that might have multiple owners.
	// It keeps a reference count, that tracks how many references to the pointed object
	// exist in the code. If nothing is left that owns the pointed resource, it's deleted.
	// They're useful for shared objects (e.g. a shader used by multiple meshes).

	// You can access the reference coutner using use_count(). Note that this includes
	// the reference managed by the shared_ptr itself!
	// A value of 0 means the shared_ptr doesn't store anything (it's nullptr)
	// A value of 2 or greater means there's at least one reference in the code
	// When the count drops to 1 there are no code references to the pointed
	// object and it'll be deleted.

	{
		std::unique_ptr<Resource> ptr = std::make_unique<Resource>(1);
	}

	auto owners = makeOwners();
	std::cout << "Resource use count: " << owners.begin()->resource().use_count() << std::endl;

	std::cout << "Deleting the first owner object decrements the resource count" << std::endl;
	owners.erase(owners.begin());
	std::cout << "Resource use count: " << owners.begin()->resource().use_count() << std::endl;

	std::cout << "Deleting another owner object..." << std::endl;
	owners.erase(owners.begin());
	std::cout << "Resource use count: " << owners.begin()->resource().use_count() << std::endl;

	std::cout << "Deleting another owner object..." << std::endl;
	owners.erase(owners.begin());
	std::cout << "Resource use count: " << owners.begin()->resource().use_count() << std::endl;

	std::cout << "Deleting another owner object..." << std::endl;
	owners.erase(owners.begin());
	std::cout << "Resource use count: " << owners.begin()->resource().use_count() << std::endl;

	std::cout << "There's only one owner left (note use_count is 2)." << std::endl;
	std::cout << "When we delete this, the resource gets deleted." << std::endl;
	owners.erase(owners.begin());

}
