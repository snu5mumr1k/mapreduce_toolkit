#pragma once

#include <string>
#include <core/parser.h>

class MapReduce {
public:
    MapReduce();
    void RunInterpreter();

private:
    bool Execute(const std::string &command);
    void RunDesc(const OperationDescription &op_desc);
    void RunReduce(const OperationDescription &op_desc);
    void RunMap(const OperationDescription &op_desc);
};
