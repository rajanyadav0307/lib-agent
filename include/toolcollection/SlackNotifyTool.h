#pragma once
#include "../agent/Tool.h"
#include <string>
#include <set>

namespace tools {

struct SlackConfig {
    std::string webhook_url;
    std::string channel;
    std::string username;
    std::string icon_emoji;
};

class SlackNotifyTool : public agent::Tool {
public:
    explicit SlackNotifyTool(const SlackConfig& config);

    std::string name() const override;
    std::set<agent::Capability> capabilities() const override;

    agent::ToolResult invoke(const agent::ToolContext& ctx) override;

private:
    SlackConfig config_;
};

} // namespace tools
