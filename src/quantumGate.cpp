#include "quantumGate.h"
#include <cmath>

const double sqrt2_inv = 1.0 / sqrt(2.0);

void hadamardGate::apply(qubit &q) {
    complex<double> newAlpha = (q.getAlpha() + q.getBeta()) * sqrt2_inv;
    complex<double> newBeta = (q.getAlpha() - q.getBeta()) * sqrt2_inv;
    q = qubit(newAlpha, newBeta);
}

void pauliXGate::apply(qubit &q) {
    complex<double> newAlpha = q.getBeta();
    complex<double> newBeta = q.getAlpha();
    q = qubit(newAlpha, newBeta);
}

void pauliYGate::apply(qubit &q) {
    complex<double> newAlpha = -1i * q.getBeta();
    complex<double> newBeta = 1i * q.getAlpha();
    q = qubit(newAlpha, newBeta);
}

void pauliZGate::apply(qubit &q) {
    complex<double> newAlpha = q.getAlpha();
    complex<double> newBeta = -q.getBeta();
    q = qubit(newAlpha, newBeta);
}
