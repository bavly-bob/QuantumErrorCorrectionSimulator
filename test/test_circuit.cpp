#include <gtest/gtest.h>
#include "circuit.h"

TEST(QuantumCircuitTest, AppendingOperations_AreStoredCorrectly) {
    QuantumCircuit qc;
    qc.h(0);
    qc.x(1);
    qc.z(2);
    qc.cnot(0, 1);
    
    auto ops = qc.getOperations();
    ASSERT_EQ(ops.size(), 4);
    
    EXPECT_EQ(ops[0].type, OpType::H);
    EXPECT_EQ(ops[0].target, 0);
    
    EXPECT_EQ(ops[1].type, OpType::X);
    EXPECT_EQ(ops[1].target, 1);

    EXPECT_EQ(ops[2].type, OpType::Z);
    EXPECT_EQ(ops[2].target, 2);

    EXPECT_EQ(ops[3].type, OpType::CNOT);
    EXPECT_EQ(ops[3].control, 0);
    EXPECT_EQ(ops[3].target, 1);
}
