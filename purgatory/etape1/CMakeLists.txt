project(test_fsa)

set(CMAKE_CXX_STANDARD)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS -std=c++98)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror")
endif()

set(SOURCE_FILES main.cpp Machine.hpp Machine.cpp)
add_executable(test_fsa ${SOURCE_FILES})