#pragma once
#include "quantumState.h"
#include "quantumGate.h"
#include "circuit.h"

class Simulator
{
public:
    Simulator(int qubits);
    void run(const QuantumCircuit& circuit);
    int measure();
private:
    QuantumState state;
};