#include <iostream>
#include <cmath>

void resize(std::size_t*& primes, std::size_t& length, std::size_t newLength) {
	if (newLength <= length) {
		std::cerr << "New length must be greater than old length" << std::endl;
		exit(-1);
	}

	std::size_t* ret{new std::size_t[newLength]};

	for (std::size_t i{0}; i < length; ++i) {
		ret[i] = primes[i];
	}

	delete[] primes;

	primes = ret;
	length = newLength;
}

int main() {
	std::size_t n{100};
	
	//Dusart: pi(n) <= 1 + (n / std::log(n)) * (1 + 1.2762 / std::log(n))
	//the alternative is starting with a small array and resizing; classic implementation uses a factor, but it can be wasteful
	std::size_t length{static_cast<std::size_t>(1 + (n / std::log(n)) * (1 + 1.2762 / std::log(n)))};
	std::size_t* primes{new std::size_t[length]};
	primes[0] = 2;
	std::size_t values{1};

	int resizes{0};

	//iterate on odd integers > 1
	for (std::size_t i{3}; i <= n; i += 2) {
		bool divided{false};
		//skip test dividing by 2; test up to sqrt(i)
		for (std::size_t j = 1; j < values && primes[j] * primes[j] <= i; ++j) {
			if (i % primes[j] == 0) {
				divided = true;
				break;
			}
		}

		if (divided) {
			continue;
		}
		
		//using Dusart's result, this is never called
		/*
		if (values == length) {
			resize(primes, length, length * 2);
			++resizes;
		}
		*/
		
		primes[values++] = i;
	}

	for (std::size_t i = 0; i < values; ++i) {
		std::cout << primes[i] << std::endl;
	}

	//std::cout << "resizes: " << resizes << " values: " << values << " length: " << length << std::endl;

	delete[] primes;
}
