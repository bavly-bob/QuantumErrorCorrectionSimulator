#include <gtest/gtest.h>
#include "circuit.h"

TEST(QuantumCircuitTest, AppendingOperations_AreStoredCorrectly) {
    QuantumCircuit qc;
    qc.h(0);
    qc.x(1);
    qc.z(2);
    qc.cnot(0, 1);
    
    auto ops = qc.getOperations();
    ASSERT_EQ(ops.size(), 12); // Each logical op appends 3 physical ops
    
    EXPECT_EQ(ops[0].type, OpType::H);
    EXPECT_EQ(ops[0].target, 0);
    
    EXPECT_EQ(ops[3].type, OpType::X);
    EXPECT_EQ(ops[3].target, 3);

    EXPECT_EQ(ops[6].type, OpType::Z);
    EXPECT_EQ(ops[6].target, 6);

    EXPECT_EQ(ops[9].type, OpType::CNOT);
    EXPECT_EQ(ops[9].control, 0); // controlBase
    EXPECT_EQ(ops[9].target, 3);  // targetBase
}

