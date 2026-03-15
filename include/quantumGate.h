#pragma once
#include "qubit.h"

class gate
{
public:
    virtual void apply(qubit &q) = 0;
};

class hadamardGate : public gate
{
public:
    void apply(qubit &q) override;
};

class pauliXGate : public gate
{
public:
    void apply(qubit &q) override;
};

class pauliYGate : public gate
{
public:
    void apply(qubit &q);
};

class pauliZGate : public gate
{
public:
    void apply(qubit &q) override;
};
