#pragma once 
#include <vector>
#include <complex>
using namespace std;

class qubit {

complex<double> alpha;
complex<double> beta;

public:
    qubit( complex<double> alpha, complex<double> beta);
    void normalize();
    complex<double> getAlpha() const{return alpha;}
    complex<double> getBeta() const{return beta;}
    int measure();
};