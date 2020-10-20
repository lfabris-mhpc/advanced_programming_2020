#include <iostream>
#include <limits>

template<typename T>
T* getValues(const std::size_t length) {
	T* ret{new T[length]};
	if (!ret) {
		exit(-1);
	}

	for (std::size_t i = 0; i < length; ++i) {
		while (!(std::cin >> ret[i])) {
			std::cout << "Invalid value; retry" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	return ret;
}

template<typename T>
void printReverse(const T* const values, const std::size_t length) {
	for (std::size_t i = length - 1; i != 0; --i) {
		std::cout << values[i] << "\n";
	}

	if (length) {
		std::cout << *values << std::endl;
	}
}

int main() {
	std::cout << "Please input the length of the array: ";
	std::cout.flush();

	std::size_t length{0};
	while (!(std::cin >> length)) {
		std::cout << "Invalid value; retry" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cout << "Please input " << length << " integers" << std::endl;
	auto valuesInt = getValues<int>(length);

	std::cout << "Reversed array:" << std::endl;
	printReverse(valuesInt, length);

	delete[] valuesInt;
	valuesInt = nullptr;

	std::cout << "Please input " << length << " doubles" << std::endl;
	auto valuesDouble = getValues<double>(length);
	std::cout << "Reversed array:" << std::endl;
	printReverse(valuesDouble, length);

	delete[] valuesDouble;
	valuesDouble = nullptr;
}
