#include "../../include/ServiceProvider/modelgroq.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace agent {

// Helper for CURL
namespace {
size_t curlWriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
} // anonymous

GroqModel::GroqModel(const std::string& endpoint,
                     const std::string& model_name,
                     const std::string& api_key)
    : endpoint_(endpoint), model_name_(model_name), api_key_(api_key) {}

ModelResponse GroqModel::predict(const std::string& prompt) {
    std::cout << "[GroqModel] Sending prompt to Groq endpoint...\n";

    // Prepare payload
    nlohmann::json payload;
    payload["model"] = model_name_;
    payload["messages"] = {{{"role", "user"}, {"content", prompt}}};

    std::string payload_str = payload.dump();
    std::string response_text;

    CURL* curl = curl_easy_init();
    if (!curl) throw std::runtime_error("Failed to initialize CURL");

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key_).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, endpoint_.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_text);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::ostringstream oss;
        oss << "CURL error: " << curl_easy_strerror(res);
        throw std::runtime_error(oss.str());
    }

    // Parse response
    nlohmann::json json_resp = nlohmann::json::parse(response_text, nullptr, false);
    if (json_resp.is_discarded()) {
        throw std::runtime_error("Groq response JSON parse failed");
    }

    if (!json_resp.contains("choices") || json_resp["choices"].empty()) {
        throw std::runtime_error("Groq response missing choices");
    }

    std::string assistant_text = json_resp["choices"][0]["message"]["content"].get<std::string>();

    return ModelResponse{assistant_text, {}, true};
}

} // namespace agent
