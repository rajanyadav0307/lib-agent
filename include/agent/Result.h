#pragma once
#include <string>

namespace agent {

enum class ToolStatus {
    OK,
    SKIPPED,
    ERROR
};

struct Result {
    std::string output;
    ToolStatus status;
    std::string error_message;
};

} // namespace agent
