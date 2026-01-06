#include "../include/agent/Agent.h"
#include "../include/agent/ExecutionPlan.h"
#include "../include/agent/ExecutionContext.h"
#include "../include/agent/Clock.h"

namespace agent {

Agent::Agent(ToolRegistry& registry) 
    : registry_(registry) {}

void Agent::run(const std::string& input, const ExecutionPlan& plan) {
    DeterministicClock clock;

    std::string current_input = input;
    for (const auto& step : plan.steps()) {
        Tool* tool = registry_.get(step.tool_name);
        if (!tool) {
            trace_.record({"tool_skip", step.tool_name, clock.now()});
            continue;
        }

        ToolContext tool_ctx{
            .input = current_input,
            .trace = trace_
        };

        trace_.record({"tool_start", tool->name(), clock.now()});

        try {
            ToolResult result = tool->invoke(tool_ctx);

            if (result.status == ToolStatus::OK) {
                current_input = result.output;
                trace_.record({"tool_end", tool->name(), clock.now()});
            } else {
                trace_.record({"tool_error", result.error_message, clock.now()});
                break; // fail-fast policy (industrial default)
            }

        } catch (const std::exception& e) {
            trace_.record({"tool_exception", e.what(), clock.now()});
            break;
        }

        clock.tick();

    }
}

const Trace& Agent::trace() const {
    return trace_;
}

} // namespace agent
