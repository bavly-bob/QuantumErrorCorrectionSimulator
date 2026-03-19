#include <gtest/gtest.h>
#include "correction.h"
#include "noise.h"

TEST(ErrorCorrectionTest, BitFlipCorrectionFixesSingleErrorOnFirstPhysicalQubit)
{
    QuantumState state(1, 3);
    state.applyGate(Gate::pauliX(), 0);

    BitFlipErrorCorrector corrector;
    corrector.correct(state);

    EXPECT_EQ(state.measureAllLogical(), 0);
}

TEST(ErrorCorrectionTest, BitFlipCorrectionFixesSingleErrorOnSecondPhysicalQubit)
{
    QuantumState state(1, 3);
    state.applyGate(Gate::pauliX(), 1);

    BitFlipErrorCorrector corrector;
    corrector.correct(state);

    EXPECT_EQ(state.measureAllLogical(), 0);
}

TEST(ErrorCorrectionTest, PhaseFlipCorrectionRecoversPlusStateAfterPhaseError)
{
    QuantumState state(1, 3);
    state.applyGate(Gate::hadamard(), 0);

    PhaseFlipErrorCorrector corrector;
    state.applyGate(Gate::pauliZ(), 0);
    corrector.correct(state);

    state.applyGate(Gate::hadamard(), 0);
    EXPECT_EQ(state.measureAllLogical(), 0);
}
