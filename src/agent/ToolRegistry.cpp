#include "../include/agent/ToolRegistry.h"
#include <stdexcept>

namespace agent {

void ToolRegistry::registerTool(std::unique_ptr<Tool> tool) {
    if (!tool) throw std::invalid_argument("Cannot register null tool");
    auto name = tool->name();
    if (name.empty()) throw std::invalid_argument("Tool name cannot be empty");

    auto [it, inserted] = tools_.emplace(name, std::move(tool));
    if (!inserted) throw std::runtime_error("Tool already registered: " + name);
}

Tool* ToolRegistry::get(const std::string& name) const {
    auto it = tools_.find(name);
    return it == tools_.end() ? nullptr : it->second.get();
}

} // namespace agent
