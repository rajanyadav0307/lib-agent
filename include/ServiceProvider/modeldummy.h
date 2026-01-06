#pragma once
#include "model.h"

namespace agent {

class DummyModel : public Model {
public:
    ModelResponse predict(const std::string& prompt) override;
};

} // namespace agent
