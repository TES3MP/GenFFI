//
// Created by koncord on 23.01.19.
//

#pragma once

#include "ISerializer.hpp"

class ToMono: public ISerializer
{
public:
    explicit ToMono(const Parser &parser): ISerializer(parser) {}
    std::ostream &Serialize(std::ostream &out) const override;
};
