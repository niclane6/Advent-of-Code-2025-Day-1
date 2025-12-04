#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

int wrap(int currentValue, int delta, int& zeroCount) {
	const int capacity = 100; // This will always be 100 in this problem 
	int newValue = currentValue + delta;
	int multipleCheck = static_cast<int>(std::abs(newValue / capacity));
	zeroCount += multipleCheck;
	return (newValue % capacity + capacity) % capacity;

}

void turn(std::string input, int& dialCurrent, int& zeroCount) {
	char direction = input[0];
	input.erase(0, 1);
	int delta = std::stoi(input);

	if (direction == 'L') {
		if (dialCurrent - delta < 0) {
			dialCurrent = wrap(dialCurrent, -delta, zeroCount);
			zeroCount++;
		}
		else {
			dialCurrent -= delta;
			if (dialCurrent == 0) { zeroCount += 1; }

		}

	}
	else {
		if (dialCurrent + delta > 100) {
			dialCurrent = wrap(dialCurrent, delta, zeroCount);
			zeroCount++;
		}
		else {
			dialCurrent += delta;
			if (dialCurrent == 0) { zeroCount += 1; }

		}

	}
}

void getPassword(std::string filename, int dialCurrent) {
	std::ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		throw std::runtime_error("Could not open file, aborting");
	}

	int zeroCount = 0;
	std::string line;
	while (std::getline(inputFile, line)) {
		turn(line, dialCurrent, zeroCount);
		//if (dialCurrent == 0) { zeroCount += 1; }
	}

	inputFile.close();

	std::cout << "The password is " << zeroCount << std::endl;
}

int main() {

	try {
		getPassword("input.txt", 50);
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}