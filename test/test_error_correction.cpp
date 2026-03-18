#include <gtest/gtest.h>
#include "quantumState.h"

class ErrorCorrectionTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ErrorCorrectionTest, Syndrome_NoErrors_CorrectProbabilities) {
    QuantumState state(1);
    state.encode(0); // Encode logical qubit 0
    SyndromeProb prob = state.computeSyndromeProb(0);
    EXPECT_DOUBLE_EQ(prob.p00, 1.0);
    EXPECT_DOUBLE_EQ(prob.p10, 0.0);
    EXPECT_DOUBLE_EQ(prob.p11, 0.0);
    EXPECT_DOUBLE_EQ(prob.p01, 0.0);
}

TEST_F(ErrorCorrectionTest, Syndrome_SingleBitFlip_FirstPhysicalQubit) {
    QuantumState state(1);
    state.encode(0);
    state.applyGate(Gate::pauliX(), 0); 
    state.correctBitFlip(0);
    int result = state.measureAllLogical(1);
    EXPECT_EQ(result, 0); // Corrected to logical |0>
}

TEST_F(ErrorCorrectionTest, Syndrome_SingleBitFlip_SecondPhysicalQubit) {
    QuantumState state(1);
    state.encode(0);
    state.applyGate(Gate::pauliX(), 1); 
    state.correctBitFlip(0);
    int result = state.measureAllLogical(1);
    EXPECT_EQ(result, 0); // Corrected to logical |0>
}
