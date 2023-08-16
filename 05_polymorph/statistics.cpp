#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <cstring>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

// mimimum value
class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

// maximum value
class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::lowest()} {}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
};

// mean value
class Mean : public IStatistics {
public:
	void update(double next) override {
		sum += next;
		count++;
	}

	double eval() const override {
		return sum / count;
	}

	const char * name() const override {
		return "mean";
	}
private:
	double sum = 0;
	int count = 0;
};

// std value
class Std : public IStatistics {
public:

	void update(double next) override {
		vec.push_back(next);
	}

	double eval() const override {
	    const double sum = std::accumulate(vec.begin(), vec.end(), 0);
	    const auto m_size = size(vec);
		const double m_mean = sum / m_size;

		double sumOfSquares = 0;
		for (double value : vec) 
			sumOfSquares += pow(value - m_mean, 2);
		
		return sqrt(sumOfSquares / m_size);
	}

	const char * name() const override {
		return "std";
	}
private:
	std::vector<double> vec;
};

//pct value
class Pct : public IStatistics {
public:

	Pct(const double alpha): alpha{alpha / 100.} {}

	void update(double next) override {
		vec.push_back(next);
	}

	double eval() const override {

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

	const char * name() const override {
		const char* percent = std::to_string(int(alpha * 100)).c_str();
		char* result = new char[6];
		strcpy(result, "pct");
		strcat(result, percent);
		return result;
	}
private:

	double k_value(const int k) const {
		std::nth_element(vec.begin(), vec.begin() + k, vec.end());
		return vec[k];
	}

	const double alpha;
	std::vector<double> mutable vec;
};

int main() {

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	statistics[4] = new Pct{90};
	statistics[5] = new Pct{95};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}