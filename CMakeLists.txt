cmake_minimum_required(VERSION 3.16)

set(target Q)

project(${target})
set(CMAKE_CXX_STANDARD 17)

add_executable(${target} 
    main.cpp 
    src/quantumState.cpp 
    src/quantumGate.cpp
    src/qubit.cpp
    src/circuit.cpp
    src/simulator.cpp
    src/noise.cpp
)

target_include_directories(${target} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/test
)

