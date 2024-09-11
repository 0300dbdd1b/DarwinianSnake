
#include "NeuralNetwork.hpp"
#include <algorithm>

// Constructor to initialize the neural network structure
NeuralNetwork::NeuralNetwork(int inputSize, int numHiddenLayers, int neuronsPerLayer, int outputSize)
    : inputSize(inputSize), numHiddenLayers(numHiddenLayers), neuronsPerLayer(neuronsPerLayer), outputSize(outputSize) {
    InitializeWeights();
}

// Initialize the weights between each layer with random values
void NeuralNetwork::InitializeWeights() {
    weights.resize(numHiddenLayers + 1); // +1 for input to first hidden layer and last hidden to output

    // Input layer to first hidden layer
    weights[0].resize(neuronsPerLayer, std::vector<double>(inputSize));
    for (auto& row : weights[0]) {
        for (auto& weight : row) {
            weight = (std::rand() / double(RAND_MAX)) * 2.0 - 1.0; // Random weight between -1 and 1
        }
    }

    // Hidden layers
    for (int l = 1; l < numHiddenLayers; ++l) {
        weights[l].resize(neuronsPerLayer, std::vector<double>(neuronsPerLayer));
        for (auto& row : weights[l]) {
            for (auto& weight : row) {
                weight = (std::rand() / double(RAND_MAX)) * 2.0 - 1.0;
            }
        }
    }

    // Last hidden layer to output layer
    weights[numHiddenLayers].resize(outputSize, std::vector<double>(neuronsPerLayer));
    for (auto& row : weights[numHiddenLayers]) {
        for (auto& weight : row) {
            weight = (std::rand() / double(RAND_MAX)) * 2.0 - 1.0;
        }
    }
}

// Feedforward process through the neural network
std::vector<double> NeuralNetwork::FeedForward(const std::vector<double>& inputs) {
    std::vector<double> hidden(neuronsPerLayer, 0.0);

    // First hidden layer activation
    for (int i = 0; i < neuronsPerLayer; ++i) {
        for (int j = 0; j < inputSize; ++j) {
            hidden[i] += weights[0][i][j] * inputs[j];
        }
        hidden[i] = Sigmoid(hidden[i]);
    }

    // Hidden layers processing
    for (int l = 1; l < numHiddenLayers; ++l) {
        std::vector<double> newHidden(neuronsPerLayer, 0.0);
        for (int i = 0; i < neuronsPerLayer; ++i) {
            for (int j = 0; j < neuronsPerLayer; ++j) {
                newHidden[i] += weights[l][i][j] * hidden[j];
            }
            newHidden[i] = Sigmoid(newHidden[i]);
        }
        hidden = newHidden;
    }

    // Output layer
    std::vector<double> output(outputSize, 0.0);
    for (int i = 0; i < outputSize; ++i) {
        for (int j = 0; j < neuronsPerLayer; ++j) {
            output[i] += weights[numHiddenLayers][i][j] * hidden[j];
        }
        output[i] = Sigmoid(output[i]);
    }

    return output;
}

// Sigmoid activation function
double NeuralNetwork::Sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}
