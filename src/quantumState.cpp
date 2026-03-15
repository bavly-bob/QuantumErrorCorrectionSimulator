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

void QuantumState::applyGate(const Gate &gate, int target)
{
    int dim = 1 << numQubits;

    for (int i = 0; i < dim; i++)
    {
        if (((i >> target) & 1) == 0)
        {
            int j = i | (1 << target);

            auto a = getAmplitude(i);
            auto b = getAmplitude(j);

            setAmplitude(i, gate.m[0][0] * a + gate.m[0][1] * b);
            setAmplitude(j, gate.m[1][0] * a + gate.m[1][1] * b);
        }
    }
}

void QuantumState::applyCNOT(int control, int target)
{
    int dim = 1 << numQubits;

    for (int i = 0; i < dim; i++)
    {
        if (((i >> control) & 1) == 1)
        {
            int j = i ^ (1 << target);

            if (i < j)
                std::swap(amplitudes[i], amplitudes[j]);
        }
    }
}
