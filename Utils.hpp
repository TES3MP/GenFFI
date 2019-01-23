//
// Created by koncord on 20.01.19.
//

#pragma once

#include <string>
#include <ostream>
#include <clang-c/CXString.h>

std::ostream &operator<<(std::ostream &stream, const CXString &str);
std::string GetCXXString(const CXString &str);
