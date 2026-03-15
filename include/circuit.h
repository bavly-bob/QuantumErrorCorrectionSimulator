#pragma once
#include <vector>
#include "quantumGate.h"

enum class OpType
{
    H,
    X,
    Z,
    CNOT,
    MEASURE
};

struct Operation
{
    OpType type;
    int target;
    int control;
};

class QuantumCircuit
{
public:
    void h(int q);
    void x(int q);
    void z(int q);
    void cnot(int control, int target);
    void measure(int q);
    const std::vector<Operation>& getOperations() const;
    QuantumCircuit();
private:
    std::vector<Operation> ops;
};
