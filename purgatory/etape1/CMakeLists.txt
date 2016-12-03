project(test_fsa)

set(CMAKE_CXX_STANDARD)

set(SOURCE_FILES main.cpp Machine.hpp Machine.cpp)
add_executable(test_fsa ${SOURCE_FILES})