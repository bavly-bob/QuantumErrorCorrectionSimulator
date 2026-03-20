#include "simulator.h"
#include "correction.h"
#include "quantumState.h"
#include "quantumGate.h"
#include "circuit.h"

Simulator::Simulator(int qubits, int repetitionCode)
    : logicalQubits(qubits), repetitionCode(repetitionCode), state(qubits, repetitionCode)
{}

void Simulator::run(QuantumCircuit& circuit)
{
    for (const auto& op : circuit.getOperations())
    {
        switch (op.type)
        {
            case OpType::H:
            {
                const int base = op.target * repetitionCode;
                for (int i = 0; i < repetitionCode; ++i)
                    state.applyGate(Gate::hadamard(), base + i);
                break;
            }
            case OpType::X:
            {
                const int base = op.target * repetitionCode;
                for (int i = 0; i < repetitionCode; ++i)
                    state.applyGate(Gate::pauliX(), base + i);
                break;
            }
            case OpType::Z:
            {
                const int base = op.target * repetitionCode;
                for (int i = 0; i < repetitionCode; ++i)
                    state.applyGate(Gate::pauliZ(), base + i);
                break;
            }
            case OpType::CNOT:
            {
                const int controlBase = op.control * repetitionCode;
                const int targetBase = op.target * repetitionCode;
                for (int i = 0; i < repetitionCode; ++i)
                    state.applyCNOT(controlBase + i, targetBase + i);
                break;
            }
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
