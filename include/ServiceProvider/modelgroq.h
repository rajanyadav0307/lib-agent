#pragma once
#include "model.h"
#include <string>

namespace agent {

class GroqModel : public Model {
public:
    GroqModel(const std::string& endpoint,
              const std::string& model_name,
              const std::string& api_key);

    ModelResponse predict(const std::string& prompt) override;

private:
    std::string endpoint_;
    std::string model_name_;
    std::string api_key_;
};

} // namespace agent
