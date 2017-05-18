#include <set>
#include <helpers/validators.h>

bool LooksLikeColumn(const std::string &s) {
    if (!(IsLetter(s[0]) || s[0] == '_')) {
        return false;
    }
    for (char c : s) {
        if (!(IsLetter(c) || IsDigit(c) || c == '_')) {
            return false;
        }
    }
    return true;
}

bool LooksLikeTableFilename(const std::string &s) {
    return s.find_last_of(".csv") == s.size() - 1;
}

bool IsCapital(char c) {
    return 'A' <= c && c <= 'Z';
}

bool IsLittle(char c) {
    return 'a' <= c && c <= 'z';
}

bool IsLetter(char c) {
    return IsCapital(c) || IsLittle(c);
}

bool IsDigit(char c) {
    return '0' <= c && c <= '9';
}
