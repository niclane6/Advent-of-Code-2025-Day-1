#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

int wrap(int currentValue, int delta) {
	const int capacity = 100; // This will always be 100 in this problem 
	int newValue = currentValue + delta;
	return (newValue % capacity + capacity) % capacity;
}

void turn(std::string input, int& dialCurrent) {
	char direction = input[0];
	input.erase(0, 1);
	int delta = std::stoi(input);

	if (direction == 'L') {
		dialCurrent = wrap(dialCurrent, -delta);
	}
	else {
		dialCurrent = wrap(dialCurrent, delta);
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
		turn(line, dialCurrent);
		if (dialCurrent == 0) { zeroCount += 1; }
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