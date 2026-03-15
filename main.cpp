#include <iostream>
#include "quantumState.h"
#include "quantumGate.h"
#include "singleQubit.h"
#include "multiQubits.h"

#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    assert(test_single_qubit());
    assert(test_two_qubits_bell_state());
    assert(test_three_qubits_GHZ_state());
    assert(test_two_qubits_double_hadamard());
    assert(test_two_qubits_double_cnot());
    assert(test_two_qubits_single_hadamard());
    
    cout << "All tests passed!" << endl;
    return 0;
}