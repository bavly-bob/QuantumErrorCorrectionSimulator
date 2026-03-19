#include "quantumState.h"
#include <cmath>
#include <random>
#include <complex>
#include <algorithm>
using namespace std;

QuantumState::QuantumState(int n, int repetitionCode)
{
    logicalQubits = n;
    this->repetitionCode = repetitionCode;
    amplitudes.resize(1 << getPhysicalQubits());
    amplitudes[0] = 1.0;   // |000...0>
}

void QuantumState::encode(int logicalQubit)
{
    int base = logicalQubit * repetitionCode;
    for (int i = 1; i < repetitionCode; i++)
        applyCNOT(base, base + i);
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


int QuantumState::measureAllLogical()
{
    int rawResult = measure();  // collapse physical state once

    int logicalResult = 0;
    for (int lq = 0; lq < logicalQubits; ++lq)
    {
        int base = lq * repetitionCode;
        int majority = HammingWeight(rawResult, base, repetitionCode);
        majority = (majority > repetitionCode / 2) ? 1 : 0;
        logicalResult |= (majority << lq);  // pack into bit lq
    }
    return logicalResult;
}

int QuantumState::HammingWeight(int state, int base, int length)
{
    int count = 0;

    for (int i = 0; i < length; i++)
        count += (state >> (base + i)) & 1;

    return count;
}

int QuantumState::sampleSyndrome(const SyndromeProb& sample)
{
    static std::mt19937 gen(std::random_device{}());

    std::discrete_distribution<int> dist(sample.probs.begin(), sample.probs.end());
    return dist(gen);
}

void QuantumState::collapseToSyndrome(int logicalQubit, int targetSyndrome)
{
    int dim = 1 << getPhysicalQubits();

    for (int i = 0; i < dim; i++)
    {
        int syndrome = 0;
        int base = logicalQubit * repetitionCode;
        for (int j = 0; j < repetitionCode - 1; j++)
        {
            int b_i = (i >> (base + j)) & 1;
            int b_next = (i >> (base + j + 1)) & 1;
            syndrome |= ((b_i ^ b_next) << j);
        }

        if (syndrome != targetSyndrome)
            amplitudes[i] = 0.0;
    }

    normalize();
}

SyndromeProb QuantumState::computeSyndromeProb(int logicalQubit)
{
    SyndromeProb s(repetitionCode);
    int dim = 1 << getPhysicalQubits();
    int base = logicalQubit * repetitionCode;

    for (int i = 0; i < dim; i++)
    {
        double p = std::norm(amplitudes[i]);
        if (p == 0.0) continue; // skip zero probability states
        int syndrome = 0;

        for(int j = 0; j < repetitionCode - 1; j++)
        {
            int b_i = (i >> (base + j)) & 1;
            int b_i_plus_1 = (i >> (base + j + 1)) & 1;
            int S_i = b_i ^ b_i_plus_1;
            syndrome |= (S_i << j);
        }

        s[syndrome] += p;
    }

    return s;
}


void QuantumState::collapseLogical(int logicalQubit, int value)
{
    int dim = 1 << getPhysicalQubits();
    int base = logicalQubit * repetitionCode;

    for (int i = 0; i < dim; i++)
    {
        bool match = true;

        for (int j = 0; j < repetitionCode; j++)
        {
            int b = (i >> (base + j)) & 1;
            if (b != value)
            {
                match = false;
                break;
            }
        }

        if (!match)
            amplitudes[i] = 0.0;
    }

    normalize();
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
    int dim = 1 << getPhysicalQubits();

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