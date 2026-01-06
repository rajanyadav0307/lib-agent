#include "../include/agent/Trace.h"
#include <sstream>

namespace agent {

std::string Trace::serialize() const {
    std::ostringstream oss;
    oss << "{ \"trace\": [";
    for (size_t i = 0; i < events_.size(); ++i) {
        oss << "{"
            << "\"event\":\"" << events_[i].event << "\","
            << "\"detail\":\"" << events_[i].detail << "\","
            << "\"ts\":" << events_[i].timestamp
            << "}";
        if (i + 1 < events_.size()) oss << ",";
    }
    oss << "] }";
    return oss.str();
}

} // namespace agent
