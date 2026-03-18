#include "simulator.h"
#include "quantumState.h"
#include "quantumGate.h"
#include "circuit.h"

Simulator::Simulator(int qubits)
    : logicalQubits(qubits) , state(qubits)
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

        state.applyBitFlipNoise(0.01);
    }

    for (int i = 0; i < logicalQubits; i++)
        state.correctBitFlip(i);
}

int Simulator::measure()
{
    return state.measure();
}

int Simulator::measureAllLogical()
{
    return state.measureAllLogical(logicalQubits);
}
