#pragma once
#include <vector>
#include <complex>
#include "quantumGate.h"

struct SyndromeProb {
    double p00 = 0;
    double p10 = 0;
    double p11 = 0;
    double p01 = 0;
};

class QuantumState {
public:
    QuantumState(int n);
    int size() const { return static_cast<int>(amplitudes.size()); }
    std::complex<double> getAmplitude(int i) const { return amplitudes[i]; }
    void setAmplitude(int i, std::complex<double> val) { amplitudes[i] = val; }
    void applyGate(const Gate &gate, int target);
    void applyCNOT(int control, int target);
    void applyBitFlipNoise(double prob);
    void applyPhaseFlipNoise(double prob);
    void normalize();
    void encode(int logicalQubit);
    int measure();
    void collapseLogical(int logicalQubit, int value);
    SyndromeProb computeSyndromeProb(int logicalQubit);
    std::pair<int, int> sampleSyndrome(const SyndromeProb& sample);
    void collapseToSyndrome(int logicalQubit, int S1, int S2);
    void correctBitFlip(int logicalQubit);
    void correctPhaseFlip(int logicalQubit);
    int measureAllLogical(int numLogicalQubits);

private:
    int numQubits;
    std::vector<std::complex<double>> amplitudes;
};