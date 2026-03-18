#include "quantumGate.h"
#include <cmath>

Gate::Gate(std::complex<double> a, std::complex<double> b, std::complex<double> c, std::complex<double> d)
    : m{{ {{a, b}}, {{c, d}} }} {}

Gate Gate::hadamard()
{
    double s = 1.0 / std::sqrt(2);
    return Gate(s, s, s, -s);
}

Gate Gate::pauliX()
{
    return Gate(0, 1, 1, 0);
}

Gate Gate::pauliY()
{
    return Gate(0, std::complex<double>(0, -1), std::complex<double>(0, 1), 0);
}

Gate Gate::pauliZ()
{
    return Gate(1, 0, 0, -1);
}

Gate Gate::cnot()
{
    return Gate(1, 0, 0, 1);
}
