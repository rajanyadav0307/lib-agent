#pragma once
#include "../agent/Tool.h"

namespace tools {

class GmailTool : public agent::Tool {
public:
    std::string name() const override { return "gmail"; }
    std::set<agent::Capability> capabilities() const override { return {agent::Capability::NOTIFY, agent::Capability::NET}; }
    std::string invoke(const std::string& input) override {
        return "[Gmail] " + input;
    }
};

}
