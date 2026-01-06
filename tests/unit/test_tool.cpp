#include "../include/agent/Tool.h"
#include <cassert>

using namespace agent;

class TestTool : public Tool {
public:
    std::string name() const override { return "TestTool"; }
    std::set<Capability> capabilities() const override { return {Capability::READ}; }
    std::string invoke(const std::string& input) override { return "Output: " + input; }
};

int main() {
    TestTool t;
    assert(t.invoke("abc") == "Output: abc");
    assert(t.name() == "TestTool");
    return 0;
}
