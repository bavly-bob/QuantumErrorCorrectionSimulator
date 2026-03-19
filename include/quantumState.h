#pragma once
#include <vector>
#include <complex>
#include "quantumGate.h"

struct SyndromeProb {
    std::vector<double> probs;
    SyndromeProb(int repetitionCode)
    {
        int numSyndromes = 1 << (repetitionCode > 0 ? repetitionCode - 1 : 0);
        probs.resize(numSyndromes, 0.0);
    }
    double& operator[](int i) { return probs[i]; }
    const double& operator[](int i) const { return probs[i]; }
};

class BitFlipErrorCorrector;
class PhaseFlipErrorCorrector;
class BitFlipNoise;
class PhaseFlipNoise;

class QuantumState {
public:
    QuantumState(int n, int repetitionCode);
    int size() const { return static_cast<int>(amplitudes.size()); }
    std::complex<double> getAmplitude(int i) const { return amplitudes[i]; }
    void setAmplitude(int i, std::complex<double> val) { amplitudes[i] = val; }
    void applyGate(const Gate &gate, int target);
    void applyCNOT(int control, int target);
    void normalize();
    void encode(int logicalQubit);
    int measure();
    void collapseLogical(int logicalQubit, int value);
    int measureAllLogical();
    int getPhysicalQubits() const { return logicalQubits * repetitionCode; }
    int getLogicalQubitCount() const { return logicalQubits; }
    int getRepetitionCode() const { return repetitionCode; }

private:
    friend class BitFlipErrorCorrector;
    friend class PhaseFlipErrorCorrector;
    friend class BitFlipNoise;
    friend class PhaseFlipNoise;

    int HammingWeight(int state, int base, int length);
    int sampleSyndrome(const SyndromeProb& sample);
    void collapseToSyndrome(int logicalQubit, int targetSyndrome);
    SyndromeProb computeSyndromeProb(int logicalQubit);

    int logicalQubits;
    int repetitionCode;
    std::vector<std::complex<double>> amplitudes;
};
