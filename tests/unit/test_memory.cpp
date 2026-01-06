#include "../include/agent/memory/ShortTermMemory.h"
#include "../include/agent/memory/LongTermMemory.h"
#include <cassert>

using namespace agent;

int main() {
    ShortTermMemory stm;
    stm.put("k", "v");
    assert(stm.get("k") == "v");

    LongTermMemory ltm;
    ltm.put("foo", "bar");
    assert(ltm.get("foo") == "bar");

    return 0;
}
