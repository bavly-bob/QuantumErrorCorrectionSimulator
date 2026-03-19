#pragma once
#include "quantumState.h"

class NoiseModel {
public:
    virtual void apply(QuantumState& state) = 0;
};

class BitFlipNoise : public NoiseModel {
    double p;
public:
    BitFlipNoise(double prob) : p(prob) {}
    void apply(QuantumState& state) override;
};

class PhaseFlipNoise : public NoiseModel {
    double p;
public:
    PhaseFlipNoise(double prob) : p(prob) {}
    void apply(QuantumState& state) override;
};