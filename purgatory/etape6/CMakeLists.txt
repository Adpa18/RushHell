project(etape6)

set(CMAKE_CXX_STANDARD)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS -std=c++98)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -W -Wall -Werror")
endif()

set(SOURCE_FILES main.cpp Edge.cpp State.cpp Matcher.cpp Closure.cpp FSA.cpp ExpressionParser.cpp ExpressionParser.hpp ConsumerParser.cpp ProducterStream.cpp Parser.cpp)
add_executable(test_improved_pattern ${SOURCE_FILES})