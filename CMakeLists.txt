cmake_minimum_required(VERSION 3.20)
project(agent_runtime LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#Options
option(AGENT_ENABLE_TRACING "Enable tracing" ON)
option(AGENT_ENABLE_PLUGINS "Enable plugins" ON)

# ------------------- Dependencies -------------------
# nlohmann_json
find_package(nlohmann_json 3.10 REQUIRED)

# libcurl
find_package(CURL REQUIRED)

#Include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#Sources
file(GLOB_RECURSE SRC_FILES src/*.cpp)


# Add the plugin subdirectory
#add_subdirectory(plugins/tools/filesystem)

# Append plugin source file to agent_runtime
#list(APPEND SRC_FILES ${FILESYSTEM_TOOL_SRC_FULL})

#Library
add_library(agent_runtime STATIC ${SRC_FILES})

# Link dependencies
target_link_libraries(agent_runtime
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE CURL::libcurl
)


#Example
add_executable(simple_agent ${CMAKE_CURRENT_SOURCE_DIR}/examples/simple_agent.cpp)

target_link_libraries(simple_agent PRIVATE agent_runtime)


# Unit tests
#add_executable(test_tool ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/test_tool.cpp)
#target_link_libraries(test_tool PRIVATE agent_runtime)

#add_executable(test_memory ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/test_memory.cpp)
#target_link_libraries(test_memory PRIVATE agent_runtime)

#add_executable(test_agent ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/test_agent.cpp)
#target_link_libraries(test_agent PRIVATE agent_runtime)

#add_executable(phase6_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/phase6_test.cpp)
#target_link_libraries(phase6_test agent_runtime ${GTEST_BOTH_LIBRARIES} pthread)

#enable_testing()

#add_test(NAME test_tool COMMAND test_tool)
#add_test(NAME test_memory COMMAND test_memory)
#add_test(NAME test_agent COMMAND test_agent)
#add_test(NAME Phase6Test COMMAND phase6_test)
