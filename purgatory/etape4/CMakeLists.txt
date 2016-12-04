project(test_nsa_to_dfa)

set(CMAKE_CXX_STANDARD)

set(CMAKE_CXX_FLAGS -g)

set(SOURCE_FILES main.cpp Edge.cpp State.cpp FSA.cpp Matcher.cpp Closure.cpp Closure.h)
add_executable(test_nsa_to_dfa ${SOURCE_FILES})