#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "Tool.h"

namespace agent {

class ToolRegistry {
public:
    void registerTool(std::unique_ptr<Tool> tool);

    template<typename T, typename... Args>
    void emplaceTool(Args&&... args) {
        registerTool(std::make_unique<T>(std::forward<Args>(args)...));
    }

    Tool* get(const std::string& name) const;
    bool has(const std::string& name) const { return tools_.count(name) > 0; }
    size_t size() const { return tools_.size(); }

private:
    std::unordered_map<std::string, std::unique_ptr<Tool>> tools_;
};

} // namespace agent
