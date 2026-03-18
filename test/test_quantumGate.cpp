#include <gtest/gtest.h>
#include "quantumGate.h"
#include <cmath>

TEST(QuantumGateTest, Creation_HadamardGate) {
    Gate h = Gate::hadamard();
    double inv_sqrt2 = 1.0 / std::sqrt(2.0);
    EXPECT_DOUBLE_EQ(h.at(0,0).real(), inv_sqrt2);
    EXPECT_DOUBLE_EQ(h.at(0,1).real(), inv_sqrt2);
    EXPECT_DOUBLE_EQ(h.at(1,0).real(), inv_sqrt2);
    EXPECT_DOUBLE_EQ(h.at(1,1).real(), -inv_sqrt2);
}

TEST(QuantumGateTest, Creation_PauliXGate) {
    Gate x = Gate::pauliX();
    EXPECT_DOUBLE_EQ(x.at(0,0).real(), 0.0);
    EXPECT_DOUBLE_EQ(x.at(0,1).real(), 1.0);
    EXPECT_DOUBLE_EQ(x.at(1,0).real(), 1.0);
    EXPECT_DOUBLE_EQ(x.at(1,1).real(), 0.0);
}

TEST(QuantumGateTest, Creation_PauliYGate) {
    Gate y = Gate::pauliY();
    EXPECT_DOUBLE_EQ(y.at(0,0).real(), 0.0);
    EXPECT_DOUBLE_EQ(y.at(0,1).imag(), -1.0);
    EXPECT_DOUBLE_EQ(y.at(1,0).imag(), 1.0);
    EXPECT_DOUBLE_EQ(y.at(1,1).real(), 0.0);
}

TEST(QuantumGateTest, Creation_PauliZGate) {
    Gate z = Gate::pauliZ();
    EXPECT_DOUBLE_EQ(z.at(0,0).real(), 1.0);
    EXPECT_DOUBLE_EQ(z.at(0,1).real(), 0.0);
    EXPECT_DOUBLE_EQ(z.at(1,0).real(), 0.0);
    EXPECT_DOUBLE_EQ(z.at(1,1).real(), -1.0);
}
