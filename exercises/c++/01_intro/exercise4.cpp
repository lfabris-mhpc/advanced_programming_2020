#include <iostream>
#include <unordered_map>

const std::string usage{"Input format: 'VALUE UNIT'"};

int main() {
	using conv_data = std::pair<std::string, double>;
	std::unordered_map<std::string, conv_data> conversions;

	//length
	conversions.emplace("metre", conv_data{"m", 1});
	
	conversions.emplace("angstrom", conv_data{"m", 1E-10});
	conversions.emplace("fermi", conv_data{"m", 1E-15});
	conversions.emplace("foot", conv_data{"m", 0.3048});
	conversions.emplace("inch", conv_data{"m", 0.0254});
	conversions.emplace("league", conv_data{"m", 4828});
	conversions.emplace("mile", conv_data{"m", 1855.3176});
	conversions.emplace("shaku", conv_data{"m", 10 / 33.0});
	conversions.emplace("yard", conv_data{"m", 0.9144});

	double value{0};
	std::cin >> value;
	if (!std::cin) {
		std::cerr << usage << std::endl;
		
		conversions.clear();
		exit(EXIT_FAILURE);
	}

	std::string unit;
	std::cin >> unit;
	if (unit.empty()) {
		std::cerr << usage << std::endl;
		
		unit.clear();
		conversions.clear();
		exit(EXIT_FAILURE);
	}

	const auto iter = conversions.find(unit);
	if (iter == conversions.end()) {
		std::cerr << "Unknown unit of measure '" << unit << "'" << std::endl;
		
		conversions.clear();
		exit(EXIT_FAILURE);
	}

	std::cout << value * iter->second.second << " " << iter->second.first << std::endl;
}
