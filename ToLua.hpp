//
// Created by koncord on 23.01.19.
//

#pragma once

#include "ISerializer.hpp"

class ToLua: public ISerializer
{
public:
    explicit ToLua(const Parser &parser): ISerializer(parser) {}
    std::ostream &Serialize(std::ostream &out) const override;
};
