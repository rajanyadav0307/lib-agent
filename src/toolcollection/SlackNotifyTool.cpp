#include "../include/toolcollection/SlackNotifyTool.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

namespace tools {

SlackNotifyTool::SlackNotifyTool(const SlackConfig& config)
    : config_(config) {}

std::string SlackNotifyTool::name() const { 
    return "slack_notify"; 
}

std::set<agent::Capability> SlackNotifyTool::capabilities() const {
    return {agent::Capability::NET, agent::Capability::NOTIFY};
}

agent::ToolResult SlackNotifyTool::invoke(const agent::ToolContext& ctx) {
    try {
        nlohmann::json payload_json;
        payload_json["channel"] = config_.channel;
        payload_json["username"] = config_.username;
        payload_json["text"] = ctx.input;
        payload_json["icon_emoji"] = config_.icon_emoji;

        std::string json_str = payload_json.dump();
        std::string payload = "payload=" + json_str;  // Slack wants exactly this

        CURL* curl = curl_easy_init();
        if (!curl) return {"", agent::ToolStatus::ERROR, "CURL init failed"};

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        curl_easy_setopt(curl, CURLOPT_URL, config_.webhook_url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        CURLcode res = curl_easy_perform(curl);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            return {"", agent::ToolStatus::ERROR, curl_easy_strerror(res)};
        }

        return {"Slack notification sent", agent::ToolStatus::OK, ""};
    } catch (const std::exception& e) {
        return {"", agent::ToolStatus::ERROR, e.what()};
    }
}


} // namespace tools
