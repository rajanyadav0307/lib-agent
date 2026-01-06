#pragma once
#include <functional>
#include <string>

namespace agent {

class Sandbox {
public:
    Sandbox() = default;
    ~Sandbox() = default;

    bool init() { return true; }

    std::string run_sandboxed(const std::string& tool_name,
                              std::function<std::string()> func);
};

} // namespace agent
