#include "Master.h"

#include <iostream>


Master::Master(const Parameters& parameters,
               const std::size_t numberOfParameters,
               const double distMin,
               const double distMax
): mParameters(parameters), mNumberOfParameters(numberOfParameters), distributionMin(distMin), distributionMax(distMax)
{
	mNumberOfCores = std::thread::hardware_concurrency();
}
