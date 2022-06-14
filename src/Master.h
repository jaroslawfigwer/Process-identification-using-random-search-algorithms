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
	Master(const Parameters& parameters, std::size_t numberOfParameters, double distMin, double distMax);

    template<typename Algorithm>
	void Run();

private:
    const Parameters& mParameters;
	unsigned mNumberOfCores;
    const std::size_t mNumberOfParameters;
    const double distributionMin;
    const double distributionMax;
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
                std::ref(mParameters),
                std::ref(result)));
    }

    for (auto& t : at) t.join();

    std::cout << result << std::endl;

}