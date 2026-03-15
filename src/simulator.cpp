#include "simulator.h"
#include "quantumState.h"
#include "quantumGate.h"
#include "circuit.h"

Simulator::Simulator(int qubits)
    : state(qubits)
{
}

void Simulator::run(const QuantumCircuit& circuit)
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

            case OpType::MEASURE:
                state.measure();
                break;
        }
    }
}

int Simulator::measure()
{
    return state.measure();
}
