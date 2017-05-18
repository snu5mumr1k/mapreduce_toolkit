#include <basic/value.h>

Value::Value():
    type_(Type::Null)
{}

Value::Value(int int_value):
    type_(Type::IntValue),
    int_value_(int_value)
{}

Value::Value(double double_value):
    type_(Type::IntValue),
    double_value_(double_value)
{}

Value::Value(bool bool_value):
    type_(Type::IntValue),
    bool_value_(bool_value)
{}
