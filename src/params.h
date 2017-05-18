#pragma once

#include <string>
#include <unordered_map>

class Params {
public:
    Params();

    std::string Get(const std::string &param) const;
    void Set(const std::string &param, const std::string &value);

private:
    std::unordered_map<std::string, std::string> params_;
};
