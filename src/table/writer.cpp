#include <table/writer.h>
#include <helpers/singleton.h>
#include <params.h>
#include <iostream>

TableWriter::TableWriter(const std::string &filename, const std::vector<std::string> &columns):
    out_(Singleton<Params>()->Get("tables_dir") + filename),
    columns_(columns)
{
    if (!out_.is_open()) {
        throw std::runtime_error("Didn't manage to open " + filename + " for writing");
    }
    std::string sep;
    std::string real_sep = Singleton<Params>()->Get("sep");
    for (const auto &col : columns_) {
        out_ << sep << col;
        sep = real_sep;
    }
    out_ << std::endl;
}

void TableWriter::WriteRow(const Row &row) {
    file_mutex_.lock();
    RealWriteRow(row);
    file_mutex_.unlock();
}

void TableWriter::RealWriteRow(const Row &row) {
    std::string sep;
    std::string real_sep = Singleton<Params>()->Get("sep");
    for (const auto &col : columns_) {
        out_ << sep << row[col];
        sep = real_sep;
    }
    out_ << std::endl;
}
