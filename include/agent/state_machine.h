#pragma once
#include <string>

namespace agent {
    
enum class AgentState {
    Idle,
    Thinking,
    ToolCalling,
    Observing,
    Finished,
    Error
};

inline std::string state_to_string(AgentState state) {
    switch(state) {
        case AgentState::Idle: return "Idle";
        case AgentState::Thinking: return "Thinking";
        case AgentState::ToolCalling: return "ToolCalling";
        case AgentState::Observing: return "Observing";
        case AgentState::Finished: return "Finished";
        case AgentState::Error: return "Error";
    }
    return "Unknown";
}

}   // namespace agent