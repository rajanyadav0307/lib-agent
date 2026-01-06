#pragma once
#include <cstdint>
#include <string>

namespace agent {

enum class ServiceProviderBackend {
    DUMMY,
    GROQ,
    OpenAI,
    Anthropic
};

struct ServiceProviderConfiguration {
    ServiceProviderBackend backend = ServiceProviderBackend::DUMMY;
    std::string endpoint = "";
    std::string model_name = "";
    std::string api_key = "";
};

struct RuntimeConfig {
    uint32_t seed{42};
    bool deterministic{true};
    bool enableTracing{true};
};

} // namespace agent
