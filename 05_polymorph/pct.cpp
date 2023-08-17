#include "pct.hpp"

void Pct::update(double next) {
	vec.push_back(next);
}

double Pct::eval() const {

	auto N = size(vec);	               

	auto K = int(alpha * (N - 1));

	auto aN = N * alpha;

	if (fabs(K + 1 - aN) < (1 / N)) {
		return (k_value(K) + k_value(K+1)) / 2;
	} else if ((K + 1) < aN) {
		return k_value(K+1);
	} else {
		return k_value(K);
	}
}

const char * Pct::name() const {
	const char* percent = std::to_string(int(alpha * 100)).c_str();
	strcpy(result, "pct");
	strcat(result, percent);
	return result;
}
double Pct::k_value(const int k) const {
	std::nth_element(vec.begin(), vec.begin() + k, vec.end());
	return vec[k];
}
