#pragma once
#include <functional>
#include <vector>

namespace agent {

class Scheduler {
public:
    void schedule(std::function<void()> task);
    void run();

private:
    std::vector<std::function<void()>> tasks;
};

} // namespace agent
