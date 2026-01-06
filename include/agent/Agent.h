#pragma once
#include <string>
#include "ExecutionPlan.h"
#include "ToolRegistry.h"
#include "Trace.h"
#include "ExecutionContext.h"

namespace agent {

class Agent {
public:
    explicit Agent(ToolRegistry& registry);

    void run(const std::string& input, const ExecutionPlan& plan);

    const Trace& trace() const;

private:
    ToolRegistry& registry_;
    Trace trace_;
};

} // namespace agent
