#include "std.hpp"

void Std::update(double next) {
	vec.push_back(next);
	sum += next;
}

double Std::eval() const {
	const auto m_size = size(vec);
	const double m_mean = Mean(sum, m_size).eval();

	double sumOfSquares = 0;
	for (double value : vec) 
		sumOfSquares += pow(value - m_mean, 2);
		
	return sqrt(sumOfSquares / m_size);
}

const char * Std::name() const {
	return "std";
}

