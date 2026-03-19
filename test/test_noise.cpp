#include <gtest/gtest.h>
#include "noise.h"

TEST(NoiseTest, BitFlipProbabilityZeroLeavesStateUnchanged)
{
    QuantumState state(1, 3);
    BitFlipNoise noise(0.0);
    noise.apply(state);
    EXPECT_EQ(state.measureAllLogical(), 0);
}

TEST(NoiseTest, BitFlipProbabilityOneFlipsAllPhysicalQubits)
{
    QuantumState state(1, 3);
    BitFlipNoise noise(1.0);
    noise.apply(state);
    EXPECT_EQ(state.measureAllLogical(), 1);
}

TEST(NoiseTest, PhaseFlipProbabilityZeroLeavesStateUnchanged)
{
    QuantumState state(1, 3);
    PhaseFlipNoise noise(0.0);
    noise.apply(state);
    EXPECT_EQ(state.measureAllLogical(), 0);
}

TEST(NoiseTest, PhaseFlipProbabilityOneDoesNotChangeZBasisZeroState)
{
    QuantumState state(1, 3);
    PhaseFlipNoise noise(1.0);
    noise.apply(state);
    EXPECT_EQ(state.measureAllLogical(), 0);
}
