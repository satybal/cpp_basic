#pragma once
#include "istatistics.hpp"

class Mean : public IStatistics {
public:
	Mean() {}
	Mean(const double sum, const size_t count): sum{sum}, count{count} {}

	void update(double next) override; 
	double eval() const override;
	const char * name() const override;

private:
	double sum = 0;
	size_t count = 0;
};
