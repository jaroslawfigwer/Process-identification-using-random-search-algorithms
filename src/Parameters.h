#pragma once

#include <vector>

struct Parameters {
    const std::vector<double>& inputs;
    const std::vector<double>& outputs;
    const std::size_t numberOfIterations;
    const double precision;
};
