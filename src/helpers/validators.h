#pragma once

#include <string>

bool LooksLikeColumn(const std::string &s);
bool LooksLikeTableFilename(const std::string &s);

bool IsCapital(char c);
bool IsLittle(char c);
bool IsLetter(char c);
bool IsDigit(char c);
