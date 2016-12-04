project(etape6)

set(CMAKE_CXX_STANDARD)

set(SOURCE_FILES main.cpp Edge.cpp State.cpp Matcher.cpp Closure.cpp FSA.cpp)
add_executable(etape6 ${SOURCE_FILES})