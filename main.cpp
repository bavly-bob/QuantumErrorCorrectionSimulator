#include <iostream>
#include <cassert>
#include "qubit.h"
#include "quantumGate.h"
#include "singleQubit.h"

using namespace std;

int main()
{
    assert(test_single_qubit());
    cout << "All tests passed!\n";
    
    qubit q({1,0},{0,0});   // |0>
    hadamardGate g;
    g.apply(q);              // H|0> = (|0> + |1>)/sqrt(2)
    g.apply(q);              // H((|0> + |1>)/sqrt(2)) = |0> should return to |0>

    int result = q.measure();

    cout << result << '\n';
}