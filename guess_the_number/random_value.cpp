#include <random_value.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

int random_value(int level = 1, int max = 10) {
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	
	if (max != 10) { return std::rand() % max; }

	int max_value;

	if (level == 2) {
		std::cout << "Guess the number between 0 and 49";
		max_value = 50;
	}
	else if (level == 3) {
		std::cout << "Guess the number between 0 and 99";
		max_value = 100;
	}
	else {
		std::cout << "Guess the number between 0 and 9";
		max_value = 10;
	}

	return std::rand() % max_value;
}