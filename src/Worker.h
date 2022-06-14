#pragma once

#include "Result.h"
#include "Parameters.h"

#include <mutex>
#include <vector>

class Worker
{
public:
    static void Run(const Parameters& parameters, Result& result);
	
private:
	static std::mutex lock;

	static void SearchForBetterResultAroundPoint(
            Result& result,
            std::vector<double>& newParameters,
            const std::vector<double>& inputs,
            std::vector<double>& newOutput,
            double& localCostFunction,
            const std::vector<double>& outputs,
            double& newCostFunction, std::size_t iterations,
            double range
        );

    static void SaveResults(
            double precision,
            Result &result,
            const std::vector<double> &newParameters,
            double newCostFunction,
            double localCostFunction
        );
};