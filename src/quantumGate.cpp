#include "quantumGate.h"
#include <cmath>

Gate pauliX()
{
    Gate g;
    g.m[0][0] = 0;
    g.m[0][1] = 1;
    g.m[1][0] = 1;
    g.m[1][1] = 0;
    return g;
}

Gate pauliZ()
{
    Gate g;
    g.m[0][0] = 1;
    g.m[0][1] = 0;
    g.m[1][0] = 0;
    g.m[1][1] = -1;
    return g;
}

Gate pauliY()
{
    Gate g;
    g.m[0][0] = 0;
    g.m[0][1] = std::complex<double>(0, -1);
    g.m[1][0] = std::complex<double>(0, 1);
    g.m[1][1] = 0;
    return g;
}

Gate hadamard()
{
    Gate g;
    double s = 1.0 / std::sqrt(2);
    g.m[0][0] = s;
    g.m[0][1] = s;
    g.m[1][0] = s;
    g.m[1][1] = -s;
    return g;
}