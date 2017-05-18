#include <table/row.h>

Row::Row(const std::vector<std::string> &columns, const std::vector<Value> &values):
    values_()
{
    if (columns.size() != values.size()) {
        throw std::runtime_error("Operation finished");
    }
    for (int i = 0; i < columns.size(); ++i) {
        values_[columns[i]] = values[i];
    }
}

Row::operator bool() const {
    return static_cast<bool>(values_.begin()->second);
}

Value &Row::operator [](const std::string &key) {
    return values_[key];
}

const Value &Row::operator [](const std::string &key) const {
    return values_.at(key);
}
