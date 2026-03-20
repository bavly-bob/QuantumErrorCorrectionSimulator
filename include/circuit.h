#pragma once
#include <vector>

enum class OpType
{
    H,
    X,
    Z,
    CNOT,
    MEASURE_LOGICAL,
    MEASURE_ANCILLA,
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
    QuantumCircuit() = default;
    QuantumCircuit(const QuantumCircuit& other) = default;
    QuantumCircuit(QuantumCircuit&& other) = default;
    QuantumCircuit& operator=(const QuantumCircuit& other) = default;
    QuantumCircuit& operator=(QuantumCircuit&& other) = default;
    ~QuantumCircuit() = default;
private:
    std::vector<Operation> ops;
};
