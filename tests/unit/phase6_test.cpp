#include "gtest/gtest.h"
#include "../include/agent/agent.h"
#include "../include/agent/tool.h"

class ReadTool : public agent::Tool {
public:
    std::string name() const override { return "ReadTool"; }
    std::set<agent::Capability> capabilities() const override { return {agent::Capability::READ}; }
    std::string invoke(const std::string& input) override {
        return "Read: " + input;
    }
};

class WriteTool : public agent::Tool {
public:
    std::string name() const override { return "WriteTool"; }
    std::set<agent::Capability> capabilities() const override { return {agent::Capability::WRITE}; }
    std::string invoke(const std::string& input) override {
        return "Write: " + input;
    }
};

TEST(Phase6, AgentExecutesToolsAndTraces) {
    agent::Agent agent;

    ReadTool rtool;
    WriteTool wtool;

    agent.addTool(rtool);
    agent.addTool(wtool);

    agent::RuntimeConfig cfg;
    cfg.deterministic = true;
    cfg.seed = 123;

    agent.run("Test input", cfg);

    std::string trace_json = agent.trace();
    
    // Check that tool calls appear in trace
    EXPECT_NE(trace_json.find("tool_call"), std::string::npos);
    EXPECT_NE(trace_json.find("ReadTool"), std::string::npos);
    EXPECT_NE(trace_json.find("WriteTool"), std::string::npos);

    // Check that model call appears in trace
    EXPECT_NE(trace_json.find("model_call"), std::string::npos);

    // Optional: print trace for inspection
    std::cout << trace_json << std::endl;
}
