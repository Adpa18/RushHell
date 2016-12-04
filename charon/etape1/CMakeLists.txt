project(etape1)

set(CMAKE_CXX_STANDARD)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS -std=c++98)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror")
endif()

set(SOURCE_FILES main.cpp FunctionSignature.hpp)
add_executable(test_functor_type ${SOURCE_FILES})