#pragma once
#include "istatistics.hpp"
#include "mean.hpp"

class Std : public IStatistics {
public:

	void update(double next) override;
	double eval() const override;
	const char * name() const override;
    
private:
	std::vector<double> vec;
	double sum = 0;
};
