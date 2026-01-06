#pragma once
#include <string>
#include <vector>

namespace agent {

struct ToolCall {
    std::string tool_name;
    std::string args;
};

struct ModelResponse {
    std::string text;
    std::vector<ToolCall> tool_calls;
    bool final = true;
};

class Model {
public:
    virtual ~Model() = default;
    virtual ModelResponse predict(const std::string& prompt) = 0;
};

} // namespace agent
