#include <iostream>
//string is included by the above header
#include <iomanip>

int main() {
	std::size_t counter{0};
	std::string previous{""};
	
	//the for loop version is arguably less readable, but has the advantage of giving a smaller scope to variable line
	//std::string line;
	//while (std::getline(std::cin, line)) {
	for (std::string line; std::getline(std::cin, line);) {
		if (!counter) {
			previous = std::move(line);
		} else if (line != previous) {
			std::cout << std::setw(7) << counter << " " << previous <<std::endl;
			counter = 0;
			previous = std::move(line);
		}
		
		++counter;
	}

	if (counter) {
		std::cout << std::setw(7) << counter << " " << previous <<std::endl;
	}
}
