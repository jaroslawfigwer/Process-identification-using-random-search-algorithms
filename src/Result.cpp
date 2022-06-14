#include "Result.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>


Result::Result(const std::size_t numberOfParameters, const double distMin, const double distMax):
    distMin(distMin), distMax(distMax)
{
    parameters = generateRandomData(distMin, distMax, numberOfParameters);
}

std::vector<double> Result::generateRandomData(const double distMin, const double distMax, std::size_t size)
{
    static std::uniform_real_distribution<double> distribution(
        distMin,
        distMax);
    static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

    std::vector<double> data(size);
    std::generate(data.begin(), data.end(), []() { return distribution(generator); });
    return data;
}

std::ostream& operator<<(std::ostream& os, const Result& result)
{
	for (const auto& parameter : result.parameters)
	{
		os << parameter << ", ";
	}
	os << " Cost function: " << result.costFunction;
	return os;
}