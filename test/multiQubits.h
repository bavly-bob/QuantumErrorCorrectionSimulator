#pragma once
#include "circuit.h"
#include "simulator.h"
#include "quantumState.h"
#include "quantumGate.h"
#include <vector>
#include <complex>
using namespace std;

bool test_two_qubits_bell_state()
{
    //test Bell state creation
    int count00 = 0, count11 = 0;
    for(int i = 0; i < 10000; ++i)
    {
        QuantumCircuit qc;
        qc.h(0);
        qc.cnot(0, 1);
        Simulator sim(2);
        sim.run(qc);
        int result = sim.measureAllLogical();
        if(result != 0 && result != 3)
            return false;
        if(result == 0)
            count00++;
        else
            count11++;
    }
    cout << "test_two_qubits_bell_state: " << count00 << " " << count11 << "\n";
    if(count00 < 4500 || count00 > 5500)
        return false;
    return true;
}

bool test_three_qubits_GHZ_state()
{
    //test GHZ state creation
    for(int i = 0; i < 1000; ++i)
    {
        QuantumCircuit qc;
        qc.h(0);
        qc.cnot(0, 1);
        qc.cnot(0, 2);
        Simulator sim(3);
        sim.run(qc);
        int result = sim.measureAllLogical();
        if(result != 0 && result != 7)
            return false;
    }
    return true;
}

bool test_three_qubits_W_state()
{
    //test W state creation
    for(int i = 0; i < 1000; ++i)
    {
        QuantumCircuit qc;
        qc.h(0);
        qc.cnot(0, 1);
        qc.cnot(0, 2);
        Simulator sim(3);
        sim.run(qc);
        int result = sim.measureAllLogical();
        if(result != 0 && result != 7)
            return false;
    }
    return true;
}

// test double hadamard on two qubits
bool test_two_qubits_double_hadamard()
{
    //test double application of Hadamard gate on |00> should return to |00>
    for(int i = 0; i < 1000; ++i)
    {
        QuantumCircuit qc;
        qc.h(0);
        qc.h(1);
        qc.h(0);
        qc.h(1);
        Simulator q(2);
        q.run(qc);
        int result = q.measureAllLogical();
        if(result != 0)
            return false;
    }
    return true;
}

bool test_two_qubits_double_cnot()
{
    //test double application of CNOT gate on |00> should return to |00>
    for(int i = 0; i < 1000; ++i)
    {
        QuantumCircuit qc;
        qc.cnot(0, 1);
        qc.cnot(0, 1);
        Simulator sim(2);
        sim.run(qc);
        int result = sim.measureAllLogical();
        if(result != 0)
            return false;
    }
    return true;
}

// test single hadamard on two qubits
bool test_two_qubits_single_hadamard()
{
    int count00 = 0, count11 = 0, count01 = 0, count10 = 0;
    // the first qubit should be 50% 0 and 50% 1
    // the second qubit should be | 0 > as no gate is applied to it
    for(int i = 0; i < 10000; ++i)
    {
        QuantumCircuit qc;
        qc.h(0);
        Simulator sim(2);
        sim.run(qc);
        int result = sim.measureAllLogical();
        if(result == 0)
            count00++;
        else if(result == 1)
            count01++;
        else if(result == 2)
            count10++;
        else if(result == 3)
            count11++;
        else cout << "error: " << result << "\n";
    }
    cout << "test_two_qubits_single_hadamard: " << count00 << " " << count11 << " " << count01 << " " << count10 << "\n";
    if(count00 < 4500 || count00 > 5500)
        return false;
    return true;
}