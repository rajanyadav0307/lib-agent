# Build filesystem plugin as part of agent_runtime
set(FILESYSTEM_TOOL_SRC fs_tool.cpp)

# Make sure it uses your main include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../include)

# This will add the plugin source to the main agent_runtime library
set(FILESYSTEM_TOOL_SRC_FULL ${CMAKE_CURRENT_SOURCE_DIR}/fs_tool.cpp PARENT_SCOPE)
