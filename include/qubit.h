#pragma once 
#include <vector>
#include <complex>

class qubit {
std::complex<double> alpha;
std::complex<double> beta;

public:
    qubit( std::complex<double> alpha, std::complex<double> beta);
    void normalize();
    std::complex<double> getAlpha() const{return alpha;}
    std::complex<double> getBeta() const{return beta;}
    int measure();
};