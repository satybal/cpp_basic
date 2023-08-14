#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

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
	Max() : m_max{std::numeric_limits<double>::min()} {}

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

	std::vector<double> vec;

	void update(double next) final {
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
};

class Pct95;

//pct value
class Pct90 : public Std {
public:

	virtual double getAlpha() const {
		return 0.9;
	}

	double eval() const override {
		const double alpha = getAlpha();

		std::vector<double> vecCopy = vec;
		std::sort(vecCopy.begin(), vecCopy.end());

		auto N = size(vecCopy);	               

		auto K = int(alpha * (N - 1));

		auto aN = N * alpha;

		if (fabs(K + 1 - aN) < (1 / N)) {
			return (vecCopy[K] + vecCopy[K+1]) / 2;
		} else if ((K + 1) < aN) {
			return vecCopy[K+1];
		} else {
			return vecCopy[K];
		}
	}

	const char * name() const override {
		return "pct90";
	}
};


// pct95 value
class Pct95 : public Pct90 {
public:

	double getAlpha() const override {
		return 0.95;
	}
	
	const char * name() const override {
		return "pct95";
	}
};

int main() {

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	statistics[4] = new Pct90{};
	statistics[5] = new Pct95{};

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