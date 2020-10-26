#include <iostream>
#include <sstream>

void print(double* m, std::size_t rows, std::size_t columns) {
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

void transpose(double*& m, std::size_t rows, std::size_t columns) {
	if (rows == columns) {
		for (std::size_t i{0}; i < rows; ++i) {
			for (std::size_t j{i+1}; j < columns; ++j) {
				std::swap(m[i*columns + j], m[j*rows + i]);
			}
		}

		return;
	}

	double* tmp{new double[rows*columns]};

	for (std::size_t i{0}; i < columns; ++i) {
		for (std::size_t j{0}; j < rows; ++j) {
			tmp[i*rows + j] = m[j*columns + i];
		}
	}

	std::swap(m, tmp);

	delete[] tmp;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Usage: exercise02.x rows columns" << std::endl;
		exit(1);
	}

	std::size_t rows{0}, columns{0};
	
	for (int i{1}; i < argc; ++i) {
		std::istringstream is{argv[i]};
		switch (i) {
			case 1:
				is >> rows;
				break;
			case 2:
				is >> columns;
				break;
			default:
				std::cerr << "Error" << std::endl;
				exit(1);
		}
	}

	double* m{new double[rows * columns]};
	for (std::size_t i{0}; i < rows*columns; ++i) {
		m[i] = i;
	}

	std::cout << m << std::endl;
	std::cout << "original matrix:" << std::endl;
	print(m, rows, columns);

	transpose(m, rows, columns);
	
	std::cout << m << std::endl;
	std::cout << "transposed matrix:" << std::endl;
	print(m, columns, rows);

	delete[] m;
}
