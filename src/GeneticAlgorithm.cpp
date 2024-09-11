
#include "GeneticAlgorithm.hpp"
#include <algorithm>
#include <random>

// Constructor to initialize the population of snake agents
GeneticAlgorithm::GeneticAlgorithm(int populationSize, int inputSize, int hiddenSize, int outputSize)
    : populationSize(populationSize) {
    population.reserve(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        // Explicitly initialize each agent with a NeuralNetwork
        SnakeAgent agent;
        agent.brain = NeuralNetwork(inputSize, hiddenSize, outputSize);
        agent.fitness = 0.0;
        population.push_back(agent);
    }
}


void GeneticAlgorithm::Evolve() {
    // Your logic for evolving the population goes here
}
