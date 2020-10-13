#include <iostream>
#include <limits>

constexpr auto IGNORE{std::numeric_limits<std::streamsize>::max()};

int get_int() {
	std::cout << "Please input an int" << std::endl;
	int i;
	while (!(std::cin >> i)) {
		std::cin.clear();
		std::cin.ignore(IGNORE, '\n');
		std::cout << "Please input a valid int" << std::endl;
	}

	std::cin.clear();
	std::cin.ignore(IGNORE, '\n');

	return i;
}

double get_double() {
	std::cout << "Please input a double" << std::endl;
	double d;
	while (!(std::cin >> d)) {
		std::cin.clear();
		std::cin.ignore(IGNORE, '\n');
		std::cout << "Please input a valid double" << std::endl;
	}

	std::cin.clear();
	std::cin.ignore(IGNORE, '\n');

	return d;
}

int main() {
	int i{get_int()};
	double d{get_double()};

	std::cout << "int i = " << i << "\n";
	std::cout << "double d = " << d << std::endl;
}
