#include <iostream>
#include <memory>
#include "agent/Agent.h"
#include "agent/ExecutionPlan.h"
#include "agent/ToolRegistry.h"
#include "agent/Config.h"
#include "ServiceProvider/modelgroq.h"
#include "toolcollection/SlackNotifyTool.h"
#include "agent/ServiceProviderFactory.h"

int main() {
    using namespace agent;

    // ------------------ Step 1: Configure Service Provider ------------------
    ServiceProviderConfiguration sp_config;
    sp_config.backend = ServiceProviderBackend::GROQ;
    sp_config.endpoint = "https://api.groq.com/openai/v1/chat/completions"; // Groq endpoint
    sp_config.model_name = "llama-3.3-70b-versatile";                          // your model
    sp_config.api_key = std::getenv("GROQ_API_KEY");                                 // set your key

    std::shared_ptr<Model> sp = ServiceProviderFactory::create(sp_config);

    // ------------------ Step 2: Configure ToolRegistry ------------------
    ToolRegistry registry;

    // Slack tool configuration
    tools::SlackConfig slack_config;
    slack_config.webhook_url = std::getenv("SLACK_WEBHOOK_URL");
    slack_config.channel = "#all-aiagent";
    slack_config.username = "incoming-webhook";
    slack_config.icon_emoji = ":ghost:";

    registry.emplaceTool<tools::SlackNotifyTool>(slack_config);

    // ------------------ Step 3: Create ExecutionPlan ------------------
    ExecutionPlan plan;
    plan.addStep({"groq_predict"});   // LLM tool step
    plan.addStep({"slack_notify"});   // Slack step

    // ------------------ Step 4: Run Agent ------------------
    Agent runtime(registry);

    // Input prompt
    std::string input = "Predict if the sentence is positive or negative: 'I love programming!'";

    // Step: define groq_predict as a simple inline tool
    class GroqTool : public Tool {
    public:
        explicit GroqTool(std::shared_ptr<Model> model) : model_(std::move(model)) {}
        std::string name() const override { return "groq_predict"; }
        std::set<Capability> capabilities() const override { return {Capability::LLM}; }

        ToolResult invoke(const ToolContext& ctx) override {
            try {
                ModelResponse resp = model_->predict(ctx.input);
                return {resp.text, ToolStatus::OK, ""};
            } catch (const std::exception& e) {
                return {"", ToolStatus::ERROR, e.what()};
            }
        }
    private:
        std::shared_ptr<Model> model_;
    };

    registry.emplaceTool<GroqTool>(sp);

    // Run agent
    runtime.run(input, plan);

    // ------------------ Step 5: Inspect Trace ------------------
    std::cout << "=== Execution Trace ===" << std::endl;
    std::cout << runtime.trace().serialize() << std::endl;

    return 0;
}
