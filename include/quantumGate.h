#pragma once
#include <complex>

struct Gate
{
    std::complex<double> m[2][2];
};

Gate hadamard();
Gate pauliX();
Gate pauliY();
Gate pauliZ();
Gate cnot();
