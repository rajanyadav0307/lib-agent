#include "../include/agent/Trace.h"
#include <chrono>
#include <unordered_map>
#include <string>

namespace agent {

using Clock = std::chrono::steady_clock;

struct Metric {
    size_t count = 0;
    double total_time_ms = 0.0;
};

class MetricsCollector {
public:
    void record(const std::string& name, double duration_ms) {
        auto& m = metrics_[name];
        m.count++;
        m.total_time_ms += duration_ms;
    }

    double avg_time(const std::string& name) const {
        auto it = metrics_.find(name);
        return it != metrics_.end() && it->second.count > 0 ? 
               it->second.total_time_ms / it->second.count : 0.0;
    }
private:
    std::unordered_map<std::string, Metric> metrics_;
};

} // namespace agent
