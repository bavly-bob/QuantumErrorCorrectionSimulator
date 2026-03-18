#include "quantumState.h"
#include "quantumGate.h"
#include <random>

void QuantumState::applyBitFlipNoise(double prob) 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::bernoulli_distribution flip(prob);

    for (int q = 0; q < numQubits; q++)
        if (flip(gen))
            applyGate(Gate::pauliX(), q); 
}

void QuantumState::applyPhaseFlipNoise(double prob) 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::bernoulli_distribution flip(prob);

    for (int q = 0; q < numQubits; q++)
        if (flip(gen))
            applyGate(Gate::pauliZ(), q); 
}