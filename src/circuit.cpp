#include "circuit.h"

void QuantumCircuit::h(int q)
{
    int base = q * 3;
    ops.push_back({OpType::H, base, -1});
    ops.push_back({OpType::H, base + 1, -1});
    ops.push_back({OpType::H, base + 2, -1});
}

void QuantumCircuit::x(int q)
{
    int base = q * 3;
    ops.push_back({OpType::X, base, -1});
    ops.push_back({OpType::X, base + 1, -1});
    ops.push_back({OpType::X, base + 2, -1});
}

void QuantumCircuit::z(int q)   
{
    int base = q * 3;
    ops.push_back({OpType::Z, base, -1});
    ops.push_back({OpType::Z, base + 1, -1});
    ops.push_back({OpType::Z, base + 2, -1});
}

void QuantumCircuit::cnot(int control, int target)
{
    int controlBase = control * 3;
    int targetBase = target * 3;
    ops.push_back({OpType::CNOT, targetBase, controlBase});
    ops.push_back({OpType::CNOT, targetBase + 1, controlBase + 1});
    ops.push_back({OpType::CNOT, targetBase + 2, controlBase + 2});
}

const std::vector<Operation>& QuantumCircuit::getOperations() const
{
    return ops;
}