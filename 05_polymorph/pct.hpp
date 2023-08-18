#pragma once
#include "istatistics.hpp"

class Pct : public IStatistics {
public:
	Pct(const double percentile): 
		alpha{percentile / 100.},
		m_name{"pct" + std::to_string(int(percentile))} {}
	
	void update(double next) override;
	double eval() const override;
	const char * name() const override;

private:
	double k_value(const int k) const;
	const double alpha;
	std::vector<double> mutable vec;
	const std::string m_name;
};
