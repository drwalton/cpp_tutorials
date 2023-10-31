#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>


int main() {
	// Let's have a look at how std::vector really works!
	// Vector's actually quite an unusual data structure, that doesn't have an equivalent in many other
	// languages.
	std::vector<int> myVec;

	// Vectors have a size, which reflects the number of elements added to them.
	// They also have a capacity, which is the amount of memory allocated to store the elements.
	// At the start our vector is of size 0. Its capacity is also 0.
	std::cout << "Vector size " << myVec.size() << " capacity " << myVec.capacity() << std::endl;

	// As you can see, as we push back more elements, the vector's size increases to match.
	// The capacity varies differently. In order to avoid allocating memory too often, the vector class
	// adds memory in chunks, in a heuristic way. 
	// For me it reallocated to sizes 0, 1, 2, 3, 4, 6, 9, 13 and 28
	// exact numbers may depend on your c++ implementation.
	for (size_t i = 0; i < 20; ++i) {
		myVec.push_back(i);
		std::cout << "Vector size " << myVec.size() << " capacity " << myVec.capacity() << std::endl;
	}

	// For optimal std::vector performance it's in principle best to tell it how many things you plan
	// to add at the start, so it allocates the right amount of memory once. For example:
	std::vector<int> myVec2(20);
	// But if you don't know how big it should be, this clever allocation strategy keeps things pretty
	// fast even if you start off empty and use push_back().
	

	// Let's save the results to a csv file so we can do a nice line plot.
	// A copy of my line plot is in images/std_vector_allocation.jpg
	std::vector<int> myVec3;

	std::ofstream outFile("results.csv");
	outFile << "size, capacity\n";
	outFile << myVec3.size() << ", " << myVec3.capacity() << "\n";
	for (size_t i = 0; i < 500; ++i) {
		myVec3.push_back(i);
		outFile << myVec3.size() << ", " << myVec3.capacity() << "\n";
	}

	return 0;
}
