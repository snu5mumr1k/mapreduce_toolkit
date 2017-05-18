#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <basic/value.h>

class Row {
public:
    Row(const std::vector<std::string> &columns, const std::vector<Value> &values);

    Value &operator [](const std::string &key);
    const Value &operator [](const std::string &key) const;

    operator bool() const;

private:
    std::unordered_map<std::string, Value> values_;
};
