#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

void render(std::vector<bool> const& state, std::size_t rows, std::size_t columns) {
	for (std::size_t i{0}; i < rows + 2; ++i) {
		std::cout << "-";
	}
	std::cout << "\n";

	for (std::size_t i{0}; i < rows; ++i) {
		std::cout << "|";
		for (std::size_t j{0}; j < columns; ++j) {
			if (state[i*columns + j]) {
				std::cout << "@";
			} else {
				std::cout << " ";
			}

		}
		std::cout << "|\n";
	}
	
	for (std::size_t i{0}; i < rows + 2; ++i) {
		std::cout << "-";
	}
	std::cout << "\n";
	std::cout.flush();
}

void setCell(std::vector<bool>& state, std::size_t rows, std::size_t columns, std::size_t i, std::size_t j, bool value) {
	state[columns * (i % rows) + (j % columns)] = value;
}

bool getCell(std::vector<bool> const& state, std::size_t rows, std::size_t columns, std::size_t i, std::size_t j) {
	return state[columns * (i % rows) + (j % columns)];
}

int liveNeighbors(std::vector<bool> const& state, std::size_t rows, std::size_t columns, std::size_t i, std::size_t j) {
	int cnt = 0;
	cnt += getCell(state, rows, columns, i+rows-1, j+columns-1);
	cnt += getCell(state, rows, columns, i+rows-1, j);
	cnt += getCell(state, rows, columns, i+rows-1, j+1);
	
	cnt += getCell(state, rows, columns, i, j+columns-1);
	cnt += getCell(state, rows, columns, i, j+1);
	
	cnt += getCell(state, rows, columns, i+1, j+columns-1);
	cnt += getCell(state, rows, columns, i+1, j);
	cnt += getCell(state, rows, columns, i+1, j+1);

	return cnt;
}

void update(std::vector<bool>& prev, std::vector<bool>& next
		, std::size_t rows, std::size_t columns) {
	for (std::size_t i{0}; i < rows; ++i) {
		for (std::size_t j{0}; j < columns; ++j) {
			int neighbors{liveNeighbors(prev, rows, columns, i, j)};
			bool alive{prev[columns*i + j]};

			if (!alive && neighbors == 3) {
				alive = true;
			} else if (alive && (neighbors == 2 || neighbors == 3)) {
				alive = true;
			} else {
				alive = false;
			}

			next[columns*i + j] = alive;
		}
	}
}

void makeBlinker(std::vector<bool>& state, std::size_t rows, std::size_t columns, std::size_t i, std::size_t j) {
	setCell(state, rows, columns, i, j, true);  
	setCell(state, rows, columns, i, j+1, true);  
	setCell(state, rows, columns, i, j+2, true);  
}

void makeGlider(std::vector<bool>& state, std::size_t rows, std::size_t columns, std::size_t i, std::size_t j) {
	setCell(state, rows, columns, i, j+1, true);  
	setCell(state, rows, columns, i+1, j+2, true);  
	setCell(state, rows, columns, i+2, j, true);  
	setCell(state, rows, columns, i+2, j+1, true);  
	setCell(state, rows, columns, i+2, j+2, true);
}

int main(int argc, char** argv) {
	/*
	if (argc < 3) {
		std::cerr << "Usage: exercise06 rows columns" << std::endl;
		exit(1);
	}
	*/
	std::size_t rows{60};//std::stoul(argv[1])};
	std::size_t columns{60};//std::stoul(argv[2])};
	std::size_t frames{1000};
	
	std::vector<bool> states[2];
	states[0] = std::vector<bool>(rows*columns, false);
	states[1] = std::vector<bool>(rows*columns, false);

	makeBlinker(states[1], rows, columns, 234, 45);
	makeBlinker(states[1], rows, columns, 3543, 443);
	makeBlinker(states[1], rows, columns, 3453, 12);
	makeBlinker(states[1], rows, columns, 265342, 23);
	makeBlinker(states[1], rows, columns, 17361, 98);

	makeGlider(states[1], rows, columns, 1, 1);
	makeGlider(states[1], rows, columns, 43, 32);
	makeGlider(states[1], rows, columns, 28, 56);

	render(states[1], rows, columns);

	for (std::size_t frame{0}; frame < frames; ++frame) {
		std::this_thread::sleep_for (std::chrono::milliseconds(100));

		std::size_t upd{frame % 2};
		std::fill(begin(states[upd]), end(states[upd]), false);
		update(states[(upd+1) % 2], states[upd], rows, columns);
		render(states[upd], rows, columns);
	}
}
