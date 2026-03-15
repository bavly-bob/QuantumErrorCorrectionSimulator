#pragma once 
#include "qubit.h"
#include "quantumGate.h"
#include <vector>
#include <complex>
using namespace std;

bool test_single_qubit()
{
    //test double application of Hadamard gate on |0> should return to |0>
    for(int i = 0; i < 1000; ++i)
    {
        qubit q({1,0},{0,0});   // |0>
        hadamardGate g;
        g.apply(q);              // H|0> = (|0> + |1>)/sqrt(2)
        g.apply(q);              // H((|0> + |1>)/sqrt(2)) = |0> should return to |0>
        int result = q.measure();
        if(result != 0)
            return false; // Test failed
    }

    // test single application of Hadamard gate on |0> should give 50% chance of measuring 0 or 1
    int count0 = 0, count1 = 0;
    for(int i = 0; i < 10000; ++i)
    {
        qubit q({1,0},{0,0});   // |0>
        hadamardGate g;
        g.apply(q);              // H|0> = (|0> + |1>)/sqrt(2)
        int result = q.measure();
        if(result == 0)
            count0++;
        else
            count1++;
    }

    // Check if the counts are approximately 50% each
    if(count0 < 4500 || count0 > 5500)
        return false;

    return true;
}