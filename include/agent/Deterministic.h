#pragma once
#include <cstdint>

namespace agent {

class Deterministic {
public:
    static uint64_t seed() { return 42; }
};

} // namespace agent
