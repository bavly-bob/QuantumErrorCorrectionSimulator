#include <gtest/gtest.h>
#include "qubit.h"

TEST(QubitTest, Initialization_DefaultStateIsZero) {
    qubit q(1.0, 0.0);
    EXPECT_DOUBLE_EQ(q.getAlpha().real(), 1.0);
    EXPECT_DOUBLE_EQ(q.getAlpha().imag(), 0.0);
    EXPECT_DOUBLE_EQ(q.getBeta().real(), 0.0);
    EXPECT_DOUBLE_EQ(q.getBeta().imag(), 0.0);
}

TEST(QubitTest, Initialization_NormalizedState) {
    qubit q(1.0, 1.0);
    EXPECT_DOUBLE_EQ(q.getAlpha().real(), 1.0 / std::sqrt(2.0));
    EXPECT_DOUBLE_EQ(q.getBeta().real(), 1.0 / std::sqrt(2.0));
}

TEST(QubitTest, Measurement_DeterministicZero) {
    qubit q(1.0, 0.0);
    EXPECT_EQ(q.measure(), 0);
    // After measurement, state should collapse to |0>
    EXPECT_DOUBLE_EQ(q.getAlpha().real(), 1.0);
    EXPECT_DOUBLE_EQ(q.getBeta().real(), 0.0);
}

TEST(QubitTest, Measurement_DeterministicOne) {
    qubit q(0.0, 1.0);
    EXPECT_EQ(q.measure(), 1);
    // After measurement, state should collapse to |1>
    EXPECT_DOUBLE_EQ(q.getAlpha().real(), 0.0);
    EXPECT_DOUBLE_EQ(q.getBeta().real(), 1.0);
}

TEST(QubitTest, Measurement_ProbabilisticSuperposition) {
    int count0 = 0;
    int count1 = 0;
    int num_shots = 10000;
    
    for (int i = 0; i < num_shots; ++i) {
        qubit q(1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0));
        if (q.measure() == 0) count0++;
        else count1++;
    }
    
    // Allow roughly 5% error margin for probabilistic test
    EXPECT_NEAR(count0, 5000, 500);
    EXPECT_NEAR(count1, 5000, 500);
}
