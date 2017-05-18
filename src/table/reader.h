#pragma once

#include <vector>
#include <table/row.h>
#include <fstream>

class TableReader {
public:
    TableReader(const std::string &filename);

    Row GetRow();

    operator bool() const;

private:
    std::ifstream in_;
    std::vector<std::string> columns_;
};
