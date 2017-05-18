#include <params.h>

Params::Params():
    params_({
        {"sep", " "},
        {"tables_dir", "tables/"}
    })
{}

std::string Params::Get(const std::string &param) const {
    return params_.at(param);
}

void Params::Set(const std::string &param, const std::string &value) {
    params_[param] = value;
}
