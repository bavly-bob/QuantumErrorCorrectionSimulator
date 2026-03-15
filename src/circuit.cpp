#include "circuit.h"

void QuantumCircuit::h(int q)
{
    ops.push_back({OpType::H, q, -1});
}

void QuantumCircuit::x(int q)
{
    ops.push_back({OpType::X, q, -1});
}

void QuantumCircuit::z(int q)   
{
    ops.push_back({OpType::Z, q, -1});
}

void QuantumCircuit::cnot(int control, int target)
{
    ops.push_back({OpType::CNOT, target, control});
}

void QuantumCircuit::measure(int q)
{
    ops.push_back({OpType::MEASURE, q, -1});
}

const std::vector<Operation>& QuantumCircuit::getOperations() const
{
    return ops;
}