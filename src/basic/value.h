#pragma once

class Value {
public:
    enum class Type {
        IntValue,
        DoubleValue,
        BoolValue,
        Null
    };

    Value();
    Value(int int_value);
    Value(double double_value);
    Value(bool bool_value);
private:
    Type type_;

    int int_value_;
    double double_value_;
    bool bool_value_;
};
