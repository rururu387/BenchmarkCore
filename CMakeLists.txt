cmake_minimum_required(VERSION 3.5)

project(benchmarkCore LANGUAGES CXX)

set(JAVA_HOME "/home/lavrentiy/.jbang/currentjdk")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fPIC -shared -O0 -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux")

add_executable(benchmarkCore com_goose_jni_JNIBenchmarkRunner.h com_goose_jni_JNIBenchmarkRunner.cpp ${JAVA_HOME}/include ${JAVA_HOME}/include)
target_include_directories(benchmarkCore PUBLIC ${JAVA_HOME}/include)
target_include_directories(benchmarkCore PUBLIC ${JAVA_HOME}/include/linux)
set_target_properties(benchmarkCore
                        PROPERTIES
                            OUTPUT_NAME "benchmarkCore"
                            SUFFIX ".so")
