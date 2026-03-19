#include "quantumState.h"
#include "quantumGate.h"
#include "noise.h"
#include <random>

void BitFlipNoise::apply(QuantumState& state)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::bernoulli_distribution flip(p);

    for (int q = 0; q < state.getPhysicalQubits(); ++q)
        if (flip(gen))
            state.applyGate(Gate::pauliX(), q);
}

void PhaseFlipNoise::apply(QuantumState& state)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::bernoulli_distribution flip(p);

    for (int q = 0; q < state.getPhysicalQubits(); ++q)
        if (flip(gen))
            state.applyGate(Gate::pauliZ(), q);
}
