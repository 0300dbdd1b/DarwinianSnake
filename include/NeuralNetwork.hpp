
#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include <vector>
#include <cmath>
#include <cstdlib>

class NeuralNetwork {
public:
    NeuralNetwork(int inputSize, int numHiddenLayers, int neuronsPerLayer, int outputSize);

    std::vector<double> FeedForward(const std::vector<double>& inputs);

private:
    void InitializeWeights();
    double Sigmoid(double x);

    std::vector<std::vector<std::vector<double>>> weights; // Weights for layers
    int inputSize, outputSize;
    int numHiddenLayers, neuronsPerLayer;
};

#endif // NEURAL_NETWORK_HPP
