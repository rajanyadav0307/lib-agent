#pragma once

#include <iostream>

#include "../include/agent/Tool.h"

namespace agent {

    inline void executeTool(Tool& tool) {
        std::cout << "[Executor] Executing tool: " << tool.name() << std::endl;
    }
}