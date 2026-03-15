#include "quantumState.h"
#include <cmath>
#include <random>

QuantumState::QuantumState(int n)
{
    numQubits = n;
    amplitudes.resize(1 << n);
    amplitudes[0] = 1.0;   // |000...0>
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

    return amplitudes.size() - 1; // should never happen
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
    int dim = 1 << numQubits;

    for (int i = 0; i < dim; i++)
    {
        // Skip unless control=1, target=0
        if (!((i >> control) & 1) || ((i >> target) & 1))
            continue;

        std::swap(amplitudes[i], amplitudes[i ^ (1 << target)]);
    }
}
