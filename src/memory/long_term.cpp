#include "../include/agent/Memory.h"
#include <fstream>

namespace agent {

void LongTermMemory::persist(const std::string& filename) {
    std::ofstream ofs(filename);
    for (const auto& [k,v] : storage_) {
        ofs << k << "=" << v << "\n";
    }
}

void LongTermMemory::load(const std::string& filename) {
    std::ifstream ifs(filename);
    std::string line;
    while (std::getline(ifs, line)) {
        auto pos = line.find('=');
        if (pos != std::string::npos) {
            storage_[line.substr(0,pos)] = line.substr(pos+1);
        }
    }
}

} // namespace agent
