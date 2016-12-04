project(etape5)

set(CMAKE_CXX_STANDARD)

set(SOURCE_FILES main.cpp Edge.cpp FSA.cpp Closure.cpp Matcher.cpp State.cpp)
add_executable(etape5 ${SOURCE_FILES})