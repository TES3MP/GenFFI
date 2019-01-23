//
// Created by koncord on 20.01.19.
//

#include "Utils.hpp"

std::ostream &operator<<(std::ostream &stream, const CXString &str)
{
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}

std::string GetCXXString(const CXString &str)
{
    if(str.data == nullptr)
        return "";
    std::string c = clang_getCString(str);
    clang_disposeString(str);
    return c;
}
