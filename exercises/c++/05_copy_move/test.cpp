#include <iostream>

#include "List.hpp"

int main(void) {
	auto list = new List<int>{};
	std::cout << "newly created list: " << *list << "\n";

	int nodes = 1000;
	for (int i = 0; i < nodes; ++i) {
		list->insert(i, static_cast<Insertion_method>(i % 2));
	}
	std::cout << "after alternating push_*: " << *list << "\n";

	auto list2 = new List<int>{*list};
	std::cout << "deep copy (constructor): " << *list2 << "\n";
	std::cout << "original: " << *list << "\n";

	for (int i = 0; i < nodes; ++i) {
		list->insert(i, static_cast<Insertion_method>(i % 2));
	}

	auto list3 = *list;
	std::cout << "deep copy (assignment): " << list3 << "\n";
	std::cout << "original: " << *list << "\n";

	List<int> list4{std::move(*list)};
	std::cout << "using move (constructor): " << list4 << "\n";
	std::cout << "original: " << *list << "\n";

	List<int> list5 = std::move(list3);
	std::cout << "using move (assignment): " << list5 << "\n";
	std::cout << "original: " << list3 << "\n";
	
	list5 = std::move(*list2);
	std::cout << "using move (assignment): " << list5 << "\n";
	std::cout << "original: " << *list2 << "\n";

	std::cout << "before reset: " << list5 << "\n";
	list5.reset();
	std::cout << "after reset: " << list5 << "\n";
	std::cout.flush();

	//the first was moved from an empty list, the second from a non-empty one
	//without deletes, valgrind shows only 32B lost, thus the move to non-empty deletes the nodes
	delete list;
	delete list2;
}
