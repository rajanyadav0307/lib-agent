#include "../include/agent/Sandbox.h"
#include <functional>
#include <string>

namespace agent {

std::string Sandbox::run_sandboxed(const std::string& tool_name,
                                   std::function<std::string()> func) {
    // Wrap execution with optional isolation
    try {
        return func();
    } catch (...) {
        return "[sandbox_error] Tool " + tool_name + " failed";
    }
}

} // namespace agent
