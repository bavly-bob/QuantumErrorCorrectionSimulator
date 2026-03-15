#include <iostream>
#include <cassert>
#include "quantumState.h"
#include "quantumGate.h"
#include "singleQubit.h"

using namespace std;

int main()
{
    assert(test_single_qubit());
    cout << "All tests passed!\n";

    QuantumState q(1);
    q.applyGate(hadamard(), 0);              // H|0> = (|0> + |1>)/sqrt(2)

    int result = q.measure();

    cout << result << '\n';
}