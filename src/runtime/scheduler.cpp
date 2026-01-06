#include "../include/runtime/scheduler.h"

namespace agent {

void Scheduler::schedule(std::function<void()> task) {
    tasks.push_back(task);
}

void Scheduler::run() {
    for (auto& task : tasks) {
        task();
    }
    tasks.clear();
}

} // namespace agent
