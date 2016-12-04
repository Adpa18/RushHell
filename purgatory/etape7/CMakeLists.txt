project(etape7)

set(CMAKE_CXX_STANDARD)
set(CMAKE_CXX_FLAGS -g)

set(SOURCE_FILES main.cpp ConsumerParser.cpp Edge.cpp ExpressionParser.cpp FSA.cpp Matcher.cpp Parser.cpp ProducterStream.cpp State.cpp Closure.cpp)
add_executable(test_notifier ${SOURCE_FILES})