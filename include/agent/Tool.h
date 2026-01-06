#pragma once
#include <string>
#include <set>
#include "../agent/Trace.h"

namespace agent {

enum class Capability {
    READ,
    WRITE,
    EXECUTE,
    NET,
    LLM,
    NOTIFY
};

enum class ToolStatus {
    OK,
    SKIPPED,
    ERROR
};

struct ToolContext {
    std::string input;   // current data payload
    Trace& trace;        // execution trace (owned by Agent)
};

struct ToolResult {
    std::string output;
    ToolStatus status;
    std::string error_message; // empty if OK
};

class Tool {
public:
    virtual ~Tool() = default;
    virtual std::string name() const = 0;
    virtual std::set<Capability> capabilities() const = 0;

    // **Use ToolContext & ToolResult for industrial-grade consistency**
    virtual ToolResult invoke(const ToolContext& ctx) = 0;
};

} // namespace agent
