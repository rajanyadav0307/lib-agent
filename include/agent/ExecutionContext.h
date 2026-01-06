#pragma once
#include <string>
#include "Trace.h"

namespace agent {

struct ExecutionContext {
    std::string input;
    std::string output;
    std::string current_tool;
    Trace& trace;
    uint64_t timestamp = 0;
};

} // namespace agent
