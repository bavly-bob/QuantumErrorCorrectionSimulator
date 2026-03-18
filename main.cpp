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
    cout << test_single_qubit() << "\n";
    cout << test_two_qubits_bell_state() << "\n";
    cout << test_three_qubits_GHZ_state() << "\n";
    cout << test_two_qubits_double_hadamard() << "\n";
    cout << test_two_qubits_double_cnot() << "\n";
    cout << test_two_qubits_single_hadamard() << "\n";
    
    return 0;
}