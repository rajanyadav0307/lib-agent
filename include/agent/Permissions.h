#pragma once
#include <set>
#include "Tool.h"

namespace agent {

class EnginePermissions {
public:
    explicit EnginePermissions(std::set<Capability> allowed)
        : allowed_caps(std::move(allowed)) {}

    bool isAllowed(const Tool& tool) const {
        for (auto cap : tool.capabilities())
            if (allowed_caps.count(cap) == 0)
                return false;
        return true;
    }

private:
    std::set<Capability> allowed_caps;
};

} // namespace agent
