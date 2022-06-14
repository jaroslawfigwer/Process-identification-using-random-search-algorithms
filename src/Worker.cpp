#include "Worker.h"

#include <cmath>
#include <limits>

std::mutex Worker::lock;

void Worker::Run(const Parameters& parameters, Result& result)
{
    for (std::size_t i = 0; i < parameters.numberOfIterations; ++i)
    {
        if (!result.continueCalculations)
        {
            break;
        }
        bool hasBetterResult = false;

        // Generate random parameters
        std::vector<double> newParameters = Result::generateRandomData(result.distMin, result.distMax, 
            result.parameters.size());

        // Calculate output
        std::vector<double> newOutput(parameters.inputs.size());
        for (std::size_t j = 0; j < parameters.inputs.size(); ++j)
        {
            newOutput[j] = (newParameters[0] + newParameters[1] * parameters.inputs[j]) / (newParameters[4] + newParameters[3] * parameters.inputs[j] + newParameters[2] * pow(parameters.inputs[j], 2));
        }

        // Calculate cost function
        double newCostFunction = 0;
        for (std::size_t j = 0; j < parameters.outputs.size(); ++j)
        {
            newCostFunction += pow(parameters.outputs[j] - newOutput[j], 2);
        }

        {
            std::lock_guard<std::mutex> lockGuard(lock);
            hasBetterResult = newCostFunction < result.costFunction;
            if (hasBetterResult)
            {
                result.costFunction = newCostFunction;
                result.parameters = newParameters;
                if (result.costFunction < parameters.precision)
                {
                    result.continueCalculations = false;
                }
            }
        }

        if (hasBetterResult) //Zoom with better precision
        {
            double localCostFunction = 0;
            SearchForBetterResultAroundPoint(result, newParameters, parameters.inputs, newOutput,
                localCostFunction, parameters.outputs, newCostFunction, 10, 1.0);


            SaveResults(parameters.precision, result, newParameters, newCostFunction, localCostFunction);

            SearchForBetterResultAroundPoint(result, newParameters, parameters.inputs, newOutput,
                localCostFunction, parameters.outputs, newCostFunction, 10, 0.1);

            SaveResults(parameters.precision, result, newParameters, newCostFunction, localCostFunction);

            SearchForBetterResultAroundPoint(result, newParameters, parameters.inputs, newOutput,
                localCostFunction, parameters.outputs, newCostFunction, 10, 0.001);

            SaveResults(parameters.precision, result, newParameters, newCostFunction, localCostFunction);
        }
    }
}

void Worker::SaveResults(const double precision,
                         Result &result,
                         const std::vector<double> &newParameters,
                         double newCostFunction,
                         double localCostFunction)
 {
     std::lock_guard<std::mutex> lockGuard(lock);
     if (localCostFunction < newCostFunction)
     {
         result.costFunction = newCostFunction;
         result.parameters = newParameters;
         if (result.costFunction < precision)
         {
             result.continueCalculations = false;
         }
     }
 }

void Worker::SearchForBetterResultAroundPoint(
        Result& result,
        std::vector<double>& newParameters,
        const std::vector<double>& inputs,
        std::vector<double>& newOutput,
        double& localCostFunction,
        const std::vector<double>& outputs,
        double& newCostFunction,
        const std::size_t iterations,
        const double range)
{
    std::vector<double> localParameters(result.parameters.size());

    for (std::size_t k = 0; k < iterations; ++k)
    {
        std::vector<double> jump = Result::generateRandomData(-range, range, result.parameters.size());

        for (std::size_t j = 0; j < newParameters.size(); ++j)
        {
            localParameters[j] = newParameters[j] + jump[j];
        }

        for (std::size_t j = 0; j < inputs.size(); ++j)
        {
            newOutput[j] = (localParameters[0] + localParameters[1] * inputs[j]) / (localParameters[4] + localParameters[3] * inputs[j] + localParameters[2] * pow(inputs[j], 2));
        }

        localCostFunction = 0;
        for (std::size_t j = 0; j < outputs.size(); ++j)
        {
            localCostFunction += pow(outputs[j] - newOutput[j], 2);
        }

        if (localCostFunction < newCostFunction)
        {
            newCostFunction = localCostFunction;
            newParameters = localParameters;
        }
    }
}
