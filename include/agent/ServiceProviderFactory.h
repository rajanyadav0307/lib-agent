#pragma once
#include <memory>
#include <string>
#include "../ServiceProvider/model.h"
#include "../ServiceProvider/modelgroq.h"
#include "../ServiceProvider/modeldummy.h"  
#include "Config.h"

namespace agent {

class ServiceProviderFactory {
public:
    static std::shared_ptr<Model> create(const ServiceProviderConfiguration& config) {
        if (config.backend == ServiceProviderBackend::DUMMY) return std::make_shared<DummyModel>();
        if (config.backend == ServiceProviderBackend::GROQ) return std::make_shared<GroqModel>(config.endpoint, config.model_name, config.api_key);
        return std::make_shared<DummyModel>();
    }
};

} // namespace agent
