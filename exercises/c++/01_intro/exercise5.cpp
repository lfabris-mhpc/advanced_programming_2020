#include <iostream>
#include <limits>

int main() {
	std::size_t linewidth{0};
	std::cout << "Please input the maximum number of characters per line: ";
	std::cout.flush();

	while (!(std::cin >> linewidth) || !linewidth) {
		std::cout << "Please input a valid character limit" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << std::string(linewidth, '#') << std::endl;

	std::string line{""};
	while (std::getline(std::cin, line)) {
		if (line.size() > linewidth) {
			auto beginl = line.begin(), endl = line.end();
			for (auto iter = line.begin(); iter != line.end(); ++iter) {
				if (std::isspace(static_cast<unsigned char>(*iter))) {
					if (iter - beginl > linewidth) {
						*endl = '\n';
						beginl = endl;
					}

					endl = iter;
				}
			}

			if (line.end() - beginl > linewidth) {
				*endl = '\n';
			}
		}

		std::cout << line << std::endl;
	}
}
