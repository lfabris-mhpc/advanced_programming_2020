#include <iostream>
#include <vector>
#include <algorithm>

#include "vector.hpp"

template<typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& t) {
	return os << "(" << t.first << ", " << t.second << ")";
}

struct Foo {
	Foo() {std::cout << "foo ctor" << std::endl;}
};

std::ostream& operator<<(std::ostream& os, const Foo& t) {
	return os << "(Foo)";
}

int main() {
	/*
	std::vector<int> v;
	//best initializer
	std::vector<int> v1(4, 2);
	//initializer lists ctors have the highest priority
	std::vector<int> v2{4, 2};

	std::cout << "v1: ";
	std::for_each(v1.begin(), v1.end(), [] (const auto& e) {std::cout << e << " ";});
	std::cout << std::endl;
	std::cout << "v2: ";
	std::for_each(v2.begin(), v2.end(), [] (const auto& e) {std::cout << e << " ";});
	std::cout << std::endl;
	*/

	vector<std::pair<int, std::string>> v{};

	//v.push_back(std::make_pair(1, "asd"));
	v.emplace_back(1, "asd");
	v.push_back(std::make_pair(11, "asdasd"));
	v.emplace_back(2, "22");

	std::cout << v << std::endl;

	//since it uses new internally, it initializes all the elements of array
	vector<Foo> vfoo{{}, {}};

	//vfoo.emplace_back();

	std::cout << vfoo << std::endl;
}
