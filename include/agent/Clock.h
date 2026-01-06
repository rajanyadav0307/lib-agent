#pragma once
#include <cstdint>

namespace agent {

class DeterministicClock {
public:
    explicit DeterministicClock(uint64_t start = 0) : time(start) {}
    uint64_t now() const { return time; }
    void tick(uint64_t delta = 1) { time += delta; }
    void seed(uint64_t s) { time = s; }

private:
    uint64_t time;
};

} // namespace agent
