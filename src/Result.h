#pragma once

#include <atomic>
#include <iostream>
#include <vector>
#include <limits>

struct Result
{
	Result(const std::size_t numberOfParameters, const double distMin, const double distMax);

	static std::vector<double> generateRandomData(const double distMin, const double distMax, std::size_t size);

	double costFunction { std::numeric_limits<double>::max() };
	std::vector<double> parameters;
	const double distMin;
	const double distMax;
	std::atomic<bool> continueCalculations{true};
};

std::ostream& operator<<(std::ostream& os, const Result& result);