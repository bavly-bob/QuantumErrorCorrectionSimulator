#include "quantumState.h"
#include <cmath>
#include <random>
#include <complex>
#include <algorithm>

QuantumState::QuantumState(int n)
{
    numQubits = n * 3;
    amplitudes.resize(1 << numQubits);
    amplitudes[0] = 1.0;   // |000...0>
}

void QuantumState::encode(int logicalQubit)
{
    int physicalQubit = logicalQubit * 3;
    applyCNOT(physicalQubit, physicalQubit + 1);
    applyCNOT(physicalQubit, physicalQubit + 2);
}

int QuantumState::measure()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dist(0.0, 1.0);

    double r = dist(gen);
    double cumulative = 0.0;

    for (int i = 0; i < amplitudes.size(); i++)
    {
        cumulative += norm(amplitudes[i]);

        if (r < cumulative)
        {
            // collapse
            fill(amplitudes.begin(), amplitudes.end(), 0.0);

            amplitudes[i] = 1.0;
            return i;
        }
    }

    return static_cast<int>(amplitudes.size()) - 1; // should never happen and casting to slient the warning in cmake
}

int QuantumState::measureAllLogical(int numLogicalQubits)
{
    int rawResult = measure();  // collapse physical state once

    int logicalResult = 0;
    for (int lq = 0; lq < numLogicalQubits; ++lq)
    {
        int base = lq * 3;
        int b0 = (rawResult >> base) & 1;
        int b1 = (rawResult >> (base + 1)) & 1;
        int b2 = (rawResult >> (base + 2)) & 1;
        int majority = (b0 + b1 + b2 >= 2) ? 1 : 0;
        logicalResult |= (majority << lq);  // pack into bit lq
    }
    return logicalResult;
}


SyndromeProb QuantumState::computeSyndromeProb(int logicalQubit)
{
    int q0 = logicalQubit * 3;
    int q1 = q0 + 1;
    int q2 = q0 + 2;

    SyndromeProb s;
    int dim = 1 << numQubits;

    for (int i = 0; i < dim; i++)
    {
        double p = std::norm(amplitudes[i]);
        if (p == 0.0) continue;

        int b0 = (i >> q0) & 1;
        int b1 = (i >> q1) & 1;
        int b2 = (i >> q2) & 1;

        int S1 = b0 ^ b1;
        int S2 = b1 ^ b2;

        if (S1 == 0 && S2 == 0) s.p00 += p;
        else if (S1 == 1 && S2 == 0) s.p10 += p;
        else if (S1 == 1 && S2 == 1) s.p11 += p;
        else if (S1 == 0 && S2 == 1) s.p01 += p;
    }

    return s;
}

std::pair<int,int> QuantumState::sampleSyndrome(const SyndromeProb& sample)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::vector<double> probs = {sample.p00, sample.p10, sample.p11, sample.p01};

    std::discrete_distribution<int> dist(probs.begin(), probs.end());
    int result = dist(gen);

    switch(result)
    {
        case 0: return {0,0};
        case 1: return {1,0};
        case 2: return {1,1};
        case 3: return {0,1};
        default: return {0,0}; // safety fallback
    }
}

void QuantumState::collapseToSyndrome(int logicalQubit, int S1, int S2)
{
    int q0 = logicalQubit * 3;
    int q1 = q0 + 1;
    int q2 = q0 + 2;

    int dim = 1 << numQubits;

    for (int i = 0; i < dim; i++)
    {
        int b0 = (i >> q0) & 1;
        int b1 = (i >> q1) & 1;
        int b2 = (i >> q2) & 1;

        int s1 = b0 ^ b1;
        int s2 = b1 ^ b2;

        if (s1 != S1 || s2 != S2)
        {
            amplitudes[i] = 0.0;
        }
    }

    normalize(); // REQUIRED
}

void QuantumState::collapseLogical(int logicalQubit, int value)
{
    int q0 = logicalQubit * 3;
    int q1 = q0 + 1;
    int q2 = q0 + 2;

    int dim = 1 << numQubits;

    for (int i = 0; i < dim; i++)
    {
        int b0 = (i >> q0) & 1;
        int b1 = (i >> q1) & 1;
        int b2 = (i >> q2) & 1;

        if (b0 != value || b1 != value || b2 != value)
            amplitudes[i] = 0;
    }

    normalize();
}


void QuantumState::correctBitFlip(int logicalQubit)
{
    SyndromeProb probs = computeSyndromeProb(logicalQubit);
    std::pair<int, int> syndrome = sampleSyndrome(probs);
    int S1 = syndrome.first;
    int S2 = syndrome.second;

    collapseToSyndrome(logicalQubit, S1, S2);

    int q0 = logicalQubit * 3;
    int q1 = q0 + 1;
    int q2 = q0 + 2;

    if (S1 == 1 && S2 == 0)
        applyGate(Gate::pauliX(), q0);
    else if (S1 == 1 && S2 == 1)
        applyGate(Gate::pauliX(), q1);
    else if (S1 == 0 && S2 == 1)
        applyGate(Gate::pauliX(), q2);
}

void QuantumState::correctPhaseFlip(int logicalQubit)
{
    // will be implemented later 
}

void QuantumState::normalize()
{
    double sum = 0;

    for (int i = 0; i < amplitudes.size(); i++)
        sum += norm(amplitudes[i]);

    sum = sqrt(sum);

    if (sum > 0)
    {
        for (int i = 0; i < amplitudes.size(); i++)
            amplitudes[i] /= sum;
    }
}

void QuantumState::applyGate(const Gate& gate, int target)
{
    int dim = 1 << numQubits;

    int stride = 1 << target;
    int step = stride * 2;

    for (int base = 0; base < dim; base += step)
    {
        for (int offset = 0; offset < stride; offset++)
        {
            int i = base + offset;
            int j = i + stride;

            auto a = amplitudes[i];
            auto b = amplitudes[j];

            amplitudes[i] = gate.at(0,0) * a + gate.at(0,1) * b;
            amplitudes[j] = gate.at(1,0) * a + gate.at(1,1) * b;
        }
    }
}

void QuantumState::applyCNOT(int control, int target)
{
    if (control == target) return;

    std::size_t dim = amplitudes.size();
    std::size_t controlMask = 1ULL << control;
    std::size_t targetMask  = 1ULL << target;

    for (std::size_t i = 0; i < dim; ++i)
    {
        if ((i & controlMask) && !(i & targetMask))
        {
            std::size_t j = i | targetMask;
            std::swap(amplitudes[i], amplitudes[j]);
        }
    }
}