#pragma once
#pragma once

#include <thread>
#include <functional>
#include <iostream>
#include <mutex>
#include <vector>
#include "Worker.h"

class Master
{
public:
	Master(const std::vector<double>& inputs, const std::vector<double>& outputs, const std::size_t iterations,
        const std::size_t numberOfParameters, const double distMin, const double distMax, const double precision);

    template<typename Algorithm>
	void Run();

private:
	unsigned mNumberOfCores;
    const std::size_t mNumberOfIterations;
	std::vector<double> mInputs;
    std::vector<double> mOutputs;
    const std::size_t mNumberOfParameters;
    const double distributionMin;
    const double distributionMax;
    const double precision;
	std::mutex standardOutLock;
};

template<typename Algorithm>
void Master::Run()
{
    std::vector<std::thread> at;
    Result result(mNumberOfParameters, distributionMin, distributionMax);
    for (unsigned n = 0; n < mNumberOfCores; n++) {
        at.push_back(std::thread(
                &Algorithm::Run,
                std::ref(mInputs),
                std::ref(mOutputs),
                mNumberOfIterations,
                precision,
                std::ref(result)));
    }

    for (auto& t : at) t.join();

    std::cout << result << std::endl;

}