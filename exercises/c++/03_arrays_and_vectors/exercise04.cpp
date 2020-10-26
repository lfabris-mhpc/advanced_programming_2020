#include <iostream>

#include <vector>
#include <map>
#include <unordered_map>

#include <algorithm>
#include <chrono>

using timeRes = std::chrono::microseconds;

void useVector(bool printCount) {
	std::vector<std::string> tokens;
	std::vector<std::size_t> counts;
	std::string token;
	
	auto start = std::chrono::high_resolution_clock::now();
	
	while (std::cin >> token) {
		auto lb = std::lower_bound(begin(tokens), end(tokens), token);
		auto pos{std::distance(begin(tokens), lb)};
		if (lb == end(tokens) || *lb != token) {

			tokens.emplace(lb, std::move(token));
			counts.insert(begin(counts) + pos, 1);
		} else {
			(*(begin(counts) + pos))++;
		}
	}

	auto finish = std::chrono::high_resolution_clock::now();
	auto buildup = std::chrono::duration_cast<timeRes>(finish-start);
	start = std::chrono::high_resolution_clock::now();

	if (!printCount) {
		for (auto& s : tokens) {
			std::cout << s << "\n";
		}
	} else {
		for (std::size_t i{0}; i < tokens.size(); ++i) {
			std::cout << tokens[i] << " " << counts[i] << "\n";
		}
	}
	
	finish = std::chrono::high_resolution_clock::now();
	auto traversal = std::chrono::duration_cast<timeRes>(finish-start);
	
	std::cout.flush();
	std::cout << "vector builup: " << buildup.count() << "s" << std::endl;
	std::cout << "vector traversal: " << traversal.count() << "s" << std::endl;
}

void useMap(bool printCount) {
	std::map<std::string, std::size_t> tokens;
	std::string token;

	auto start = std::chrono::high_resolution_clock::now();
	
	while (std::cin >> token) {
		tokens[token]++;
	}
	
	auto finish = std::chrono::high_resolution_clock::now();
	auto buildup = std::chrono::duration_cast<timeRes>(finish-start);
	start = std::chrono::high_resolution_clock::now();

	if (!printCount) {
		for (auto& p : tokens) {
			std::cout << p.first << "\n";
		}
	} else {
		for (auto& p : tokens) {
			std::cout << p.first << " " << p.second << "\n";
		}
	}
	
	finish = std::chrono::high_resolution_clock::now();
	auto traversal = std::chrono::duration_cast<timeRes>(finish-start);
	
	std::cout.flush();
	std::cout << "map builup: " << buildup.count() << "s" << std::endl;
	std::cout << "map traversal: " << traversal.count() << "s" << std::endl;
}

void useHashMap(bool printCount) {
	std::unordered_map<std::string, std::size_t> tokens;
	std::string token;

	auto start = std::chrono::high_resolution_clock::now();
	
	while (std::cin >> token) {
		tokens[token]++;
	}
	
	auto finish = std::chrono::high_resolution_clock::now();
	auto buildup = std::chrono::duration_cast<timeRes>(finish-start);
	start = std::chrono::high_resolution_clock::now();

	if (!printCount) {
		for (auto& p : tokens) {
			std::cout << p.first << "\n";
		}
	} else {
		for (auto& p : tokens) {
			std::cout << p.first << " " << p.second << "\n";
		}
	}
	
	finish = std::chrono::high_resolution_clock::now();
	auto traversal = std::chrono::duration_cast<timeRes>(finish-start);
	
	std::cout.flush();
	std::cout << "hashmap builup: " << buildup.count() << "s" << std::endl;
	std::cout << "hashmap traversal: " << traversal.count() << "s" << std::endl;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Usage: exercise04.x (vector|map|hashmap)" << std::endl;
		exit(1);
	}

	std::string token{argv[1]};
	if (token == "vector") {
		useVector(true);
	} else if (token == "map") {
		useMap(true);
	} else if (token == "hashmap") {
		useHashMap(true);
	} else {
		std::cerr << "unrecognized parameter value: " << token << "; must be one of vector, map, hashmap" << std::endl;
		exit(1);
	}
}
