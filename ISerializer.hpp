//
// Created by koncord on 23.01.19.
//

#pragma once

#include <ostream>

class Parser;

class ISerializer
{
protected:
    const Parser &parser;
public:
    explicit ISerializer(const Parser &parser) : parser(parser) {}
    virtual std::ostream &Serialize(std::ostream &out) const = 0;
    friend std::ostream &operator<<(std::ostream &out, const ISerializer &obj) { return obj.Serialize(out); }
};
