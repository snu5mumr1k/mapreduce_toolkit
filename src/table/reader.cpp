#include <algorithm>
#include <iostream>
#include <table/reader.h>
#include <helpers/file.h>
#include <basic/value.h>
#include <params.h>
#include <helpers/singleton.h>

TableReader::TableReader(const std::string &filename):
    in_(Singleton<Params>()->Get("tables_dir") + filename),
    columns_(GetDescription(filename))
{
    if (!in_.is_open()) {
        throw std::runtime_error("Didn't manage to open " + filename + " for reading");
    }
    std::string header;
    std::getline(in_, header);
}

Row TableReader::GetRow() {
    std::string new_row;
    std::getline(in_, new_row);
    std::vector<std::string> raw_values = Split(new_row);
    std::vector<Value> row_values;
    for (auto value : raw_values) {
        row_values.push_back(Value::FromString(value));
    }
    return Row{columns_, row_values};
}

TableReader::operator bool() const {
    return static_cast<bool>(in_);
}
