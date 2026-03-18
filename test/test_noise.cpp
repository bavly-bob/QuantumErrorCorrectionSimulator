#include <gtest/gtest.h>
#include "quantumState.h"

TEST(NoiseTest, BitFlipNoise_ApplyingWithProbabilityOne) {
    QuantumState state(1); // 1 logical qubit means 3 physical qubits
    state.applyBitFlipNoise(1.0); // Flips all physical qubits deterministically
    int result = state.measureAllLogical(1);
    EXPECT_EQ(result, 1);
}

TEST(NoiseTest, BitFlipNoise_ApplyingWithProbabilityZero) {
    QuantumState state(1);
    state.applyBitFlipNoise(0.0);
    int result = state.measureAllLogical(1);
    EXPECT_EQ(result, 0);
}

TEST(NoiseTest, PhaseFlipNoise_ApplyingWithProbabilityZero) {
    QuantumState state(1);
    state.applyPhaseFlipNoise(0.0);
    int result = state.measureAllLogical(1);
    EXPECT_EQ(result, 0);
}
