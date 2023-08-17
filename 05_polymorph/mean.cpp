#include "mean.hpp"

void Mean::update(double next) {
	sum += next;
	count++;
}

double Mean::eval() const {
	return sum / count;
}

const char * Mean::name() const {
	return "mean";
}
