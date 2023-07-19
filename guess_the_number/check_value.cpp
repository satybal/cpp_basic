#include <iostream>
#include <limits>
#include "check_value.h"

int check_value(const int target_value) {
	int current_value = 0;
	int attempts = 0;
	bool not_win = true;
	std::cout << "Enter your guess:" << std::endl;

    // std::cout << target_value << std::endl;

	do {
		attempts++;

		while (!(std::cin >> current_value)) {
			std::cout << "Please enter a positive number." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (current_value > target_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value < target_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		else {
			std::cout << "you win!" << std::endl;
			break;
		}
	} while(true);

	return attempts;
}
