#pragma once
#include "../agent/Tool.h"

namespace tools {

class DriveTool : public agent::Tool {
public:
    std::string name() const override { return "drive"; }
    std::set<agent::Capability> capabilities() const override { return {agent::Capability::READ, agent::Capability::WRITE, agent::Capability::NET}; }
    std::string invoke(const std::string& input) override {
        return "[Drive] " + input;
    }
};

}
