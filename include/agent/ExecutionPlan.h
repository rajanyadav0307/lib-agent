#pragma once
#include <vector>
#include <string>

namespace agent {

struct ExecutionStep {
    std::string tool_name;
};

class ExecutionPlan {
public:
    void addStep(const ExecutionStep& step) { steps_.push_back(step); }
    const std::vector<ExecutionStep>& steps() const { return steps_; }

private:
    std::vector<ExecutionStep> steps_;
};

} // namespace agent
