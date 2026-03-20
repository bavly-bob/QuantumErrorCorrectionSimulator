#include <gtest/gtest.h>
#include "correction.h"
#include "noise.h"

// Helper to create |0> logical state
QuantumState createZeroState()
{
    QuantumState expected(1, 3);
    return expected;
}

TEST(ErrorCorrectionTest, BitFlipCorrectionFixesSingleErrorOnFirstPhysicalQubit)
{
    QuantumState state(1, 3);
    state.applyGate(Gate::pauliX(), 0);

    BitFlipErrorCorrector corrector;
    corrector.correct(state);

    QuantumState expected = createZeroState();
    EXPECT_NEAR(state.fidelity(expected), 1.0, 1e-6);
}

TEST(ErrorCorrectionTest, BitFlipCorrectionFixesSingleErrorOnSecondPhysicalQubit)
{
    QuantumState state(1, 3);
    state.applyGate(Gate::pauliX(), 1);

    BitFlipErrorCorrector corrector;
    corrector.correct(state);

    QuantumState expected = createZeroState();
    EXPECT_NEAR(state.fidelity(expected), 1.0, 1e-6);
}

TEST(ErrorCorrectionTest, PhaseFlipCorrectionRecoversPlusStateAfterPhaseError)
{
    QuantumState state(1, 3);

    // Prepare |+>
    state.applyGate(Gate::hadamard(), 0);

    // Apply phase error
    state.applyGate(Gate::pauliZ(), 0);

    // Correct
    PhaseFlipErrorCorrector corrector;
    corrector.correct(state);

    // Expected = |+>
    QuantumState expected(1, 3);
    expected.applyGate(Gate::hadamard(), 0);

    EXPECT_NEAR(state.fidelity(expected), 1.0, 1e-6);
}