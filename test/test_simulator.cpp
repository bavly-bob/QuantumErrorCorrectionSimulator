#include <gtest/gtest.h>
#include "simulator.h"
#include "circuit.h"

class SimulatorTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(SimulatorTest, SingleQubit_DoubleHadamard_ReturnsZero) {
    for(int i = 0; i < 100; ++i) {
        QuantumCircuit qc;
        qc.h(0);              
        qc.h(0);              
        Simulator sim(1);
        sim.run(qc);
        int result = sim.measureAllLogical();
        EXPECT_EQ(result, 0);
    }
}

TEST_F(SimulatorTest, SingleQubit_SingleHadamard_Probabilistic) {
    int count0 = 0, count1 = 0;
    int num_shots = 10000;
    for(int i = 0; i < num_shots; ++i) {
        QuantumCircuit qc;
        qc.h(0);              
        Simulator sim(1);
        sim.run(qc);
        int result = sim.measureAllLogical();
        if(result == 0) count0++;
        else count1++;
    }
    EXPECT_NEAR(count0, 5000, 500);
    EXPECT_NEAR(count1, 5000, 500);
}

TEST_F(SimulatorTest, TwoQubits_BellState_CorrelatedMeasurements) {
    int count00 = 0, count11 = 0;
    int num_shots = 1000;
    for(int i = 0; i < num_shots; ++i) {
        QuantumCircuit qc;
        qc.h(0);
        qc.cnot(0, 1);
        Simulator sim(2);
        sim.run(qc);
        int result = sim.measureAllLogical();
        
        EXPECT_TRUE(result == 0 || result == 3) << "Result was: " << result;
        
        if(result == 0) count00++;
        else if(result == 3) count11++;
    }
}

TEST_F(SimulatorTest, ThreeQubits_GHZState_CorrelatedMeasurements) {
    for(int i = 0; i < 100; ++i) {
        QuantumCircuit qc;
        qc.h(0);
        qc.cnot(0, 1);
        qc.cnot(0, 2);
        Simulator sim(3);
        sim.run(qc);
        int result = sim.measureAllLogical();
        EXPECT_TRUE(result == 0 || result == 7) << "Result was: " << result;
    }
}

TEST_F(SimulatorTest, MultiQubit_DoubleCNOT_ReturnsIdentity) {
    for(int i = 0; i < 100; ++i) {
        QuantumCircuit qc;
        qc.cnot(0, 1);
        qc.cnot(0, 1);
        Simulator sim(2);
        sim.run(qc);
        int result = sim.measureAllLogical();
        EXPECT_EQ(result, 0);
    }
}

TEST_F(SimulatorTest, FiveQubits_HadamardSubposition_ValidState) {
    QuantumCircuit qc;
    for(int i = 0; i < 5; ++i) qc.h(i);
    Simulator sim(5);
    sim.run(qc);
    int result = sim.measureAllLogical();
    EXPECT_GE(result, 0);
    EXPECT_LT(result, 32);
}
