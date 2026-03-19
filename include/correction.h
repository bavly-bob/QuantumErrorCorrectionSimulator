#pragma once
#include "quantumState.h"

class ErrorCorrector {
public:
    virtual ~ErrorCorrector() = default;
    virtual void correct(QuantumState& state) = 0;
};

class BitFlipErrorCorrector : public ErrorCorrector {
public:
    void correct(QuantumState& state) override;

private:
    SyndromeProb computeSyndromeProb(const QuantumState& state, int logicalQubit);
    int sampleSyndrome(const SyndromeProb& sample);
    void collapseToSyndrome(QuantumState& state, int logicalQubit, int targetSyndrome);
    int HammingWeight(int value, int base, int length);
};

class PhaseFlipErrorCorrector : public ErrorCorrector {
public:
    explicit PhaseFlipErrorCorrector(BitFlipErrorCorrector bitCorrector = BitFlipErrorCorrector{})
        : bitCorrector(bitCorrector) {}

    void correct(QuantumState& state) override;

private:
    BitFlipErrorCorrector bitCorrector;
    void applyHadamardBlock(QuantumState& state, int logicalQubit);
};
