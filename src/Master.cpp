#include "Master.h"

#include <iostream>


Master::Master(const std::vector<double>& inputs, const std::vector<double>& outputs, const std::size_t iterations,
	const std::size_t numberOfParameters, const double distMin, const double distMax, const double precision) :
		mInputs(inputs), mOutputs(outputs), mNumberOfIterations(iterations), mNumberOfParameters(numberOfParameters),
		distributionMin(distMin), distributionMax(distMax), precision(precision)
{
	mNumberOfCores = std::thread::hardware_concurrency();
}
