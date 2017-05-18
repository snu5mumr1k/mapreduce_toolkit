#pragma once

#include <fstream>
#include <mutex>
#include <vector>
#include <table/row.h>

class TableWriter {
public:
    TableWriter(const std::string &filename, const std::vector<std::string> &columns);

    void WriteRow(const Row &row);

private:
    void RealWriteRow(const Row &row);

    std::ofstream out_;
    std::mutex file_mutex_;
    std::vector<std::string> columns_;
};
