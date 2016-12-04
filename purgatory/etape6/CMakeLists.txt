project(etape6)

set(CMAKE_CXX_STANDARD)

set(CMAKE_CXX_FLAGS  -g)

set(SOURCE_FILES main.cpp Edge.cpp State.cpp Matcher.cpp Closure.cpp FSA.cpp ExpressionParser.cpp ExpressionParser.hpp ConsumerParser.cpp ProducterStream.cpp Parser.cpp)
add_executable(test_improved_pattern ${SOURCE_FILES})