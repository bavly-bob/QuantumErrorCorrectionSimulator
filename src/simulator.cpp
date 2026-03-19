#include "simulator.h"
#include "correction.h"
#include "quantumState.h"
#include "quantumGate.h"
#include "circuit.h"

Simulator::Simulator(int qubits, int repetitionCode)
    : logicalQubits(qubits), repetitionCode(repetitionCode), state(qubits, repetitionCode)
{
    for (int i = 0; i < qubits; i++)
        state.encode(i);
}

void Simulator::run(QuantumCircuit& circuit)
{
    for (const auto& op : circuit.getOperations())
    {
        switch (op.type)
        {
            case OpType::H:
                state.applyGate(Gate::hadamard(), op.target);
                break;
            case OpType::X:
                state.applyGate(Gate::pauliX(), op.target);
                break;
            case OpType::Z:
                state.applyGate(Gate::pauliZ(), op.target);
                break;
            case OpType::CNOT:
                state.applyCNOT(op.control, op.target);
                break;
            default:
                break;
        }
    }
}

int Simulator::measure()
{
    return state.measure();
}

int Simulator::measureAllLogical()
{
    return state.measureAllLogical();
}
