#pragma once
#include "quantumState.h"
#include "quantumGate.h"
#include "circuit.h"

class Simulator
{
public:
    Simulator(int qubits, int repetitionCode);
    void run(QuantumCircuit& circuit);
    int measure();
    int measureAllLogical();
private:
    int logicalQubits;
    int repetitionCode;
    QuantumState state;
};