#include <iostream>
#include <fstream>
#include <core/map_reduce.h>
#include <helpers/file.h>
#include <table/reader.h>
#include <table/writer.h>
#include <table/row.h>

MapReduce::MapReduce()
{}

void MapReduce::RunInterpreter() {
    std::cout << "MapReduce toolkit utility by Andrey Feofilaktov<andarpolis@gmail.com>" << std::endl;
    std::string command;
    do {
        std::cout << ":) ";
        std::getline(std::cin, command);
    } while(Execute(command) && !std::cin.eof());
    std::cout << std::endl;
}

bool MapReduce::Execute(const std::string &command) {
    Parser p;
    OperationDescription description;
    try {
        description = p.Parse(command);
        switch (description.type) {
            case OperationType::Map:
                RunMap(description);
                break;
            case OperationType::Reduce:
                RunReduce(description);
                break;
            case OperationType::Desc:
                RunDesc(description);
                break;
            case OperationType::Continue:
                break;
            case OperationType::Quit:
                return false;
            default:
                std::cout << "Failed to parse command, try again" << std::endl;
        }
    } catch (const std::runtime_error &re) {
        std::cout << re.what() << std::endl;
        return true;
    }
    return true;
}

void MapReduce::RunDesc(const OperationDescription &op_desc) {
    std::vector<std::vector<std::string>> descriptions;
    for (auto token : op_desc.tokens) {
        try {
            descriptions.push_back(GetDescription(token.filename));
        } catch (const std::runtime_error &re) {
            std::cout << re.what() << std::endl;
            return;
        }
    }
    for (auto d : descriptions) {
        for (auto col : d) {
            std::cout << col << std::endl;
        }
    }
}

void MapReduce::RunReduce(const OperationDescription &op_desc) {
    std::cout << "Reduce" << std::endl;
    std::cout << "insert into " << op_desc.insert_into << std::endl;
    std::cout << "from " << op_desc.from << std::endl;
    TableReader tr(op_desc.from);
    TableWriter tw(op_desc.insert_into, op_desc.columns_order);
    while (tr) {
        Row row = tr.GetRow();
        if (op_desc.where.Execute(row)) {
            tw.WriteRow(op_desc.select.Execute(row));
        }
    }
}

void MapReduce::RunMap(const OperationDescription &op_desc) {
    std::cout << "Map" << std::endl;
    std::cout << "insert into " << op_desc.insert_into << std::endl;
    std::cout << "from " << op_desc.from << std::endl;
    TableReader tr(op_desc.from);
    TableWriter tw(op_desc.insert_into, op_desc.columns_order);
    while (tr) {
        Row row = tr.GetRow();
        if (op_desc.where.Execute(row)) {
            tw.WriteRow(op_desc.select.Execute(row));
        }
    }
}
