#pragma once
#include <complex>
#include <array>


class Gate
{
public:
    Gate() = default;
    Gate(std::complex<double> a, std::complex<double> b, std::complex<double> c, std::complex<double> d);
    static Gate hadamard();
    static Gate pauliX();
    static Gate pauliY();
    static Gate pauliZ();
    static Gate cnot();

    std::complex<double> at(int i, int j) const { return m.at(i).at(j); }
private:
    std::array<std::array<std::complex<double>, 2>, 2> m;
};


