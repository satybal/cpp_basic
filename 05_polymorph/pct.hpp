#pragma once
#include "istatistics.hpp"

class Pct : public IStatistics {
public:
	Pct(const double alpha): alpha{alpha / 100.} {}
    ~Pct() {
        delete[] result;
    }
	
	void update(double next) override;
	double eval() const override;
	const char * name() const override;

private:
	double k_value(const int k) const;
	const double alpha;
	std::vector<double> mutable vec;
    char* result = new char[6];
};
