#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
	std::vector<double> v;
	v.reserve(100);

	std::ifstream f{"temperatures.txt"};
	double temp, tempSum{0};
	while (f >> temp) {
		v.push_back(temp);
		tempSum += temp;
	}
	
	std::cout << "Average: " << (v.empty() ? 0 : tempSum / v.size()) << std::endl;

	std::sort(begin(v), end(v));
	std::cout << "Median: " << (v.empty() ? 0 : v[v.size()/2])<< std::endl;
}
