project(test_fsa)

set(CMAKE_CXX_STANDARD)

set(SOURCE_FILES main.cpp Edge.cpp State.cpp FSA.cpp Matcher.cpp)
add_executable(test_dynamic_fsa ${SOURCE_FILES})