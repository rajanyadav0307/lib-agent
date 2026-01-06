#include "../include/ServiceProvider/modeldummy.h"

namespace agent {

ModelResponse DummyModel::predict(const std::string& prompt) {
    return ModelResponse{"Dummy response: " + prompt, {}, true};
}

} // namespace agent
