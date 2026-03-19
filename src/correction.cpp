#include "correction.h"
#include <algorithm>
#include <cmath>
#include <complex>
#include <random>

using namespace std;

namespace {
int syndromeForIndex(int index, int base, int repetitionCode)
{
    int syndrome = 0;
    for (int j = 0; j < repetitionCode - 1; ++j)
    {
        int b_i = (index >> (base + j)) & 1;
        int b_next = (index >> (base + j + 1)) & 1;
        syndrome |= ((b_i ^ b_next) << j);
    }
    return syndrome;
}
}

void BitFlipErrorCorrector::correct(QuantumState& state)
{
    const int repetitionCode = state.getRepetitionCode();
    const int logicalQubits = state.getLogicalQubitCount();

    if (repetitionCode < 2)
        return;

    for (int logicalQubit = 0; logicalQubit < logicalQubits; ++logicalQubit)
    {
        const int base = logicalQubit * repetitionCode;
        SyndromeProb probs = computeSyndromeProb(state, logicalQubit);
        int syndrome = sampleSyndrome(probs);
        collapseToSyndrome(state, logicalQubit, syndrome);

        int bestError = 0;
        int bestWeight = repetitionCode + 1;
        const int totalPatterns = 1 << repetitionCode;

        for (int e = 0; e < totalPatterns; ++e)
        {
            if (syndromeForIndex(e, 0, repetitionCode) != syndrome)
                continue;

            int w = HammingWeight(e, 0, repetitionCode);
            if (w < bestWeight)
            {
                bestWeight = w;
                bestError = e;
            }
        }

        for (int j = 0; j < repetitionCode; ++j)
        {
            if ((bestError >> j) & 1)
                state.applyGate(Gate::pauliX(), base + j);
        }
    }
}

SyndromeProb BitFlipErrorCorrector::computeSyndromeProb(const QuantumState& state, int logicalQubit)
{
    SyndromeProb s(state.getRepetitionCode());
    const int dim = 1 << state.getPhysicalQubits();
    const int base = logicalQubit * state.getRepetitionCode();

    for (int i = 0; i < dim; ++i)
    {
        const double p = std::norm(state.amplitudes[i]);
        if (p == 0.0) continue;
        s[syndromeForIndex(i, base, state.getRepetitionCode())] += p;
    }
    return s;
}

int BitFlipErrorCorrector::sampleSyndrome(const SyndromeProb& sample)
{
    static std::mt19937 gen(std::random_device{}());
    std::discrete_distribution<int> dist(sample.probs.begin(), sample.probs.end());
    return dist(gen);
}

void BitFlipErrorCorrector::collapseToSyndrome(QuantumState& state, int logicalQubit, int targetSyndrome)
{
    const int dim = 1 << state.getPhysicalQubits();
    const int base = logicalQubit * state.getRepetitionCode();

    for (int i = 0; i < dim; ++i)
    {
        if (syndromeForIndex(i, base, state.getRepetitionCode()) != targetSyndrome)
            state.amplitudes[i] = 0.0;
    }

    state.normalize();
}

int BitFlipErrorCorrector::HammingWeight(int value, int base, int length)
{
    int count = 0;
    for (int i = 0; i < length; ++i)
        count += (value >> (base + i)) & 1;
    return count;
}

void PhaseFlipErrorCorrector::correct(QuantumState& state)
{
    const int repetitionCode = state.getRepetitionCode();
    for (int logicalQubit = 0; logicalQubit < state.getLogicalQubitCount(); ++logicalQubit)
        applyHadamardBlock(state, logicalQubit);

    bitCorrector.correct(state);

    for (int logicalQubit = 0; logicalQubit < state.getLogicalQubitCount(); ++logicalQubit)
        applyHadamardBlock(state, logicalQubit);
}

void PhaseFlipErrorCorrector::applyHadamardBlock(QuantumState& state, int logicalQubit)
{
    const int repetitionCode = state.getRepetitionCode();
    const int base = logicalQubit * repetitionCode;
    for (int i = 0; i < repetitionCode; ++i)
        state.applyGate(Gate::hadamard(), base + i);
}
