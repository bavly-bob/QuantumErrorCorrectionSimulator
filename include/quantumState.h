#pragma once
#include <vector>
#include <complex>
#include "quantumGate.h"

using namespace std;

class QuantumState {

private:
    int numQubits;
    vector<complex<double>> amplitudes;

public:

    QuantumState(int n);
    int size() const { return amplitudes.size(); }
    complex<double> getAmplitude(int i) const { return amplitudes[i]; }
    void setAmplitude(int i, complex<double> val) { amplitudes[i] = val; }
    void applyGate(const Gate &gate, int target);
    void applyCNOT(int control, int target);
    void normalize();
    int measure();
};