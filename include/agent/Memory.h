#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace agent {

struct MemoryItem {
    std::string key;
    std::string value;
};

class Memory {
public:
    virtual ~Memory() = default;
    virtual void put(const std::string& key, const std::string& value) = 0;
    virtual std::string get(const std::string& key) const = 0;
};

class ShortTermMemory : public Memory {
public:
    void put(const std::string& key, const std::string& value) override;
    std::string get(const std::string& key) const override;
private:
    std::unordered_map<std::string, std::string> storage_;
};

class LongTermMemory : public Memory {
public:
    void put(const std::string& key, const std::string& value) override;
    std::string get(const std::string& key) const override;
    void persist(const std::string& filename);
    void load(const std::string& filename);
private:
    std::unordered_map<std::string, std::string> storage_;
};

} // namespace agent
