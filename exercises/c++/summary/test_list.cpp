#include <iostream>
#include <vector>
#include <algorithm>

#include "List.hpp"

int main(void) {
    auto list = new List<int>{};
    std::cout << "newly created list: " << *list << "\n";

    std::cout << "some inserts\n";
    int nodes = 5;
    for (int i = 0; i < nodes; ++i) {
        list->insert(i, static_cast<Insertion_method>((1 + i) % 2));
    }
    std::cout << "after alternating push_*: " << *list << "\n";

    std::cout << "list insert(r-value)\n";
    list->insert(13, Insertion_method::push_front);

    std::cout << "List copy constructor\n";
    auto list2 = new List<int>{*list};
    std::cout << "deep copy (constructor): " << *list2 << "\n";
    std::cout << "original: " << *list << "\n";

    std::cout << "some more inserts\n";
    for (int i = 0; i < nodes; ++i) {
        list->insert(i, static_cast<Insertion_method>(i % 2));
    }

    std::cout << "list copy assignment\n";
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

	list = new List<int>{};
	for (int i = 0; i < nodes; ++i) {
		list->insert(i, static_cast<Insertion_method>((1 + i) % 2));
	}
	std::cout << "after alternating push_*: " << *list << "\n";
	//std::sort(list->begin(), list->end());
	//std::cout << "after sort: " << *list << "\n";
	std::cout << "range-based for: [";
	for (const auto& v: *list) {
		std::cout << v << " ";
	}
	std::cout << "]" << std::endl;

	std::vector<int> vector(list->size());
	std::copy(list->begin(), list->end(), vector.begin());
	std::cout << "copied into vector: [";
	for (const auto& v: vector) {
		std::cout << v << " ";
	}
	std::cout << "]" << std::endl;

    // the first was moved from an empty list, the second from a non-empty one
    // without deletes, valgrind shows only 32B lost, thus the move to non-empty
    // deletes the nodes
    delete list;
    delete list2;
}
