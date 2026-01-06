#pragma once
#include <vector>
#include <string>

namespace agent {

struct TraceEvent {
    std::string event;
    std::string detail;
    uint64_t timestamp;
};

class Trace {
public:
    void record(const TraceEvent& ev) { events_.push_back(ev); }

    std::string serialize() const;

private:
    std::vector<TraceEvent> events_;
};

} // namespace agent
