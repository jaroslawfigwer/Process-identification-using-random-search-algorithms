#include <__bit_reference>

#pragma once

#include "Result.h"

#include <mutex>
#include <vector>

class Worker
{
public:
    static void Run(const std::vector<double>& inputs, const std::vector<double>& outputs,
		const std::size_t numberOfIterations, const double precision, Result& result);
	
private:
	static std::mutex lock;

	static void SearchForBetterResultAroundPoint(Result& result, std::vector<double>& newParameters, 
		const std::vector<double>& inputs, std::vector<double>& newOutput, double& localCostFunction,
		const std::vector<double>& outputs, double& newCostFunction, const std::size_t iterations,
		const double range);

    static void SaveResults(const double precision, Result &result, const std::vector<double> &newParameters,
                double newCostFunction,
                double localCostFunction);
};