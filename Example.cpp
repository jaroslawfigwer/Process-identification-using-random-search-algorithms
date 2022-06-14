#include <cmath>
#include <random>
#include <vector>
#include <algorithm>

#include "src/Master.h"

int main()
{
    const double minInput = -10.0;
    const double maxInput = 10.0;
    const std::size_t inputSize = 200;

    static std::uniform_real_distribution<double> distribution(
        minInput,
        maxInput);
    static std::default_random_engine generator;

    std::vector<double> inputs(inputSize);
    std::generate(inputs.begin(), inputs.end(), []() { return distribution(generator); });

    std::vector<double> outputs(inputs.size());
    for (std::size_t i = 0; i < inputs.size(); ++i)
    {
        outputs[i] = (1 - 0.8 * inputs[i]) / (1 - 1.5 * inputs[i] + 0.7 * pow(inputs[i], 2));
    }

    const std::size_t iterations = 100000;
    const std::size_t numberOfParameters = 5;
    const double distMin = -10.0;
    const double distMax = 10.0;
    const double precision = 0.05;

    const Parameters parameters = { inputs, outputs, iterations, precision };

    Master master(parameters, numberOfParameters, distMin, distMax);
    master.Run<Worker>();
}
