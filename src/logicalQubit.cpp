#include "logicalQubit.h"

LogicalQubit::LogicalQubit(QuantumState& s, int base, int rep)
    : state(s), base(base), repetition(rep) {}

void LogicalQubit::encode()
{
    for (int i = 1; i < repetition; i++)
        state.applyCNOT(base, base + i);
}

void LogicalQubit::applyHadamard()
{
    for (int i = 0; i < repetition; i++)
        state.applyGate(Gate::hadamard(), base + i);
}

void LogicalQubit::applyX()
{
    for (int i = 0; i < repetition; i++)
        state.applyGate(Gate::pauliX(), base + i);
}

void LogicalQubit::applyZ()
{
    for (int i = 0; i < repetition; i++)
        state.applyGate(Gate::pauliZ(), base + i);
}