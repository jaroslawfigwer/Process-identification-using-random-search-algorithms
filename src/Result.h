#pragma once

#include <atomic>
#include <iostream>
#include <vector>
#include <limits>

struct Result
{
	Result(std::size_t numberOfParameters, double distMin, double distMax);

	static std::vector<double> generateRandomData(double distMin, double distMax, std::size_t size);

	double costFunction { std::numeric_limits<double>::max() };
	std::vector<double> parameters;
	const double distMin;
	const double distMax;
	std::atomic<bool> continueCalculations{true};
};

std::ostream& operator<<(std::ostream& os, const Result& result);