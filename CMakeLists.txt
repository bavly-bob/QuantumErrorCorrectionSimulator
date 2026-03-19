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
    src/correction.cpp
)

target_include_directories(${target} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/test
)

# --- Testing Configuration ---
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests 
    test/test_qubit.cpp 
    test/test_quantumGate.cpp 
    test/test_simulator.cpp
    test/test_circuit.cpp
    test/test_noise.cpp
    test/test_error_correction.cpp
    src/quantumState.cpp 
    src/quantumGate.cpp
    src/qubit.cpp
    src/circuit.cpp
    src/simulator.cpp
    src/noise.cpp
    src/correction.cpp
)

target_include_directories(unit_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(unit_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)

