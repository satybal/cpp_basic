#include "random_value.h"
#include <iostream>
#include <ctime>

int random_value(const int max_value) {
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	return std::rand() % max_value;
}