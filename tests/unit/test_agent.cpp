#include "../include/agent/Agent.h"
#include "../include/agent/Tool.h"
#include "../include/agent/Config.h"
#include <cassert>
#include <iostream>

using namespace agent;

class DummyTool : public Tool {
public:
    std::string name() const override { return "DummyTool"; }
    std::set<Capability> capabilities() const override { return {Capability::READ}; }
    std::string invoke(const std::string& input) override { return input + "_done"; }
};

int main() {
    Agent agent;
    DummyTool tool;
    agent.addTool(tool);

    RuntimeConfig cfg;
    cfg.deterministic = true;
    cfg.seed = 42;
    cfg.enableTracing = true;

    agent.run("TestInput", cfg);

    std::string trace_output = agent.trace();
    assert(!trace_output.empty()); // check trace is recorded

    std::cout << "[PASS] Agent tests\n";
    return 0;
}
