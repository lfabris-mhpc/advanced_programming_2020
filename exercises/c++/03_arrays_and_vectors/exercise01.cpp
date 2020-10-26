#include <iostream>
#include <array>

template<std::size_t N>
void print(std::array<double, N>& m, std::size_t rows) {
	std::size_t columns{N / rows};

	for (std::size_t i{0}; i < rows; ++i) {
		std::cout << "[";
		for (std::size_t j{0}; j < columns; ++j) {
			if (j) {
				std::cout << ", ";
			}
			std::cout << m[i*columns + j];
		}
		std::cout << "]" << std::endl;
	}
}

template<std::size_t N>
void transpose(std::array<double, N>& m, std::size_t rows) {
	std::size_t columns{N / rows};
	if (columns == rows) {
		for (std::size_t i{0}; i < rows; ++i) {
			for (std::size_t j{i+1}; j < columns; ++j) {
				std::swap(m[i*columns + j], m[j*rows + i]);
			}
		}
		return;
	}
	std::array<double, N> tmp{};

	for (std::size_t i{0}; i < columns; ++i) {
		for (std::size_t j{0}; j < rows; ++j) {
			tmp[i*rows + j] = m[j*columns + i];
		}
	}

	std::swap(tmp, m);
}

int main(int argc, char** argv) {
	constexpr std::size_t rows{10}, columns{5};
	std::array<double, rows * columns> m;
	for (std::size_t i{0}; i < rows*columns; ++i) {
		m[i] = i;
	}

	std::cout << "original matrix:" << std::endl;
	print(m, rows);

	transpose(m, rows);
	
	std::cout << "transposed matrix:" << std::endl;
	print(m, columns);
}
