# QuantumErrorCorrectionSimulator

QuantumErrorCorrectionSimulator is a C++ project that simulates the basic principles of quantum error correction used in quantum computing. The goal of this project is to demonstrate how quantum systems can detect and correct errors that occur due to noise and decoherence.

## Overview

Quantum computers rely on qubits, which are extremely sensitive to environmental noise. Even small disturbances can introduce errors into quantum computations. Quantum Error Correction (QEC) is a set of techniques used to detect and correct these errors without directly measuring the quantum information.

This simulator models simple quantum error correction techniques such as:

- Bit-flip errors
- Phase-flip errors
- Redundant qubit encoding
- Syndrome measurement
- Error detection and correction

The project is designed as an educational tool for understanding how quantum error correction works from a computational perspective.

## Features

- Basic qubit state simulation
- Simulation of quantum noise
- Implementation of simple quantum error correction codes
- Error detection using syndrome measurements
- Modular C++ structure for easy extension

## Technologies Used

- C++
- Object-Oriented Programming
- Basic linear algebra concepts
- Quantum computing principles

## Project Structure

QuantumErrorCorrectionSimulator/
│
├── src/ # Source files
├── include/ # Header files
├── test/ # GoogleTest unit tests
├── main.cpp # Entry point of the simulator
└── README.md


## Goals

The purpose of this project is to:

- Learn the fundamentals of quantum error correction
- Explore how fragile quantum states can be protected
- Practice implementing scientific simulations in C++

## Future Improvements

- Implement more advanced error correction codes
- Add visualization of quantum states
- Simulate larger qubit systems
- Improve performance and scalability

## Testing

This project uses **GoogleTest (gtest)** to ensure correctness and high-quality testing practices across all quantum components.

### Test Structure

Tests are cleanly separated from production code and organized by subsystem. Doing so prevents mixing headers and ensures each isolated domain is independently verified:

* `test_qubit.cpp`: Verifies isolated physical qubit behavior (normalization, deterministic metrics, probabilistic superposition).
* `test_quantumGate.cpp`: Asserts individual gate matrices and correct amplitudes (Hadamard, Paulis).
* `test_simulator.cpp`: Ensures accurate execution modeling, including logical outputs like Bell states and GHZ state correlation.
* `test_circuit.cpp`: Checks proper operation decoding, logic-to-physical mapping, and layout sizes.
* `test_noise.cpp`: Proves our phase/bit flip environment behaviors strictly respect bounded probability inputs.
* `test_error_correction.cpp`: Ensures accurate identification of syndrome outcomes directly mapping to correct bit-flip mitigation.

### How to Build Tests

Configure your build and ensure a unified configuration includes the testing framework:
```bash
cmake -B build -S .
cmake --build build --config Debug
```
*Note: The CMake automatically incorporates the GoogleTest library and exposes a discrete executable named `unit_tests` to prevent namespace conflicts.*

### How to Run Tests

It is easiest to verify them globally by using CMake's standard test runner, optionally in verbose mode to view detailed pass assertions:
```bash
cd build
ctest -C Debug -V
```

Alternatively, invoke the test binary directly to filter specifically:
```bash
# Run all GoogleTest test suites explicitly
build\Debug\unit_tests.exe

# Filter to simulator subset tests
build\Debug\unit_tests.exe --gtest_filter=SimulatorTest.*
```
