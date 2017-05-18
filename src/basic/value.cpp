#include <basic/value.h>
#include <cstdlib>

Value::Value():
    type_(Type::Null)
{}

Value::Value(int int_value):
    type_(Type::IntValue),
    int_value_(int_value)
{}

Value::Value(double double_value):
    type_(Type::DoubleValue),
    double_value_(double_value)
{}

Value::Value(bool bool_value):
    type_(Type::BoolValue),
    bool_value_(bool_value)
{}

Value Value::FromString(const std::string &s) {
    if (s == "true") {
        return Value(true);
    }
    if (s == "false") {
        return Value(false);
    }
    Value result;
    char *tmp = nullptr;
    int value = std::strtol(s.c_str(), &tmp, 10);
    if (*tmp == '.') {
        result = Value(std::strtod(s.c_str(), &tmp));
    } else {
        result = Value(value);
    }
    if (*tmp != '\0') {
        throw std::runtime_error("Bad value: " + s);
    }
    return result;
}

Value::operator bool() const {
    switch (type_) {
        case Type::IntValue:
            return static_cast<bool>(int_value_);
        case Type::DoubleValue:
            return static_cast<bool>(double_value_);
        case Type::BoolValue:
            return bool_value_;
        default:
            return false;
    }
}

std::ostream &operator << (std::ostream &out, const Value &value) {
    switch (value.type_) {
        case Value::Type::IntValue:
            out << value.int_value_;
            break;
        case Value::Type::DoubleValue:
            out << value.double_value_;
            break;
        case Value::Type::BoolValue:
            out << value.bool_value_;
            break;
        default:
            break;
    }
    return out;
}
