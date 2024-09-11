
#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include "NeuralNetwork.hpp"
#include <vector>

struct SnakeAgent {
    NeuralNetwork brain;
    double fitness;
};

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationSize, int inputSize, int hiddenSize, int outputSize);
    
    // Evolve the population to the next generation
    void Evolve();
    
    // Get the population of snake agents
    std::vector<SnakeAgent>& GetPopulation() { return population; }
    
private:
    // Select the best-performing agents for reproduction
    SnakeAgent SelectParent();
    
    // Perform crossover between two parents
    NeuralNetwork Crossover(const NeuralNetwork& parent1, const NeuralNetwork& parent2);
    
    // Apply mutation to a neural network
    void Mutate(NeuralNetwork& network);
    
    int populationSize;
    std::vector<SnakeAgent> population;
    
    double mutationRate = 0.01;
};

#endif // GENETIC_ALGORITHM_HPP
