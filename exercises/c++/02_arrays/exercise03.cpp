#include <iostream>
#include <limits>
#include <cmath>

void prepareWindow(std::size_t* nums, const std::size_t length, std::size_t start) {
	for (std::size_t i{0}; i < length; ++i) {
		nums[i] = start + 2 * i;
	}
}

int main() {
	std::size_t n{0};
	std::cout << "Please input the inclusive upper bound of primes to print: ";
	std::cout.flush();
	while (!(std::cin >> n)) {
		std::cout << "Invalid value; retry" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	}

	if (!n) {
		return 0;
	}

	std::cout << 2 << std::endl;
	
	if (n == 1) {
		return 0;
	}
	
	const std::size_t sqrtn{static_cast<std::size_t>(std::sqrt(n))};
	const std::size_t sqrtni{(sqrtn - 3) / 2};
	std::size_t length{(n - 2) / 2};
	std::size_t* nums{new std::size_t[length]};
	std::size_t values{1};

	prepareWindow(nums, length, 3);

	for (std::size_t i{0}; i < sqrtni; ++i) {
		if (!nums[i]) {
			continue;
		}

		++values;
		std::cout << nums[i] << std::endl;

		for (std::size_t j{(nums[i] * nums[i] - 3) / 2}; j < length; j += nums[i]) {
			nums[j] = 0;
		}
	}

	for (std::size_t i{sqrtni}; i < length; ++i) {
		if (nums[i]) {
			++values;
			std::cout << nums[i] << std::endl;
		}
	}

	std::cout << "values: " << values << " length: " << length << std::endl;

	delete[] nums;
}
